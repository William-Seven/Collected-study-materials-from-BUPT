/*
本文件用于实现打印 DNS 报文的功能
*/

#include "DNS_print.h"
#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>

// ANSI color codes
#define RED "\x1B[31m"
#define GREEN "\x1B[32m"
#define YELLOW "\x1B[33m"
#define BLUE "\x1B[34m"
#define RESET "\x1B[0m"

void print_dstring(char* pstring, unsigned int length) {}

void print_header(Dns_Mes* msg) {
    printf(YELLOW"----------------------------header----------------------------\n" RESET);
    printf("ID = %d\n", msg->header->id);
    printf("qr = %d, ", msg->header->qr);
    printf("opcode = %d\n", msg->header->opcode);
    printf("aa = %d, ", msg->header->aa);
    printf("tc = %d, ", msg->header->tc);
    printf("rd = %d, ", msg->header->rd);
    printf("ra = %d\n", msg->header->ra);
    printf("z = %d, ", msg->header->z);
    printf("rcode = %d\n", msg->header->rcode);
    printf("qdCount = %d\n", msg->header->qdcount);
    printf("anCount = %d\n", msg->header->ancount);
    printf("nsCount = %d\n", msg->header->nscount);
    printf("arCount = %d\n", msg->header->arcount);
}

void print_question(Dns_Mes* msg) {
    printf(YELLOW"----------------------------question--------------------------\n" RESET);
    printf("domain: %s\n", msg->question->q_name);
    printf("query type: %d\n", msg->question->q_type);
    printf("query class: %d\n", msg->question->q_class);
}

void print_answer(Dns_Mes* msg) {
    if (msg->header->ancount == 0) {
        printf("\n");
    } else {
        printf(YELLOW"----------------------------answer----------------------------\n" RESET);
        printf("domain: %s\n", msg->answer->name);
        printf("answer type: %d\n", msg->answer->type);
        printf("resource record class: %d\n", msg->answer->rr_class);
        printf("time to live: %d\n", msg->answer->ttl);
        printf("record length: %d\n", msg->answer->rd_length);

        /* IPv4*/
        if (msg->answer->type == DNS_TYPE_A) {
            printf("A Record: ");
            int j;
            for (j = 0; j < 3; j++) {
                printf("%d.", msg->answer->rd_data.a_record.IP_addr[j]);
            }
            printf("%d", msg->answer->rd_data.a_record.IP_addr[3]);
        }
        printf("\n\n");
    }
}