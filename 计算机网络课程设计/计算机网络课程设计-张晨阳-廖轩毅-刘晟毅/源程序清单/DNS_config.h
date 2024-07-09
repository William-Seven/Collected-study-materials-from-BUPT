#pragma once
/*
* 2024/6/26
* 本文件用于命令行参数解析以及输出到日志中,声明了五个参数，以及一个分析命令行参数的函数接口。
*/
#include "DNS_struct.h"
#include "DNS_server.h"

char IPAddr[DNS_RR_NAME_MAX_SIZE];
char domain[DNS_RR_NAME_MAX_SIZE];
char* host_path;  // HOST文件目录
char* LOG_PATH;   // 日志文件目录

int debug_mode;
int log_mode;

void init(int argc, char* argv[]);

void get_config(int argc, char* argv[]);

void print_help_info();

void write_log(char* domain, uint8_t* ip_addr);

void read_host();

void get_host_info(FILE* ptr);
