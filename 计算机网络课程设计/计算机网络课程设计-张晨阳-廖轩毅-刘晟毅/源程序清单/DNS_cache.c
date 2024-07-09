#include "DNS_cache.h"

// ANSI color codes
#define RED "\x1B[31m"
#define GREEN "\x1B[32m"
#define YELLOW "\x1B[33m"
#define BLUE "\x1B[34m"
#define RESET "\x1B[0m"

int cache_size = 0;   //cache缓存当前大小，用于判断是否需要进行替换

// 初始化
void init_cache() {
	head = (lru_cache*)malloc(sizeof(struct nodes));	// 分配头结点内存
	head->next = NULL;			// 头结点初始时无下一个节点（即链表为空）
	tail = head;
}

// 查询操作
int cache_query(uint8_t *ipv4, char* domain) {
	lru_cache *temp = head;  //表头不存数据

	while (temp->next) {
		//相等,说明命中了
		if (strcmp(temp->next->domain, domain) == 0) {
			memcpy(ipv4, temp->next->IP, sizeof(temp->next->IP));   // 将缓存中的IP复制给ipv4
			
			lru_cache* tar = temp->next;
			temp->next = tar->next;
			tar->next = head->next;
			head->next = tar;		// 将命中的节点移到链表头部，表示最近使用
			if (debug_mode == 1)
				printf(GREEN"cache hit!\n\n" RESET);

			//printf("cache里面的内容 : %s\n", temp->domain);
			return 1;
		} else {
			temp = temp->next;		// 继续遍历下一个节点
		}
	}
	if (debug_mode == 1)
		printf(RED"cache missed!\n\n" RESET);
	return 0;		// 没有找到对应的域名
}

// 插入操作
void insert_cache(uint8_t ipv4[4], char* domain)
{
	lru_cache* new_cache = (lru_cache*)malloc(sizeof(struct nodes));	// 分配新节点内存

	if (cache_size > MAX_CACHE)  //说明cache满了,要进行替换
		delete_node();

	memcpy(new_cache->IP, ipv4, sizeof(uint8_t) * 4);		// 复制IP地址
	memcpy(new_cache->domain, domain, strlen(domain) + 1);	// 复制域名

	cache_size++;

	new_cache->next = head->next;		// 将新节点插入到链表头部
	head->next = new_cache;
}

// 删除最久未使用的节点（链表末尾节点）
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
	cache_size--;		// 缓存大小减一
}
