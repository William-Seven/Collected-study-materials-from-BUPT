#pragma once
#include "DNS_cache.h"

#define MAX_ID_SIZE 200   //IDӳ����С
#define ID_EXPIRE_TIME 4  // ID����ʱ��

typedef struct {
    uint16_t user_id;           // �û�ID
    time_t expire_time;         // ����ʱ��
    struct sockaddr_in client_address; // �ͻ��˵�ַ
} ClientSession;

ClientSession ID_list[MAX_ID_SIZE];  // �洢�ͻ��˻Ự��Ϣ������

uint16_t reset_id(uint16_t user_id, struct sockaddr_in client_address);
void init_ID_list();