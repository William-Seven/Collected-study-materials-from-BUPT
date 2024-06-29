#ifndef	_CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <time.h>

static time_t epoch; /* epoch timestamp (be same for Station A & B) */

#ifdef _WIN32 /* for Windows Visual Studio */

#include <winsock.h>
#include <io.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/timeb.h>
#include "getopt.h"

#define getopt_long getopt_int
#define stricmp _stricmp

static void socket_init(void)
{
    WORD wVersionRequested;
    WSADATA WSAData;
	int status;

    wVersionRequested = MAKEWORD(1,1);
    status = WSAStartup(wVersionRequested, &WSAData);
    if (status != 0) {
        printf("Windows Socket DLL Error\n");
	    exit(0);
    }
}

unsigned int get_ms(void)
{
	struct _timeb tm;

	_ftime(&tm);

	return (unsigned int)(epoch ? (tm.time - epoch) * 1000 + tm.millitm : 0);
}

#pragma comment(lib,"wsock32.lib")

#else /* for Linux */

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <unistd.h>
#include <ctype.h>
#include <stdlib.h>
#include <errno.h>
#include <getopt.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>
#include <netdb.h>
#define stricmp strcasecmp
#define Sleep(ms) usleep((ms) * 1000)
#define socket_init()
#define SOCKET int

unsigned int get_ms(void)
{
	struct timeval tm;
	struct timezone tz;

	gettimeofday(&tm, &tz);

	return (unsigned int)(epoch ? (tm.tv_sec - epoch) * 1000 + tm.tv_usec / 1000 : 0);
}

#endif

#include <math.h>

#include "protocol.h"

/* channel parameters */
#define CHAN_DELAY 270       /* ms */
#define CHAN_BPS   8000      /* bits per second */

#define ABORT(s) do { lprintf("\nFATAL: %s\nAbort.\n", s); exit(0); } while(0)

#define DEFAULT_TICK 15 /* ms */
#define DEFAULT_CHAN_BER   1.0E-5    /* Bit Error Rate */
#define DEFAULT_PORT  59144

#define NMAGIC     32
#define HEAD_MAGIC 0xa5a5e41b
#define FOOT_MAGIC 0xf5125a5a

static void magic_init(void);
static void magic_check(void);

static unsigned int head_magic[NMAGIC];

/* Parameters */
static int station;
static double ber = DEFAULT_CHAN_BER;  /* Bit Error Rate */
static int mode_ibib = 0;    /* 0: BUSY-IDLE-BUSY-..., 1: IDLE-BUSY-BUSY-... */
static int mode_flood = 0;   /* flood mode */
static int mode_cycle = 100;  /* seconds */
static int mode_life = 0x7fffff00;
static int mode_tick = DEFAULT_TICK;
static int mode_seed = 0x098bcde1;
static int debug_mask = 0; /* debug mask */
static unsigned short port = DEFAULT_PORT;

static SOCKET sock;
static int now; /* timestamp (ms) */
static int noise = 0; /* counter of bit errors */

char *station_name(void)
{
    return (char *)(station == 'a' ? "A" : station == 'b' ? "B" : "XXX");
}

static struct option intopts[] = {
	{ "help",	no_argument, NULL, '?' },
	{ "utopia", no_argument, NULL, 'u' },
	{ "flood",	no_argument, NULL, 'f' },
	{ "ibib",	no_argument, NULL, 'i' },
	{ "nolog",  no_argument, NULL, 'n' },
	{ "debug",	required_argument, NULL, 'd' },
	{ "port",	required_argument, NULL, 'p' },
	{ "ber",	required_argument, NULL, 'b' },
	{ "log",	required_argument, NULL, 'l' },
	{ "ttl",    required_argument, NULL, 't' },
	{ 0, 0, 0, 0 },
};

#define OPT_SHORT "?ufind:p:b:l:t:"

