#pragma once
#include "DNS_cache.h"

#define MAX_ID_SIZE 200   //ID映射表大小
#define ID_EXPIRE_TIME 4  // ID过期时间

typedef struct {
    uint16_t user_id;           // 用户ID
    time_t expire_time;         // 过期时间
    struct sockaddr_in client_address; // 客户端地址
} ClientSession;

ClientSession ID_list[MAX_ID_SIZE];  // 存储客户端会话信息的数组

uint16_t reset_id(uint16_t user_id, struct sockaddr_in client_address);
void init_ID_list();