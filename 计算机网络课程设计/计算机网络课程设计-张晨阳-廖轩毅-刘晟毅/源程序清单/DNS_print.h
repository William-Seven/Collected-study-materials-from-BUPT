/*
本文件用于定义 打印 DNS 报文（字节流、结构体）的接口
*/

#pragma once

#include "DNS_struct.h"

// 打印 DNS 报文字节流
void print_dstring(char* pstring, unsigned int length);

// 打印header
void print_header(Dns_Mes* msg);

// 打印question
void print_question(Dns_Mes* msg);

// 打印answer（RR）
void print_answer(Dns_Mes* msg);