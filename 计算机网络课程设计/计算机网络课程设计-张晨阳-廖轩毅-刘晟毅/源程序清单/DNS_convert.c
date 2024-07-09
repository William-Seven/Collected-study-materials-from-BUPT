/*
本文件用于实现DNS报文结构体与字串之间的转换等报文操作
*/

#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "DNS_convert.h"
#include "DNS_config.h"
#include "DNS_print.h"

// 从缓冲区中获取指定数量的位（8, 16, 32）并返回相应的值
size_t read_bits(uint8_t** buffer, int bits) {
    if (bits == 8) {
        uint8_t val;
        memcpy(&val, *buffer, 1);
        *buffer += 1;
        return val;
    }
    if (bits == 16) {
        uint16_t val;
        memcpy(&val, *buffer, 2);
        *buffer += 2;
        return ntohs(val); // 网络字节序转换为主机字节序
    }
    if (bits == 32) {
        uint32_t val;
        memcpy(&val, *buffer, 4);
        *buffer += 4;
        return ntohl(val); // 网络字节序转换为主机字节序
    }
}

// 解析收到的DNS报文并存储到msg结构体中
void string_to_dnsstruct(Dns_Mes* pmsg, uint8_t* buffer, uint8_t* start) {
    // 开辟空间
    pmsg->header = malloc(sizeof(Dns_Header));
    pmsg->question = malloc(sizeof(Dns_Question));
    pmsg->answer = malloc(sizeof(Dns_rr));

    if (debug_mode == 1)
        printf("收到的报文如下：\n");

    // 获取报文头
    buffer = get_dnsheader(pmsg, buffer);  // buffer指向读取完报头后的地址
    if(debug_mode==1)
        print_header(pmsg);

    // 获取询问内容
    buffer = get_dnsquestion(pmsg, buffer, start);  // buffer指向读取完询问内容后的地址
    if (debug_mode==1)
        print_question(pmsg);

    // 获取应答内容
    buffer = get_dnsanswer(pmsg, buffer, start);  // buffer指向读取完应答内容后的地址
    if (debug_mode==1)
        print_answer(pmsg);
}

// 从缓冲区中读取DNS报文头信息并存储到msg结构体中
uint8_t* get_dnsheader(Dns_Mes* msg, uint8_t* buffer) {
    msg->header->id = read_bits(&buffer, 16); // 获取ID

    uint16_t val = read_bits(&buffer, 16); // 获取标志字段

    // 解析标志字段的各个部分
    msg->header->qr = (val & QR_MASK) >> 15;
    msg->header->opcode = (val & OPCODE_MASK) >> 11;
    msg->header->aa = (val & AA_MASK) >> 10;
    msg->header->tc = (val & TC_MASK) >> 9;
    msg->header->rd = (val & RD_MASK) >> 8;
    msg->header->ra = (val & RA_MASK) >> 7;
    msg->header->rcode = (val & RCODE_MASK) >> 0;

    // 获取问题数、回答数、权威记录数、附加记录数
    msg->header->qdcount = read_bits(&buffer, 16);
    msg->header->ancount = read_bits(&buffer, 16);
    msg->header->nscount = read_bits(&buffer, 16);
    msg->header->arcount = read_bits(&buffer, 16);

    return buffer;
}

// 从缓冲区中读取DNS查询问题并存储到msg结构体中
uint8_t* get_dnsquestion(Dns_Mes* msg, uint8_t* buffer, uint8_t* start) {
    int i;
    for (i = 0; i < msg->header->qdcount; ++i) {
        char name[DNS_RR_NAME_MAX_SIZE] = { 0 };
        Dns_Question* p = malloc(sizeof(Dns_Question));

        // 从缓冲区中获取查询域名
        buffer = get_domain(buffer, name, start);

        // 分配内存并复制域名
        p->q_name = malloc(strlen(name) + 1);
        memcpy(p->q_name, name, strlen(name) + 1);

        p->q_type = read_bits(&buffer, 16); // 获取查询类型
        p->q_class = read_bits(&buffer, 16); // 获取查询类

        // 将新问题插入到问题链表的头部
        p->next = msg->question;
        msg->question = p;
    }

    return buffer;
}