static void config(int argc, char **argv)
{
	char fname[1024];
	int opt;

	if (argc < 2) {
	usage:
		printf("\nUsage:\n  %s <options> <station-name>\n", argv[0]);
		printf(
			"\nOptions : \n"
			"    -?, --help : print this\n"
			"    -u, --utopia : utopia channel (an error-free channel)\n"
			"    -f, --flood : flood traffic\n"
			"    -i, --ibib  : set station B layer 3 sender mode as IDLE-BUSY-IDLE-BUSY-...\n"
			"    -n, --nolog : do not create log file\n"
			"    -d, --debug=<0-7>: debug mask (bit0:event, bit1:frame, bit2:warning)\n"
			"    -p, --port=<port#> : TCP port number (default: %u)\n"
			"    -b, --ber=<ber> : Bit Error Rate (received data only)\n"
			"    -l, --log=<filename> : using assigned file as log file\n"
			"    -t, --ttl=<seconds> : set time-to-live\n"
			"\n"
			"i.e.\n"
			"    %s -fd3 -b 1e-4 A\n"
			"    %s --flood --debug=3 --ber=1e-4 A\n"
			"\n",
			DEFAULT_PORT, argv[0], argv[0]);
		exit(0);
	}

	strcpy(fname, "");

	while ((opt = getopt_long(argc, argv, OPT_SHORT, intopts, NULL)) != -1) {
		switch (opt) {
		case '?':
			goto usage;

		case 'u':
			ber = 0.0;
			break;

		case 'f':
			mode_flood = 1;
			break;

		case 'i':
			mode_ibib = 1;
			break;

		case 'n':
			strcpy(fname, "nul");
			break;

		case 'd':
			debug_mask = atoi(optarg);
			break;

		case 'p':
			port = (unsigned short)atoi(optarg);
			break;

		case 'b':
			ber = strtod(optarg, 0);
			if (ber >= 1.0) {
				printf("Bad BER %.3f\n", ber);
				goto usage;
			}
			break;

		case 'l':
			strcpy(fname, optarg);
			break;

		case 't':
			mode_life = atoi(optarg) * 1000; /* ms */
			break;

		default:
			printf("ERROR: Unsupported option\n");
			goto usage;
		}
	}

	if (optind == argc) 
		goto usage;

	station = tolower(argv[optind++][0]);
	if (station != 'a' && station != 'b')
		ABORT("Station name must be 'A' or 'B'");

	if (fname[0] == 0) {
		strcpy(fname, argv[0]);
		if (stricmp(fname + strlen(fname) - 4, ".exe") == 0)
			*(fname + strlen(fname) - 4) = 0;
		strcat(fname, station == 'a' ? "-A.log" : "-B.log");
	}

	if (stricmp(fname, "nul") == 0)
		log_file = NULL;
	else if ((log_file = fopen(fname, "w")) == NULL) 
		printf("WARNING: Failed to create log file \"%s\": %s\n", fname, strerror(errno));

	lprintf(
		"=============================================================\n"
		"                    Station %s                               \n"
		"-------------------------------------------------------------\n",
		station_name());

	lprintf("Protocol.lib, version %s, jiangyanjun0718@bupt.edu.cn\n", VERSION, __DATE__);
	lprintf("Channel: %d bps, %d ms propagation delay, bit error rate ", CHAN_BPS, CHAN_DELAY);
	if (ber > 0.0)
		lprintf("%.1E\n", ber);
	else
		lprintf("0\n");
	lprintf("Log file \"%s\", TCP port %d, debug mask 0x%02x\n", fname, port, debug_mask);
}

/* Create Communication Sockets  */

