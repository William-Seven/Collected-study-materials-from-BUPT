#include <stdio.h>
#include <string.h>

#include "datalink.h"
#include "protocol.h"

#define DATA_TIMER 2000              // 数据帧的超时时间
#define ACK_TIMER 300                // 确认帧 ACK 的超时时间
#define MAX_SEQ 63                   // 最大帧序号
#define NR_BUFS ((MAX_SEQ + 1) / 2)  // 帧缓冲区的大小
#define inc(k)       \
    if (k < MAX_SEQ) \
        k++;         \
    else             \
        k = 0  // 序号增加

typedef unsigned char frame_kind;
typedef unsigned char seq_nr;
typedef unsigned char packet[PKT_LEN];
typedef unsigned char boolean;

// 帧的数据结构
typedef struct {
    frame_kind kind;              // 帧的类型
    seq_nr ack;                   // 确认的帧的序号
    seq_nr seq;                   // 帧序号
    unsigned char data[PKT_LEN];  // 帧数据
    unsigned int padding;         // 填充位
} Frame;

static int phl_ready = 0;   // 物理层是否准备好，默认没有
static boolean no_nak = 1;  // 初始化，未发送 NAK

// 判断序号是否正确，区间左闭右开
static boolean between(seq_nr a, seq_nr b, seq_nr c) {
    return ((a <= b && b < c) || (c < a && b < c) || (c < a && a <= b));
}

// 补充校验和，传送给物理层
// 参数：帧指针，帧长度
// x³² + x²⁶ + x²³ + x²² + x²¹ + x²⁰ + x¹⁶ + x¹² + x¹¹ + x¹⁰ + x⁸ + x⁷ + x⁵ + x⁴ + x² + x + 1
static void put_frame(unsigned char* frame, int len) {
    *(unsigned int*)(frame + len) = crc32(frame, len);  // 添加32bit(4B)的校验位
    send_frame(frame, len + 4);
    phl_ready = 0;  // 每次发完,先假设物理层缓存已满
}

// 构建并发送一个data/ACK/NAK帧
/*
        通过frame_expected倒推计算最近收到的帧的序号,作为ack返回。
        从buffer队列中取出packet发送。
        frame_nr为帧序号。
*/
static void send__frame(frame_kind fk, seq_nr frame_nr, seq_nr frame_expected, packet buffer[]) {
    Frame s;

    s.kind = fk;
    s.seq = frame_nr;
    s.ack = (frame_expected + MAX_SEQ) % (MAX_SEQ + 1);  // 捎带ACK
    stop_ack_timer();                                    // ACK 已捎带，停止计时

    if (fk == FRAME_DATA) {
        memcpy(s.data, buffer[frame_nr % NR_BUFS], PKT_LEN);  // 将out_buf中对应该nr的内存复拷贝出来

        dbg_frame("Send DATA %d %d, ID %d\n", s.seq, s.ack, *(short*)s.data);

        put_frame((unsigned char*)&s, 3 + PKT_LEN);  // 在info后插入4字节CRC
        start_timer(frame_nr, DATA_TIMER);           // 开始计时,等待ACK
    } else if (fk == FRAME_ACK) {
        dbg_frame("Send ACK  %d\n", s.ack);
        put_frame((unsigned char*)&s, 2);  // 在ack后插入4字节crc
    } else {
        dbg_frame("Send NAK  %d\n", frame_expected);  // 出错帧NAK的序号为上一个成功帧的序号f.ack的下一帧
        no_nak = 0;
        put_frame((unsigned char*)&s, 2);  // 在ack后插入4字节crc
    }
}

