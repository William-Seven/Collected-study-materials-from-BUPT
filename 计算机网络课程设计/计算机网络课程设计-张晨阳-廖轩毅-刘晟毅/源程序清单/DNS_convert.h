/*
本文件用于定义DNS报文结构体与字串的相互转换的接口
*/

#pragma once
#include "DNS_struct.h"

// 用于获取DNS报文头各值的掩码
static const uint32_t QR_MASK = 0x8000;
static const uint32_t OPCODE_MASK = 0x7800;
static const uint32_t AA_MASK = 0x0400;
static const uint32_t TC_MASK = 0x0200;
static const uint32_t RD_MASK = 0x0100;
static const uint32_t RA_MASK = 0x0080;
static const uint32_t RCODE_MASK = 0x000F;

// DNS 报文字串转换为 DNS 结构体
void string_to_dnsstruct(Dns_Mes* pmsg, uint8_t* buffer, uint8_t* start);

// 读取指定位数
size_t read_bits(uint8_t** buffer, int bits);

// 从字串获取header
uint8_t* get_dnsheader(Dns_Mes* msg, uint8_t* buffer);

// 从字串获取question
uint8_t* get_dnsquestion(Dns_Mes* msg, uint8_t* buffer, uint8_t* start);

// 从字串获取 answer
uint8_t* get_dnsanswer(Dns_Mes* msg, uint8_t* buffer, uint8_t* start);

// 从字串获取域名Name
uint8_t* get_domain(uint8_t* buffer, char* name, uint8_t* start);

// DNS 结构体转换为字串
uint8_t* dnsstruct_to_string(Dns_Mes* pmsg, uint8_t* buffer, uint8_t* ip_addr);

// 写入指定位数
void write_bits(uint8_t** buffer, int bits, int value);

// 将header写入字串
uint8_t* set_dnsheader(Dns_Mes* msg, uint8_t* buffer, uint8_t* ip_addr);

// 将question写入字串
uint8_t* set_dnsquestion(Dns_Mes* msg, uint8_t* buffer);

// 将answer写入字串
uint8_t* set_dnsanswer(Dns_Mes* msg, uint8_t* buffer, uint8_t* ip_addr);

// 设置域名
uint8_t* set_domain(uint8_t* buffer, char* name);

// 释放空间
void free_message(Dns_Mes* msg);