void protocol_init(int argc, char **argv)
{
	SOCKET admin_sock;
	int i;
    struct sockaddr_in name;

	socket_init();
	magic_init();

	config(argc, argv);
  
    if (station == 'a') {

        srand(mode_seed ^ 97209);

        name.sin_family = AF_INET;
        name.sin_addr.s_addr = INADDR_ANY;
        name.sin_port = htons(port);

        admin_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (admin_sock < 0) 
            ABORT("Create TCP socket");
        if (bind(admin_sock, (struct sockaddr *)&name, sizeof(name)) < 0) {
            lprintf("Station A: Failed to bind TCP port %u", port);
            ABORT("Station A failed to bind TCP port");
        }

        listen(admin_sock, 5);

        lprintf("Station A is waiting for station B on TCP port %u ... ", port);
        fflush(stdout);

        sock = accept(admin_sock, 0, 0);
        if (sock < 0) 
            ABORT("Station A failed to communicate with station B");
        lprintf("Done.\n");

        recv(sock, (char *)&epoch, sizeof(epoch), 0);
    }

    if (station == 'b') {

        srand(mode_seed ^ 18231);

        sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (sock < 0) 
            ABORT("Create TCP socket");

        name.sin_family = AF_INET;
        name.sin_addr.s_addr = inet_addr("127.0.0.1");
        name.sin_port = htons((short)port);

        for (i = 0; i < 60; i++) {
            lprintf("Station B is connecting station A (TCP port %u) ... ", port);
            fflush(stdout);

            if (connect(sock, (struct sockaddr *)&name, sizeof(struct sockaddr_in)) < 0) {
                lprintf("Failed!\n");
                Sleep(2000);
            } else {
                lprintf("Done.\n");
                break;
            }
        }
        if (i == 6)
            ABORT("Station B failed to connect station A");

        time(&epoch);
        send(sock, (char *)&epoch, sizeof(epoch), 0);
    }

    {
        struct tm *newtime;
        newtime = localtime(&epoch);
        lprintf("New epoch: %s", asctime(newtime));
        lprintf("=================================================================\n\n");
    }

    /* socket options */
    {
        int timeout_ms = 10; 
        int buf_size = 1024 * 64;
        int on = 1;

        setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout_ms, sizeof(int));
        setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout_ms, sizeof(int));

        setsockopt(sock, SOL_SOCKET, SO_RCVBUF, (char *)&buf_size, sizeof(int));
        setsockopt(sock, SOL_SOCKET, SO_SNDBUF, (char *)&buf_size, sizeof(int));

        setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, (char *)&on, sizeof(on));   
    }   

    get_ms();
}

/* Physical Layer: Sender */

/* Sending queue structure */

#define SQ_SIZE (128 * 1024) 

static unsigned char sq[SQ_SIZE];
static int sq_head, sq_tail;
static int inform_phl_ready = 1;

#define sq_inc(p, n) (p = (p + n) % SQ_SIZE)

static int send_bytes_allowed = 0;

static int sq_len(void)
{
    return (sq_tail + SQ_SIZE - sq_head) % SQ_SIZE;
}

int phl_sq_len(void)
{
    return sq_len();
}

static void send_byte(unsigned char byte)
{
    inform_phl_ready = 1;

    if (send_bytes_allowed && sq_head == sq_tail) {
        send(sock, (char *)&byte, 1, 0);
        send_bytes_allowed--;
        return;
    }

    if (sq_len() == SQ_SIZE - 1)
        ABORT("Physical Layer Sending Queue overflow");

    sq[sq_tail] = byte;
    sq_inc(sq_tail, 1);
}

void send_frame(unsigned char *frame, int len)
{
    int i;

    send_byte(0xff);
    
    for (i = 0; i < len; i++) {
        send_byte(frame[i] & 0x0f);
        send_byte((frame[i] & 0xf0) >> 4);
    }
    send_byte(0xff);
}

static int send_sq_data(unsigned int start, unsigned int end1)
{
    int ret;

    if (start >= end1) 
        return 0;

    ret = send(sock, (char *)&sq[start], end1 - start, 0);
    if (ret <= 0) {
        lprintf("TCP Disconnected.\n");
        exit(0);
    }

    return ret;
}

static void socket_send(void)
{
    static int last_ts = 0;
    int n, send_tail = sq_head, send_bytes;

    if (last_ts == 0) 
        last_ts = now;

    if (now <= last_ts) 
        return;

    send_bytes_allowed = (now - last_ts) * CHAN_BPS / 8 / 1000 * 2;
    n = sq_len();
    if (n > send_bytes_allowed)
        n = send_bytes_allowed;
    sq_inc(send_tail, n);

    if (send_tail >= sq_head) 
        send_bytes = send_sq_data(sq_head, send_tail);
    else {
        send_bytes = send_sq_data(sq_head, SQ_SIZE);
        send_bytes += send_sq_data(0, send_tail);
    }

    sq_inc(sq_head, send_bytes);
    send_bytes_allowed -= send_bytes;

    last_ts = now;
}

/* Physical Layer: Receiver */

#define BLKSIZE (16 * CHAN_BPS / 8 / (1000 / DEFAULT_TICK))

struct BLK {
    int commit_ts;
    int rptr, wptr;
    struct BLK *link;
    unsigned char data[BLKSIZE];
};

