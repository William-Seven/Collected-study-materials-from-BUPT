#pragma once
#include"DNS_cache.h"

#define MAX_SIZE 65536

typedef struct node
{
    uint8_t IP[4];      // 存储IPv4地址,四个十进制数
    uint16_t val[37];   // 域名中的每个字符的编号num，val[num]存放读入某字符时，该结点的编号,一个一个字符去对应,0-9对应0-9,a-z对应10-35,.对应36,-对应37
    uint8_t isEnd;      // 标志节点是否为一个域名的结束节点，是则对应的IP地址有效
    uint16_t father;    // 存储父节点下标，字典树可能是多叉树，但是每个节点只能有一个父亲
}trie_node; // 字典树节点的结构体定义

trie_node Trie[MAX_SIZE];   // 字典树的节点数组声明
int list_size;          // 字典树当前节点数量

/**
 * @brief 提取字符串形式的IPv4地址，转换为整数数组
 *
 * @param IP 存储转换后的IP地址的数组
 * @param address 字符串形式的IPv4地址，如"192.168.1.1"
 */
void TranIP(uint8_t* IP, char* address);

/**
 * @brief 根据字符获取其对应的编号
 *
 * @param val 输入字符的ASCII值
 * @return int 字符对应的编号，0-9返回0-9，a-z返回10-35，'.'返回36，'-'返回37，未知字符返回-1
 */
int getnum(uint8_t val);

/**
 * @brief 向字典树中插入域名和对应的IP地址
 *
 * @param IP IPv4地址的数组表示
 * @param domain 要插入的域名字符串
 */
void insert_node(uint8_t* IP, char* domain);

/**
 * @brief 查询字典树中是否存在指定的域名，并输出其对应的IP地址
 *
 * @param domain 要查询的域名字符串
 * @return int 如果存在该域名，返回1；否则返回0
 */
int query_node(char* domain,uint8_t* ip_addr);