// 从缓冲区中读取DNS回答信息并存储到msg结构体中
uint8_t* get_dnsanswer(Dns_Mes* msg, uint8_t* buffer, uint8_t* start) {
    int i;
    for (i = 0; i < msg->header->ancount; ++i) {
        char name[DNS_RR_NAME_MAX_SIZE] = { 0 };
        Dns_rr* p = malloc(sizeof(Dns_rr));

        // 从缓冲区中获取回答域名
        buffer = get_domain(buffer, name, start);

        // 分配内存并复制域名
        p->name = malloc(strlen(name) + 1);
        memcpy(p->name, name, strlen(name) + 1);

        p->type = read_bits(&buffer, 16); // 获取资源记录类型
        p->rr_class = read_bits(&buffer, 16); // 获取资源记录类
        p->ttl = read_bits(&buffer, 32); // 获取TTL值
        p->rd_length = read_bits(&buffer, 16); // 获取资源数据长度

        // 根据不同的类型进行处理资源数据
        switch (p->type) {
            case DNS_TYPE_A:    // IPv4地址
                for (int j = 0; j < 4; j++) {
                    p->rd_data.a_record.IP_addr[j] = read_bits(&buffer, 8);
                }
                break;
            case DNS_TYPE_AAAA: // IPv6地址
                for (int j = 0; j < 16; j++) {
                    p->rd_data.aaaa_record.IP_addr[j] = read_bits(&buffer, 8);
                }
                break;
            case DNS_TYPE_CNAME: // CNAME记录
                p->rd_data.cname_record.cname = malloc(p->rd_length + 1);
                memcpy(p->rd_data.cname_record.cname, buffer, p->rd_length);
                p->rd_data.cname_record.cname[p->rd_length] = '\0';
                buffer += p->rd_length;
                break;
            case DNS_TYPE_MX: // MX记录
                p->rd_data.mx_record.preference = read_bits(&buffer, 16);
                p->rd_data.mx_record.exchange = malloc(p->rd_length - 2 + 1);
                buffer = get_domain(buffer, p->rd_data.mx_record.exchange, start);
                break;
            case DNS_TYPE_TXT: // TXT记录
                p->rd_data.txt_record.text = malloc(p->rd_length + 1);
                memcpy(p->rd_data.txt_record.text, buffer, p->rd_length);
                p->rd_data.txt_record.text[p->rd_length] = '\0';
                buffer += p->rd_length;
                break;
            case DNS_TYPE_SOA: // SOA记录
                p->rd_data.soa_record.MName = malloc(strlen(buffer) + 1);
                buffer = get_domain(buffer, p->rd_data.soa_record.MName, start);
                p->rd_data.soa_record.RName = malloc(strlen(buffer) + 1);
                buffer = get_domain(buffer, p->rd_data.soa_record.RName, start);
                p->rd_data.soa_record.serial = read_bits(&buffer, 32);
                p->rd_data.soa_record.refresh = read_bits(&buffer, 32);
                p->rd_data.soa_record.retry = read_bits(&buffer, 32);
                p->rd_data.soa_record.expire = read_bits(&buffer, 32);
                p->rd_data.soa_record.minimum = read_bits(&buffer, 32);
                break;
            default:    // 其他类型的记录
                buffer += p->rd_length; // 跳过不支持的资源数据
                break;
        }

        // 将新回答插入到回答链表的头部
        p->next = msg->answer;
        msg->answer = p;
    }
    return buffer;
}

// 从缓冲区中获取域名
uint8_t* get_domain(uint8_t* buffer, char* name, uint8_t* start) {
    uint8_t* ptr = buffer;
    int i = 0, j = 0;
    int len = 0;

    // 若第一个字节的前2位为11，则表示指针，后14位为偏移量，跳转到DNS报文段起始地址 + 偏移量处
    if (*ptr >= 0xc0) {
        uint16_t offset = *ptr;
        offset &= 0x3f;
        offset <<= 8;
        offset += *(ptr + 1);  // 获取后14位偏移量
        get_domain(start + offset, name, start);
        return buffer + 2;
    }

    while (1) {
        uint8_t val = *ptr;
        ptr++;

        // 读到00或指针，则结束读入域名
        if (val == 0 || val >= 0xc0) {
            return ptr;
        }

        // 若此时待读字符数为0，则开始读入字符
        else if (len == 0) {
            len = val;
            if (i != 0) {
                name[i++] = '.';
            }
        }
        else if (len != 0) {
            name[i++] = val;
            len--;
        }
    }

    if (*ptr >= 0xc0) {
        char name2[DNS_RR_NAME_MAX_SIZE] = { 0 };
        uint16_t offset = (*ptr & 0x3f) << 8 + *(ptr + 1);  // 获取后14位偏移量
        uint16_t* end = get_domain(start + offset, name, start);
        for (j = 0; j < strlen(name2); j++) {
            name[i + j] = name2[j];
        }
        ptr += 2;
    } else if (*ptr == 0) {
        ptr++;
    }

    return ptr;
}

// 将指定数量的位（8, 16, 32）设置到缓冲区中
void write_bits(uint8_t** buffer, int bits, int value) {
    if (bits == 8) {
        **buffer = (uint8_t)value;
        (*buffer)++;
    }
    if (bits == 16) {
        uint16_t val = htons((uint16_t)value);
        memcpy(*buffer, &val, 2);
        *buffer += 2;
    }
    if (bits == 32) {
        uint32_t val = htonl(value);
        memcpy(*buffer, &val, 4);
        *buffer += 4;
    }
}