static struct BLK *rblk_head, *rblk_tail;
static unsigned int nbits;

static void socket_recv(void)
{
    struct BLK *blk;
    unsigned char *p;

    blk = (struct BLK *)malloc(sizeof(struct BLK));
    if (blk == NULL) 
        ABORT("No enough memory");

    blk->rptr = 0;
    blk->wptr = recv(sock, (char *)blk->data, BLKSIZE, 0);
    if (blk->wptr <= 0) {
        lprintf("TCP disconnected.\n");
        exit(0);
    }
    nbits += blk->wptr * 4;

    /* Impose noise */
    if (ber != 0.0) {
        int a;
        double rate, fact;

        rate = (double)noise / nbits;
        fact = rate > ber ? 3.5 : 6.0;
        a = (int)((1.0 - pow(1.0 - ber, fact * blk->wptr)) * (RAND_MAX + 1.0) + 0.5);
        if (rand() <= a) {
            p = &blk->data[rand() % blk->wptr];
            if (*p & 0x0f) {
                *p ^= 1 << (rand() % 8);
                noise++;
                dbg_warning("Impose noise on received data, %u/%u=%.1E\n", noise, nbits, (double)noise / nbits);
            }
        }
    }

    blk->commit_ts = now + CHAN_DELAY - 10;
    blk->link = NULL; 

    if (rblk_head == NULL) 
        rblk_head = rblk_tail = blk;
    else {
        rblk_tail->link = blk;
        rblk_tail = blk;
    }
}

static unsigned char recv_byte(void)
{
    unsigned char ch;
    struct BLK *blk = rblk_head;

    if (blk == NULL || blk->commit_ts > now) 
        ABORT("recv_byte(): Receiving Queue is empty");

    ch = blk->data[blk->rptr++];
    if (blk->rptr == blk->wptr) {
        rblk_head = blk->link;
        free(blk);
    } 
    
    return ch;
}

/* Timer Management */

#define NTIMER 129
static int timer[NTIMER];
#define ACK_TIMER_ID (NTIMER - 1)

void start_timer(unsigned int nr, unsigned int ms)
{
    if (nr >= ACK_TIMER_ID) 
        ABORT("start_timer(): timer No. must be 0~128");
    timer[nr] = now + phl_sq_len() * 8000 / CHAN_BPS + ms;
}

void stop_timer(unsigned int nr)
{
    if (nr < ACK_TIMER_ID) 
        timer[nr] = 0;
}

int get_timer(unsigned int nr)
{
    if (nr >= ACK_TIMER_ID || timer[nr] == 0)
        return 0;
    return timer[nr] > now ? timer[nr] - now : 0;
}

void start_ack_timer(unsigned int ms)
{
    if (timer[ACK_TIMER_ID] == 0)
        timer[ACK_TIMER_ID] = now + ms;
}

void stop_ack_timer(void)
{
    timer[ACK_TIMER_ID] = 0;
}

static int scan_timer(int *nr)
{
    int i;

    for (i = 0; i < NTIMER; i++) {
        if (timer[i] && timer[i] <= now) {
            *nr = i;
            timer[i] = 0;
            return i == ACK_TIMER_ID ? ACK_TIMEOUT : DATA_TIMEOUT;
        }
    }
    return 0;
}

/* Network Layer Functions */

static int network_layer_active = 0;
static int rpackets, rbytes;

void enable_network_layer(void)
{
    network_layer_active = 1;
}

void disable_network_layer(void)
{
    network_layer_active = 0;
}

static int network_layer_ready(void)
{
    static int last_ts = 0;

    if (!network_layer_active)
        return 0;

    if (mode_flood) 
        return 1;

    if ((now - last_ts) * CHAN_BPS / 8 / 1000 < PKT_LEN * 3 / 4)
        return 0;

    if (station == 'b') {
        if (now / 1000 / mode_cycle % 2 != mode_ibib) {
            if (now - last_ts < 4000 + rand() % 500)
                return 0;
        }
        if (now < CHAN_DELAY + 3 * PKT_LEN * 8000 / CHAN_BPS)
            return 0;
    }

    last_ts = now;

    return 1;
}

static int randA(void)
{
    static unsigned int holdrand = 0x65109bc4;
    return ((holdrand = holdrand * 214013L + 2531011L) >> 16) & 0x7fff;
}

