#include "DNS_Trie.h"

// ANSI color codes
#define RED "\x1B[31m"
#define GREEN "\x1B[32m"
#define YELLOW "\x1B[33m"
#define BLUE "\x1B[34m"
#define RESET "\x1B[0m"

// IP��ַת�������ַ�����ʽ��IP��ַת��Ϊ����������ʽ�洢
void TranIP(uint8_t* IP, char* address) {
	int len = strlen(address);
	int number = 0;
	int count = 0;

	for (int i = 0; i < len; i++) {
        // ������ǵ㣬��˵��δ���ָ�
		if (address[i] != '.') 
			number = number * 10 + (address[i] - '0');  // ����IP�е�ÿһ������
		else {      // ����ǵ㣬��˵��Ҫ�ָ���
			IP[count++] = number;  // �������������ִ���IP����,��ʹ����++
			number = 0;            // ����number��׼��������һ��
		}
	}

	IP[3] = number; //���һ��IP��ַ����û��
}

// �ַ�ת��Ϊ��ֵ���������е��ַ�ת��Ϊ��Ӧ����ֵ
int getnum(uint8_t val)
{
    // ����ֱ��ת��Ϊ��Ӧ����ֵ
    if (val >= '0' && val <= '9')
        return val - '0';

    // ͳһתΪСд��ĸ����
    if (val >= 'A' && val <= 'Z')
        val += 'a' - 'A';

    // ��ĸת��Ϊ��Ӧ����ֵ��a=10, b=11, ..., z=35��
    if(val>='a'&&val<='z')
        return val - 'a' + 10;

    // �����ַ�
    switch (val) {
    case '.':
        return 36;
    case '-':
        return 37;
    default:
        return -1;  // ���û��ƥ�䵽�κ���֪�ַ������ش������
    }
}

// ����ڵ�
void insert_node(uint8_t* IP, char* domain)
{
    int len = strlen(domain);
    int index = 0;

    for (int i = 0; i < len; i++) {
        int num = getnum(domain[i]);   // ��ȡ��ǰ�ַ���Ӧ����ֵ
        
        // �����ǰ�ڵ㲻����
        if (Trie[index].val[num] == 0)
            Trie[index].val[num] = ++list_size;     //�����½ڵ�

        Trie[Trie[index].val[num]].father = index;  //���ڵ㸳ֵ
        index = Trie[index].val[num];               //�ƶ�����һ���ڵ�
    }

    for (int i = 0; i < 4; i++)
        Trie[index].IP[i] = IP[i];  //���ս�������IP

    Trie[index].isEnd = 1;      // ��ǵ�ǰ�ڵ�Ϊһ�������Ľ����ڵ�
}

// ��ѯ�ڵ�
int query_node(char* domain,uint8_t* ip_addr)
{
    int len = strlen(domain);
    int index = 0;

    for (int i = 0; i < len; i++) {
        int num = getnum(domain[i]);

        if (Trie[index].val[num] == 0) {
            if (debug_mode == 1)
                printf("%d node not exit!\n\n", num);
            return 0;
        }
        index = Trie[index].val[num];
    }

    if (Trie[index].isEnd == 0) {
        if (debug_mode == 1)
            printf("���ս�ڵ�!\n\n");
        return 0;
    }

    memcpy(ip_addr, Trie[index].IP, 4);
    insert_cache(Trie[index].IP, domain);

    if (debug_mode == 1)
        printf(GREEN"Local hit!  Cache updated!\n\n"RESET);

    return 1;
}