// 组装将要发出的DNS报文
uint8_t* dnsstruct_to_string(Dns_Mes* pmsg, uint8_t* buffer, uint8_t* ip_addr) {
    uint8_t* start = buffer;

    // 组装报头
    buffer = set_dnsheader(pmsg, buffer, ip_addr);
    // 组装询问
    buffer = set_dnsquestion(pmsg, buffer);
    // 组装回答
    buffer = set_dnsanswer(pmsg, buffer, ip_addr);

    return buffer;
}

// 将DNS报文头信息转换为网络字节序并存储到缓冲区中
uint8_t* set_dnsheader(Dns_Mes* msg, uint8_t* buffer, uint8_t* ip_addr) {
    Dns_Header* header = msg->header;
    header->qr = 1;       // 设置为回答报文
    header->aa = 1;       // 设置为权威域名服务器
    header->ra = 1;       // 设置为可用递归
    header->ancount = 1;  // 设置回答数为1

    if (ip_addr[0] == 0 && ip_addr[1] == 0 && ip_addr[2] == 0 && ip_addr[3] == 0) {
        // 若IP地址为0.0.0.0，表示该域名被屏蔽
        header->rcode = 3;  // 名字错误
    } else {
        header->rcode = 0;  // 无差错
    }

    write_bits(&buffer, 16, header->id); // 设置ID

    int flags = 0;
    // 设置标志字段的各个部分
    flags |= (header->qr << 15) & QR_MASK;
    flags |= (header->opcode << 11) & OPCODE_MASK;
    flags |= (header->aa << 10) & AA_MASK;
    flags |= (header->tc << 9) & TC_MASK;
    flags |= (header->rd << 8) & RD_MASK;
    flags |= (header->ra << 7) & RA_MASK;
    flags |= (header->rcode << 0) & RCODE_MASK;

    write_bits(&buffer, 16, flags); // 设置标志字段
    write_bits(&buffer, 16, header->qdcount); // 设置问题数
    write_bits(&buffer, 16, header->ancount); // 设置回答数
    write_bits(&buffer, 16, header->nscount); // 设置权威记录数
    write_bits(&buffer, 16, header->arcount); // 设置附加记录数

    return buffer;
}

// 将DNS查询问题转换为网络字节序并存储到缓冲区中
uint8_t* set_dnsquestion(Dns_Mes* msg, uint8_t* buffer) {
    for (int i = 0; i < msg->header->qdcount; i++) {
        Dns_Question* p = msg->question;
        buffer = set_domain(buffer, p->q_name); // 设置域名

        write_bits(&buffer, 16, p->q_type); // 设置查询类型
        write_bits(&buffer, 16, p->q_class); // 设置查询类

        p = p->next;
    }
    return buffer;
}

// 将DNS回答信息转换为网络字节序并存储到缓冲区中
uint8_t* set_dnsanswer(Dns_Mes* msg, uint8_t* buffer, uint8_t* ip_addr) {
    int i;

    buffer = set_domain(buffer, msg->question->q_name);

    write_bits(&buffer, 16, 1);  // type
    write_bits(&buffer, 16, 1);  // rr_class
    write_bits(&buffer, 32, 4);  // ttl
    write_bits(&buffer, 16, 4);  // rd_length

    for (i = 0; i < 4; i++) {
        *buffer = ip_addr[i];
        buffer++;
    }

    return buffer;
}

// 将域名转换为网络字节序并存储到缓冲区中
uint8_t* set_domain(uint8_t* buffer, char* name) {
    uint8_t* ptr = name;
    char tmp[DNS_RR_NAME_MAX_SIZE] = { 0 };
    int i = 0;

    uint8_t* s = buffer;

    while (1) {
        if (*ptr == 0) {
            *buffer = i;
            buffer++;
            memcpy(buffer, tmp, i);
            buffer += i;

            *buffer = 0;
            buffer++;
            break;
        } else if (*ptr != '.') {
            tmp[i++] = *ptr;
        } else if (*ptr == '.') {
            *buffer = i;
            buffer++;
            memcpy(buffer, tmp, i);
            buffer += i;
            memset(tmp, 0, sizeof(tmp));
            i = 0;
        }
        ptr++;
    }

    return buffer;
}

// 释放DNS报文结构体所占的内存
void free_message(Dns_Mes* msg) {
    free(msg->header);

    Dns_Question* p = msg->question;
    while (p) {
        Dns_Question* tmp = p;
        p = p->next;
        free(tmp);
    }

    Dns_rr* q = msg->answer;
    while (q) {
        Dns_Question* tmp = q;
        q = q->next;
        free(tmp);
    }

    free(msg);
}