static int randB(void)
{
    static unsigned int holdrand = 0x1e459090;
    return ((holdrand = holdrand * 214013L + 2531011L) >> 16) & 0x7fff;
}

#define next_char() ((unsigned char)(my_rand() & 0xff))

static int layer3_ready = 0;

int get_packet(unsigned char *packet)
{
    static int pkt_no = 0;
    int i, len;
    int (*my_rand)(void) = station == 'a' ? randA : randB;

    if (!layer3_ready)
        ABORT("get_packet(): Network layer is not ready for a new packet");
    
    len = PKT_LEN;
    for (i = 2; i < len; i++)
        packet[i] = next_char();
    *(unsigned short *)packet = (station - 'a' + 1) * 10000 + (pkt_no++ % 10000);

    layer3_ready = 0;

    return len;
}

static int ts0;

void put_packet(unsigned char *packet, int len)
{
    static int last_ts = 0;
    int i, (*my_rand)(void) = station == 'a' ? randB : randA;

    if (len != PKT_LEN) 
        ABORT("Bad Packet length");

    for (i = 2; i < PKT_LEN; i++) {
        if (packet[i] != next_char()) 
            ABORT("Network Layer received a bad packet from data link layer");
    }
    rpackets++;
    rbytes += len;

    if (now - last_ts > 2000 && now > ts0 + 2000) {
        double bps;
        bps = (double)rbytes * 8 * 1000 / (now - ts0);
        lprintf(".... %d packets received, %.0f bps, %.2f%%, Err %d (%.1e)\n", 
            rpackets, bps, bps / CHAN_BPS * 100, noise, (double)noise/nbits);
        last_ts = now;
    }
}

#define DBG_EVENT    0x01
#define DBG_FRAME    0x02
#define DBG_WARNING  0x04

void dbg_event(char *fmt, ...)
{
	va_list arg_ptr;

	if (debug_mask & DBG_FRAME) {
		va_start(arg_ptr, fmt);
		__v_lprintf(fmt, arg_ptr);
		va_end(arg_ptr);
	}
}

void dbg_frame(char *fmt, ...)
{
	va_list arg_ptr;

	if (debug_mask & DBG_FRAME) {
		va_start(arg_ptr, fmt);
		__v_lprintf(fmt, arg_ptr);
		va_end(arg_ptr);
	}
}

void dbg_warning(char *fmt, ...)
{
	va_list arg_ptr;

	if (debug_mask & DBG_WARNING) {
		va_start(arg_ptr, fmt);
		__v_lprintf(fmt, arg_ptr);
		va_end(arg_ptr);
	}
}

/* Event Generator */

#define PHL_SQ_LEVEL  50 

static int sleep_cnt, start_ms, wakeup_ms, busy_cnt;
static int bias_cnt;

struct RCV_FRAME {
    int len;
    int state;
    unsigned char frame[2048];
    struct RCV_FRAME *link;
};

static struct RCV_FRAME *rf_head, *rf_tail, *rf_buf;

int recv_frame(unsigned char *buf, int size)
{
    int len;
    struct RCV_FRAME *next;
    char msg[256];

    if (rf_head == NULL) 
        ABORT("recv_frame(): Receiving Queue is empty");

    len = rf_head->len;

    if (size < len) { 
        sprintf(msg, "recv_frame(): %d-byte buffer is too small to save %d-byte received frame", size, len);
        ABORT(msg);
    }
    
    memcpy(buf, rf_head->frame, len);

    next = rf_head->link;
    if (next == NULL) 
        rf_tail = NULL;
    free(rf_head); 
    rf_head = next;

    return len;
}