int main(int argc, char** argv) {
    seq_nr ack_expected = 0;        // 发送窗口下限
    seq_nr next_frame_to_send = 0;  // 发送窗口上限+1
    seq_nr frame_expected = 0;      // 下一个准备接收的帧序号,接收窗口下限
    seq_nr too_far = NR_BUFS;       // 接收窗口上限+1

    packet in_buf[NR_BUFS];    // 接收窗口缓存
    packet out_buf[NR_BUFS];   // 发送窗口缓存
    boolean arrived[NR_BUFS];  // 表示in_buf的占用情况
    seq_nr nbuffered = 0;      // 表示in_buf中已接收但未确认的帧个数

    for (int i = 0; i < NR_BUFS; ++i)
        arrived[i] = 0;  // 接收缓冲全部初始化为空

    int event;    // 事件类型
    int arg;      // 超时计时器的序号
    Frame f;      // 接收到的数据帧
    int len = 0;  // 接收到的数据帧的长度

    protocol_init(argc, argv);  // 协议初始化
    lprintf("Designed by Zhang Chenyang, build: " __DATE__
            "  "__TIME__
            "\n");

    disable_network_layer();

    for (;;) {
        // 等待事件发生
        event = wait_for_event(&arg);

        switch (event) {
            case NETWORK_LAYER_READY:
                get_packet(out_buf[next_frame_to_send % NR_BUFS]);                     // 获取待发送帧
                nbuffered++;                                                           // 已发送帧增加
                send__frame(FRAME_DATA, next_frame_to_send, frame_expected, out_buf);  // 发送数据帧
                inc(next_frame_to_send);                                               // 发送窗口上限向前滑动
                break;

            // 流量控制
            case PHYSICAL_LAYER_READY:
                phl_ready = 1;  // 物理层已准备好
                break;

            case FRAME_RECEIVED:
                len = recv_frame((unsigned char*)&f, sizeof f);  // 接收数据帧 f

                // 查错
                if (len < 6 || crc32((unsigned char*)&f, len) != 0) {
                    dbg_event("**** Receiver Error, Bad CRC Checksum\n");
                    // 收到错误帧，且没有发过NAK，则发送NAK
                    if (no_nak) {
                        send__frame(FRAME_NAK, 0, frame_expected, out_buf);  // 第2,4个参数默认,frame_expected就是出错的帧,发送一个NAK帧
                    }
                    break;  // 帧错误,丢弃
                }

                // 收到单独的 ACK
                if (f.kind == FRAME_ACK)
                    dbg_frame("Recv ACK  %d\n", f.ack);

                // 收到数据帧
                if (f.kind == FRAME_DATA) {
                    dbg_frame("Recv DATA %d %d, ID %d\n", f.seq,
                              f.ack, *(short*)f.data);

                    // 收到的帧不是期望收到的帧且没有发过NAK
                    if (f.seq != frame_expected && no_nak) {
                        dbg_event("Recv frame is not lower bound, NAK sent back\n");
                        send__frame(FRAME_NAK, 0, frame_expected, out_buf);  // 发送NAK帧
                    }

                    // 判断接收到的帧是否在接收窗口上下界之间,并判断接收buffer中还有没有属于它的位置
                    if (between(frame_expected, f.seq, too_far) && (arrived[f.seq % NR_BUFS] == 0)) {
                        arrived[f.seq % NR_BUFS] = 1;  // 将接收缓冲的对应位置占下

                        // len=PKT_LEN+3, len=len+4, len在PKT_LEN的基础上+7, 所以包长=len-7
                        memcpy(in_buf[f.seq % NR_BUFS], f.data, len - 7);  // 将该包加入接收缓冲中

                        while (arrived[frame_expected % NR_BUFS]) {  // 滑动更新接收窗口和接收缓冲区
                            dbg_event("Put packet to network layer seq:%d, ID: %d\n", frame_expected, *(short*)(in_buf[frame_expected % NR_BUFS]));
                            put_packet(in_buf[frame_expected % NR_BUFS], len - 7);  // 将缓冲区最早到达的帧上交网络层
                            arrived[frame_expected % NR_BUFS] = 0;                  // 接收缓冲区空出这个位置
                            no_nak = 1;                                             // 新的一帧没有发送过nak
                            inc(frame_expected);                                    // 滑动下界
                            inc(too_far);                                           // 滑动上界
                            start_ack_timer(ACK_TIMER);                             // 开始ACK计时,准备返回ACK
                        }
                    }
                }

                // 收到NAK
                if (f.kind == FRAME_NAK && between(ack_expected, (f.ack + 1) % (MAX_SEQ + 1), next_frame_to_send)) {
                    dbg_frame("Recv NAK  %d --%dbyte\n", (f.ack + 1) % (MAX_SEQ + 1), len);
                    // 如果返回的NAK就是ack_expected,那就将这一帧重发一遍
                    // f.ack表示接收方成功接收的最后一帧,(f.ack + 1) % (MAX_SEQ + 1)就是接收失败的那一帧
                    send__frame(FRAME_DATA, (f.ack + 1) % (MAX_SEQ + 1), frame_expected, out_buf);
                }

                // 累计确认
                while (between(ack_expected, f.ack, next_frame_to_send)) {
                    nbuffered--;               // 发送缓冲弹出确认接收的帧
                    stop_timer(ack_expected);  // 下限停止计时
                    inc(ack_expected);         // 发送窗口下限向前滑动
                }
                break;

            case DATA_TIMEOUT:  // 超时未收到ack
                dbg_event("---- DATA %d timeout, resend ----\n", arg);
                send__frame(FRAME_DATA, arg, frame_expected, out_buf);  // 重发超时的那一帧
                break;

            case ACK_TIMEOUT:  // ACK 定时器超时
                send__frame(FRAME_ACK, 0, frame_expected, out_buf);
                break;
        }

        if (nbuffered < NR_BUFS && phl_ready)  // 发送窗口为NR_BUFS,缓冲满时暂停发送
            enable_network_layer();
        else
            disable_network_layer();
    }
}