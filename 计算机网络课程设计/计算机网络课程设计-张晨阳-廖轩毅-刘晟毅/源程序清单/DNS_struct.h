/*
本文件用于实现dns报文的基本结构
    DNS 报文格式如下：
    +---------------------+
    |        Header       | 报文头，固定12字节，由结构体DNS_header存储
    +---------------------+
    |       Question      | 向域名服务器的查询请求，由结构体DNS_question存储
    +---------------------+
    |        Answer       | 对于查询问题的回复（DNS_resource_record结构）
    +---------------------+
    |      Authority      | 指向授权域名服务器（DNS_resource_record结构）
    +---------------------+
    |      Additional     | 附加信息（DNS_resource_record结构）
    +---------------------+
*/
#pragma once
#include <time.h>
#include <stdio.h>         // 标准输入输出头文件
#include <stdlib.h>        // 标准库函数头文件，如malloc, free等
#include <string.h>        // 字符串操作函数头文件
#include <stdint.h>        // 定义了整型变量的精确宽度类型
#include <WinSock2.h>      // Windows Socket API的头文件
#include <ws2tcpip.h>      // 提供更多的socket函数和结构，如getaddrinfo等
#pragma comment(lib, "ws2_32.lib")  // 自动链接到ws2_32.lib库，该库是Windows下实现socket编程的库
#pragma warning(disable:4996)      // 禁用编译器警告4996，通常是关于某些函数不安全的警告


// DNS报文的最大长度
#define DNS_STRING_MAX_SIZE 8192

// DNS资源记录中域名的最大长度
#define DNS_RR_NAME_MAX_SIZE 512

// DNS查询或响应标志，0表示查询，1表示响应
#define DNS_QR_QUERY 0
#define DNS_QR_ANSWER 1

// DNS操作码，表示查询类型
// 0表示标准查询，1表示反向查询，2表示服务器状态请求
#define DNS_OPCODE_QUERY 0
#define DNS_OPCODE_IQUERY 1
#define DNS_OPCODE_STATUS 2

// DNS资源记录类型，表示不同类型的DNS记录
#define DNS_TYPE_A 1       // A记录，表示IPv4地址
#define DNS_TYPE_NS 2      // NS记录，表示权威名称服务器
#define DNS_TYPE_CNAME 5   // CNAME记录，表示规范名称
#define DNS_TYPE_SOA 6     // SOA记录，表示起始授权机构
#define DNS_TYPE_PTR 12    // PTR记录，表示指针记录
#define DNS_TYPE_HINFO 13  // HINFO记录，表示主机信息
#define DNS_TYPE_MINFO 14  // MINFO记录，表示邮件信息
#define DNS_TYPE_MX 15     // MX记录，表示邮件交换记录
#define DNS_TYPE_TXT 16    // TXT记录，表示文本记录
#define DNS_TYPE_AAAA 28   // AAAA记录，表示IPv6地址

// DNS类，表示地址类型，通常为1，表示因特网
#define DNS_CLASS_IN 1

// DNS响应代码，表示查询的返回状态
// 0表示无错误，3表示名字错误
#define DNS_RCODE_OK 0
#define DNS_RCODE_NXDOMAIN 3

// DNS 报文 Header 结构体
typedef struct DNS_header {
    uint16_t id;            // 标识符，用于标识查询和响应的唯一ID

    // 标志位字段，位域表示
    uint8_t qr : 1;         // 查询/响应标志，0表示查询，1表示响应
    uint8_t opcode : 4;     // 操作码，表示查询类型：0=标准查询（QUERY），1=反向查询（IQUERY），2=服务器状态请求（STATUS）
    uint8_t aa : 1;         // 权威回答标志，1表示该响应由权威服务器生成
    uint8_t tc : 1;         // 截断标志，1表示消息由于超过长度而被截断
    uint8_t rd : 1;         // 期望递归标志，1表示客户端希望服务器递归查询
    uint8_t ra : 1;         // 可用递归标志，1表示服务器支持递归查询
    uint8_t z : 3;          // 保留字段，必须为0
    uint8_t rcode : 4;      // 返回码，表示查询的返回状态：0=无错误，1=格式错误，2=服务器错误，3=名字错误，4=未实现，5=拒绝

    // 计数器字段
    uint16_t qdcount;       // 问题数目，表示查询部分的问题条目数
    uint16_t ancount;       // 回答数目，表示回答部分的回答条目数
    uint16_t nscount;       // 权威记录数目，表示权威记录部分的记录条目数
    uint16_t arcount;       // 附加记录数目，表示附加记录部分的记录条目数
} Dns_Header;


// 报文 Question 结构体
typedef struct DNS_question {
    char* q_name;           // 查询的域名或IP地址，使用字符串指针表示
    uint16_t q_type;        // 查询类型，如A（IPv4地址记录）、MX（邮件交换记录）、CNAME（规范名称记录）等
    uint16_t q_class;       // 查询类，通常为1（表示IN，因特网）
    struct DNS_question* next;     // 指向下一个查询问题的指针，用于链表结构
} Dns_Question;

// 定义 ResourceData 联合体，用于存储不同类型的资源数据
union ResourceData {
    // A 记录 (IPv4 地址)
    struct {
        uint8_t IP_addr[4];      // 4 字节的 IPv4 地址
    } a_record;

    // AAAA 记录 (IPv6 地址)
    struct {
        uint8_t IP_addr[16];     // 16 字节的 IPv6 地址
    } aaaa_record;

    // SOA 记录 (权威记录的起始)
    struct {
        char* MName;             // 主服务器域名
        char* RName;             // 管理员邮箱
        uint32_t serial;         // 版本号
        uint32_t refresh;        // 刷新数据间隔
        uint32_t retry;          // 重试间隔
        uint32_t expire;         // 超时重传时间
        uint32_t minimum;        // 最小生存时间
    } soa_record;

    // CNAME 记录 (规范名称)
    struct {
        char* cname;             // 规范名称
    } cname_record;

    // MX 记录 (邮件交换)
    struct {
        uint16_t preference;     // 优先级，值越小优先级越高
        char* exchange;          // 邮件交换服务器域名
    } mx_record;

    // TXT 记录 (文本记录)
    struct {
        char* text;              // 文本内容
    } txt_record;
};

// 报文 Resource Record 结构体
typedef struct DNS_resource_record {
    char* name;                         // 域名或主机名，使用字符串指针表示
    uint16_t type;                      // 资源数据类型，表示该记录的类型，如A、AAAA、CNAME、MX等
    uint16_t rr_class;                  // 资源数据类，通常为1，表示IN（因特网）
    uint32_t ttl;                       // 生存时间（Time to Live），表示该记录在缓存中的有效时间（秒）
    uint16_t rd_length;                 // 资源数据长度，以字节为单位，表示rdata字段的长度
    union ResourceData rd_data;         // 资源数据内容，根据type字段的不同，存储不同类型的资源数据
    struct DNS_resource_record* next;   // 指向下一个资源记录的指针，用于形成链表结构
} Dns_rr;

// DNS 报文结构体
typedef struct DNS_mes {
    Dns_Header* header;
    Dns_Question* question;
    Dns_rr* answer;
    Dns_rr* authority;
    Dns_rr* additional;
} Dns_Mes;