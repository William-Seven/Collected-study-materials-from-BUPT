#pragma once
#include"DNS_cache.h"

#define MAX_SIZE 65536

typedef struct node
{
    uint8_t IP[4];      // �洢IPv4��ַ,�ĸ�ʮ������
    uint16_t val[37];   // �����е�ÿ���ַ��ı��num��val[num]��Ŷ���ĳ�ַ�ʱ���ý��ı��,һ��һ���ַ�ȥ��Ӧ,0-9��Ӧ0-9,a-z��Ӧ10-35,.��Ӧ36,-��Ӧ37
    uint8_t isEnd;      // ��־�ڵ��Ƿ�Ϊһ�������Ľ����ڵ㣬�����Ӧ��IP��ַ��Ч
    uint16_t father;    // �洢���ڵ��±꣬�ֵ��������Ƕ����������ÿ���ڵ�ֻ����һ������
}trie_node; // �ֵ����ڵ�Ľṹ�嶨��

trie_node Trie[MAX_SIZE];   // �ֵ����Ľڵ���������
int list_size;          // �ֵ�����ǰ�ڵ�����

/**
 * @brief ��ȡ�ַ�����ʽ��IPv4��ַ��ת��Ϊ��������
 *
 * @param IP �洢ת�����IP��ַ������
 * @param address �ַ�����ʽ��IPv4��ַ����"192.168.1.1"
 */
void TranIP(uint8_t* IP, char* address);

/**
 * @brief �����ַ���ȡ���Ӧ�ı��
 *
 * @param val �����ַ���ASCIIֵ
 * @return int �ַ���Ӧ�ı�ţ�0-9����0-9��a-z����10-35��'.'����36��'-'����37��δ֪�ַ�����-1
 */
int getnum(uint8_t val);

/**
 * @brief ���ֵ����в��������Ͷ�Ӧ��IP��ַ
 *
 * @param IP IPv4��ַ�������ʾ
 * @param domain Ҫ����������ַ���
 */
void insert_node(uint8_t* IP, char* domain);

/**
 * @brief ��ѯ�ֵ������Ƿ����ָ������������������Ӧ��IP��ַ
 *
 * @param domain Ҫ��ѯ�������ַ���
 * @return int ������ڸ�����������1�����򷵻�0
 */
int query_node(char* domain,uint8_t* ip_addr);