int wait_for_event(int *arg)
{
    fd_set rfd, wfd;
    struct timeval tm;
    int event, n, i, nfds;
    unsigned char ch;

    for (;;) {

        now = get_ms();
     
        /* commit received socket data */
        if (rblk_head && rblk_head->commit_ts <= now) {
            n = rblk_head->wptr - rblk_head->rptr;
            
            if (ts0 == 0) {
                ts0 = now;
                if (ts0 >= n / 2)
                    ts0 -= n / 2;
            }

            for (i = 0; i < n; i++) {
                ch = recv_byte();
                if (ch == 0xff) {
                    if (rf_buf == NULL) 
                        rf_buf = (struct RCV_FRAME *)calloc(1, sizeof(struct RCV_FRAME));
                    else {
                        if (rf_buf->len > 0) {
                            if (rf_head == NULL) 
                                rf_head = rf_tail = rf_buf;
                            else {
                                rf_tail->link = rf_buf;
                                rf_tail = rf_buf;
                            }
                            rf_buf = NULL;
                        }
                    }
                } else if (rf_buf && rf_buf->len < sizeof(rf_buf->frame)) {
                    if (rf_buf->state == 0) {
                        rf_buf->frame[rf_buf->len] = ch;
                        rf_buf->state = 1;
                    } else {
                        rf_buf->frame[rf_buf->len] |= (ch << 4) ^ (ch & 0xf0);
                        rf_buf->len++;
                        rf_buf->state = 0;
                    }
                }
            }

            if (rf_head)
                return FRAME_RECEIVED;
        }
        
        /* test socket send/receive */
        tm.tv_sec = tm.tv_usec = 0;
        FD_ZERO(&rfd);
        FD_ZERO(&wfd);
        FD_SET(sock, &rfd);
        FD_SET(sock, &wfd);

        nfds = (int)(sock + 1);
        if (select(nfds, &rfd, &wfd, 0, &tm) < 0) 
            ABORT("system select()");
         
        /* socket send */
        if (FD_ISSET(sock, &wfd)) 
            socket_send();

        /* socket receive */
        if (FD_ISSET(sock, &rfd)) 
            socket_recv();

        /* network layer event */
        if (network_layer_ready()) {
            layer3_ready = 1;
            return NETWORK_LAYER_READY;
        }

        /* check all timers */
        if ((event = scan_timer(arg)) != 0)
            return event;

        /* physical layer event */
        if (inform_phl_ready && phl_sq_len()  < PHL_SQ_LEVEL) {
            inform_phl_ready = 0;
            return PHYSICAL_LAYER_READY;
        }

        /* delay 'mode_tick' ms */
        if (1) {
            int ms0, t;
            static time_t last_warn;
            ms0 = get_ms();
            magic_check();
            Sleep(mode_tick);
            t = get_ms() - ms0;
            if (t > mode_tick + 50 && time(0) > last_warn + 1) {
                lprintf("** WARNING: System too busy, sleep %d ms, but be awakened %d ms later\n", 
                    mode_tick, t);
                last_warn = time(0);
            }
        } else {
            int ticks, ms;

            sleep_cnt++;

            ms = get_ms();
            if (start_ms == 0)
                start_ms = ms;
            else if (ms - wakeup_ms > 1) {
                ticks = (ms - start_ms) / mode_tick;
                lprintf("====== CPU BUSY for %d ms (cnt %d)\n", ms - wakeup_ms, ++busy_cnt);
                lprintf("------ noSleep %d, sleep %d, Elapse %d ticks\n", ticks - sleep_cnt, sleep_cnt, ticks);
            }

            magic_check();
            ms = get_ms();
            Sleep(mode_tick);
            wakeup_ms = get_ms();

            ms = wakeup_ms - ms;
            if (ms > mode_tick + 1 || ms < mode_tick - 1) 
                lprintf("++++++ Sleep(%d)=%d+%d (cnt %d)\n", mode_tick, mode_tick, ms - mode_tick, ++bias_cnt);
        }

        if (now > mode_life) {
            lprintf("Quit.\n");
            exit(0);
        }
    }
}


/* Memory Protection */
static unsigned int foot_magic[NMAGIC];

static void magic_init(void)
{
    int i;
    for (i = 0; i < NMAGIC; i++) {
        head_magic[i] = HEAD_MAGIC;
        foot_magic[i] = FOOT_MAGIC;;
    }
}

static void magic_check(void)
{
    int i;

    for (i = 0; i < NMAGIC; i++) {
		if (head_magic[i] != HEAD_MAGIC)
			goto exit;
    }

    for (i = 0; i < NMAGIC; i++) {
		if (foot_magic[i] != FOOT_MAGIC)
			goto exit;
    }
	return;

exit:
	ABORT("Memory used by 'protocol.lib' is corrupted by your program");

}
