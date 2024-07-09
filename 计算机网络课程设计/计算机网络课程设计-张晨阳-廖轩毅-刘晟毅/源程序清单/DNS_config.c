#include "DNS_config.h"

char* host_path = "./dnsrelay.txt";
char* LOG_PATH;
int debug_mode = 0;
int log_mode = 0;

void init(int argc, char* argv[]) {
    socketMode = 0;       // 默认非阻塞模式
    islisten = 0;  // 起始不监听

    /* 获取程序运行参数 */
    get_config(argc, argv);

    /* 初始化socket */
    initializeSocket();

    /* 初始化ID映射表 */
    init_ID_list();

    /* 初始化缓存 */
    init_cache();

    /* 初始化HOST文件 */
    read_host();
}

/* 读取程序命令参数 */
void get_config(int argc, char* argv[]) {
    print_help_info();

    for (int index = 1; index < argc; index++) {  // 使用 index < argc 来避免访问超出数组界限的风险
        if (strcmp(argv[index], "-d") == 0) {   //开启调试模式
            debug_mode = 1;
        }
        else if (strcmp(argv[index], "-l") == 0) {
            log_mode = 1;
        }
        else if (strcmp(argv[index], "-i") == 0) {  //打印系统基本信息
            printf("Hosts path: %s\n", host_path);
            printf("Remote DNS server address: %s\n", dnsServerAddress ? dnsServerAddress : "10.3.9.45, BUPT DNS");
            printf("Mode: %s\n", socketMode == 0 ? "nonblock" : "poll");
        }
        else if (strcmp(argv[index], "-s") == 0 && index + 1 < argc) {   //设置远程DNS服务器地址
            // 检查是否有足够的参数
            if (dnsServerAddress) free(dnsServerAddress);  // 避免内存泄漏
            dnsServerAddress = argv[++index];  // 使用 strdup 来复制字符串，简化代码
        }
        else if (strcmp(argv[index], "-m") == 0 && index + 1 < argc) {   //设置程序的运行模式
            socketMode = atoi(argv[++index]);  // 直接使用 atoi 转换模式数字，减少代码量
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
    printf("|   -i                         打印系统基本信息                                |\n");
    printf("|   -l:                        日志记录                                        |\n");
    printf("|   -d                         开启调试模式                                    |\n");
    printf("|   -s [server_address]        设置远程DNS服务器地址                           |\n");
    printf("|   -m [mode]                  设置程序的运行模式:0/1  非阻塞/阻塞             |\n");
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

        return; // 提前退出，避免深层嵌套
    }

    //if (debug_mode) {
    //    printf("File open succeeded.\n");
    //}

    // 获取并格式化当前时间
    time_t currentTime = time(NULL);
    struct tm* localTime = localtime(&currentTime);
    char timeString[100];
    strftime(timeString, sizeof(timeString), "%Y-%m-%d %H:%M:%S", localTime);
    fprintf(fp, "%s  %s  ", timeString, domain);

    // 根据 IP 地址是否存在写入不同的内容
    if (ip_addr != NULL) {
        fprintf(fp, "%d.%d.%d.%d\n", ip_addr[0], ip_addr[1], ip_addr[2], ip_addr[3]);
    } else {
        fprintf(fp, "Not found in local. Returned from remote DNS server.\n");
    }

    // 刷新缓冲区并关闭文件
    fflush(fp);
    fclose(fp);
}