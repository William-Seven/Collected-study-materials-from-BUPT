/*
���ļ����ڶ��� ��ӡ DNS ���ģ��ֽ������ṹ�壩�Ľӿ�
*/

#pragma once

#include "DNS_struct.h"

// ��ӡ DNS �����ֽ���
void print_dstring(char* pstring, unsigned int length);

// ��ӡheader
void print_header(Dns_Mes* msg);

// ��ӡquestion
void print_question(Dns_Mes* msg);

// ��ӡanswer��RR��
void print_answer(Dns_Mes* msg);