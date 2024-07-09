#include "DNS_Trie.h"

// ANSI color codes
#define RED "\x1B[31m"
#define GREEN "\x1B[32m"
#define YELLOW "\x1B[33m"
#define BLUE "\x1B[34m"
#define RESET "\x1B[0m"

// IP地址转换：将字符串形式的IP地址转换为整数数组形式存储
void TranIP(uint8_t* IP, char* address) {
	int len = strlen(address);
	int number = 0;
	int count = 0;

	for (int i = 0; i < len; i++) {
        // 如果不是点，则说明未到分割
		if (address[i] != '.') 
			number = number * 10 + (address[i] - '0');  // 解析IP中的每一段数字
		else {      // 如果是点，则说明要分割了
			IP[count++] = number;  // 将解析出的数字存入IP数组,先使用再++
			number = 0;            // 重置number，准备解析下一段
		}
	}

	IP[3] = number; //最后一段IP地址后面没点
}

// 字符转换为数值：将域名中的字符转换为对应的数值
int getnum(uint8_t val)
{
    // 数字直接转换为对应的数值
    if (val >= '0' && val <= '9')
        return val - '0';

    // 统一转为小写字母处理
    if (val >= 'A' && val <= 'Z')
        val += 'a' - 'A';

    // 字母转换为对应的数值（a=10, b=11, ..., z=35）
    if(val>='a'&&val<='z')
        return val - 'a' + 10;

    // 特殊字符
    switch (val) {
    case '.':
        return 36;
    case '-':
        return 37;
    default:
        return -1;  // 如果没有匹配到任何已知字符，返回错误代码
    }
}

// 插入节点
void insert_node(uint8_t* IP, char* domain)
{
    int len = strlen(domain);
    int index = 0;

    for (int i = 0; i < len; i++) {
        int num = getnum(domain[i]);   // 获取当前字符对应的数值
        
        // 如果当前节点不存在
        if (Trie[index].val[num] == 0)
            Trie[index].val[num] = ++list_size;     //创建新节点

        Trie[Trie[index].val[num]].father = index;  //父节点赋值
        index = Trie[index].val[num];               //移动到下一个节点
    }

    for (int i = 0; i < 4; i++)
        Trie[index].IP[i] = IP[i];  //最终结点里面存IP

    Trie[index].isEnd = 1;      // 标记当前节点为一个域名的结束节点
}

// 查询节点
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
            printf("非终结节点!\n\n");
        return 0;
    }

    memcpy(ip_addr, Trie[index].IP, 4);
    insert_cache(Trie[index].IP, domain);

    if (debug_mode == 1)
        printf(GREEN"Local hit!  Cache updated!\n\n"RESET);

    return 1;
}
