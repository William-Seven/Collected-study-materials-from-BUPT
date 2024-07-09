#include "DNS_cache.h"

// ANSI color codes
#define RED "\x1B[31m"
#define GREEN "\x1B[32m"
#define YELLOW "\x1B[33m"
#define BLUE "\x1B[34m"
#define RESET "\x1B[0m"

int cache_size = 0;   //cache���浱ǰ��С�������ж��Ƿ���Ҫ�����滻

// ��ʼ��
void init_cache() {
	head = (lru_cache*)malloc(sizeof(struct nodes));	// ����ͷ����ڴ�
	head->next = NULL;			// ͷ����ʼʱ����һ���ڵ㣨������Ϊ�գ�
	tail = head;
}

// ��ѯ����
int cache_query(uint8_t *ipv4, char* domain) {
	lru_cache *temp = head;  //��ͷ��������

	while (temp->next) {
		//���,˵��������
		if (strcmp(temp->next->domain, domain) == 0) {
			memcpy(ipv4, temp->next->IP, sizeof(temp->next->IP));   // �������е�IP���Ƹ�ipv4
			
			lru_cache* tar = temp->next;
			temp->next = tar->next;
			tar->next = head->next;
			head->next = tar;		// �����еĽڵ��Ƶ�����ͷ������ʾ���ʹ��
			if (debug_mode == 1)
				printf(GREEN"cache hit!\n\n" RESET);

			//printf("cache��������� : %s\n", temp->domain);
			return 1;
		} else {
			temp = temp->next;		// ����������һ���ڵ�
		}
	}
	if (debug_mode == 1)
		printf(RED"cache missed!\n\n" RESET);
	return 0;		// û���ҵ���Ӧ������
}

// �������
void insert_cache(uint8_t ipv4[4], char* domain)
{
	lru_cache* new_cache = (lru_cache*)malloc(sizeof(struct nodes));	// �����½ڵ��ڴ�

	if (cache_size > MAX_CACHE)  //˵��cache����,Ҫ�����滻
		delete_node();

	memcpy(new_cache->IP, ipv4, sizeof(uint8_t) * 4);		// ����IP��ַ
	memcpy(new_cache->domain, domain, strlen(domain) + 1);	// ��������

	cache_size++;

	new_cache->next = head->next;		// ���½ڵ���뵽����ͷ��
	head->next = new_cache;
}

// ɾ�����δʹ�õĽڵ㣨����ĩβ�ڵ㣩
void delete_node()
{
	lru_cache* p = head;
	while (p->next) {
		if (p->next->next == NULL) {
			tail = p->next;
			p->next = NULL;
			free(tail);
			return;
		}
		p = p->next;
	}
	cache_size--;		// �����С��һ
}
