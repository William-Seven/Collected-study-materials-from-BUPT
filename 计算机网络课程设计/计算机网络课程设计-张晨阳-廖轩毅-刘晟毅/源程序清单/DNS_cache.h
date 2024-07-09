#pragma once
#include "DNS_struct.h"
#include "DNS_config.h"

#define MAX_CACHE 100			// cache���ߴ�

//˼�룺����������ʵ��LRU��Խ�Ϸ�Խ����
typedef struct nodes {   
	uint8_t IP[4];						// ʮ����IP��ַ,�ĸ�ʮ������
	char domain[DNS_RR_NAME_MAX_SIZE];  //����
	struct nodes* next;
}lru_cache;	

lru_cache* head;
lru_cache* tail;

// ��ʼ��cache
void init_cache();

// ��cache�в�ѯĳ������
int cache_query(uint8_t* ipv4, char* domain);

// �����µ�������ip
void insert_cache(uint8_t ipv4[4], char* domain);

//ɾ�����ϵ�������ip
void delete_node();
