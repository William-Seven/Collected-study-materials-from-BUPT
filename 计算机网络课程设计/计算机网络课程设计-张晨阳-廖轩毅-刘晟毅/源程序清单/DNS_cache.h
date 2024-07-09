#pragma once
#include "DNS_struct.h"
#include "DNS_config.h"

#define MAX_CACHE 100			// cache最大尺寸

//思想：用有序链表实现LRU，越老放越后面
typedef struct nodes {   
	uint8_t IP[4];						// 十进制IP地址,四个十进制数
	char domain[DNS_RR_NAME_MAX_SIZE];  //域名
	struct nodes* next;
}lru_cache;	

lru_cache* head;
lru_cache* tail;

// 初始化cache
void init_cache();

// 在cache中查询某个域名
int cache_query(uint8_t* ipv4, char* domain);

// 插入新的域名及ip
void insert_cache(uint8_t ipv4[4], char* domain);

//删除最老的域名及ip
void delete_node();
