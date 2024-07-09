#include "DNS_config.h"

char* host_path = "./dnsrelay.txt";
char* LOG_PATH;
int debug_mode = 0;
int log_mode = 0;

void init(int argc, char* argv[]) {
    socketMode = 0;       // Ĭ�Ϸ�����ģʽ
    islisten = 0;  // ��ʼ������

    /* ��ȡ�������в��� */
    get_config(argc, argv);

    /* ��ʼ��socket */
    initializeSocket();

    /* ��ʼ��IDӳ��� */
    init_ID_list();

    /* ��ʼ������ */
    init_cache();

    /* ��ʼ��HOST�ļ� */
    read_host();
}

/* ��ȡ����������� */
void get_config(int argc, char* argv[]) {
    print_help_info();

    for (int index = 1; index < argc; index++) {  // ʹ�� index < argc ��������ʳ���������޵ķ���
        if (strcmp(argv[index], "-d") == 0) {   //��������ģʽ
            debug_mode = 1;
        }
        else if (strcmp(argv[index], "-l") == 0) {
            log_mode = 1;
        }
        else if (strcmp(argv[index], "-i") == 0) {  //��ӡϵͳ������Ϣ
            printf("Hosts path: %s\n", host_path);
            printf("Remote DNS server address: %s\n", dnsServerAddress ? dnsServerAddress : "10.3.9.45, BUPT DNS");
            printf("Mode: %s\n", socketMode == 0 ? "nonblock" : "poll");
        }
        else if (strcmp(argv[index], "-s") == 0 && index + 1 < argc) {   //����Զ��DNS��������ַ
            // ����Ƿ����㹻�Ĳ���
            if (dnsServerAddress) free(dnsServerAddress);  // �����ڴ�й©
            dnsServerAddress = argv[++index];  // ʹ�� strdup �������ַ������򻯴���
        }
        else if (strcmp(argv[index], "-m") == 0 && index + 1 < argc) {   //���ó��������ģʽ
            socketMode = atoi(argv[++index]);  // ֱ��ʹ�� atoi ת��ģʽ���֣����ٴ�����
        }
    }
}


void print_help_info() {
    printf("+------------------------------------------------------------------------------+\n");
    printf("|                             Welcome to use DNS!                              |\n");
    printf("|                                                                              |\n");
    printf("| Example: nslookup www.bupt.edu.cn 127.0.0.1                                  |\n");
    printf("|                                                                              |\n");
    printf("| Arguments:                                                                   |\n");
    printf("|   -i                         ��ӡϵͳ������Ϣ                                |\n");
    printf("|   -l:                        ��־��¼                                        |\n");
    printf("|   -d                         ��������ģʽ                                    |\n");
    printf("|   -s [server_address]        ����Զ��DNS��������ַ                           |\n");
    printf("|   -m [mode]                  ���ó��������ģʽ:0/1  ������/����             |\n");
    printf("+------------------------------------------------------------------------------+\n");
}

void read_host() {
    FILE* host = fopen(host_path, "r");

    if (!host) {
        printf("Error! Can not open hosts file!\n\n");
        exit(1);
    }
    get_host_info(host);
}

void get_host_info(FILE* ptr) {
    int num = 0;
    while (!feof(ptr)) {
        uint8_t this_ip[4];
        fscanf(ptr, "%s", IPAddr);
        fscanf(ptr, "%s", domain);
        num++;
        TranIP(this_ip, IPAddr);
        insert_node(this_ip, domain);
    }

    if (debug_mode == 1)
        printf("%d domain name address info has been loaded.\n\n", num);
}

void write_log(char* domain, uint8_t* ip_addr) {
    FILE* fp = fopen("./log.txt", "a");
    if (fp == NULL) {
        if (debug_mode)
            printf("File open failed.\n");

        return; // ��ǰ�˳����������Ƕ��
    }

    //if (debug_mode) {
    //    printf("File open succeeded.\n");
    //}

    // ��ȡ����ʽ����ǰʱ��
    time_t currentTime = time(NULL);
    struct tm* localTime = localtime(&currentTime);
    char timeString[100];
    strftime(timeString, sizeof(timeString), "%Y-%m-%d %H:%M:%S", localTime);
    fprintf(fp, "%s  %s  ", timeString, domain);

    // ���� IP ��ַ�Ƿ����д�벻ͬ������
    if (ip_addr != NULL) {
        fprintf(fp, "%d.%d.%d.%d\n", ip_addr[0], ip_addr[1], ip_addr[2], ip_addr[3]);
    } else {
        fprintf(fp, "Not found in local. Returned from remote DNS server.\n");
    }

    // ˢ�»��������ر��ļ�
    fflush(fp);
    fclose(fp);
}