#include"ResetID.h"

uint16_t reset_id(uint16_t user_id, struct sockaddr_in client_address) {
    uint16_t i;
    time_t current_time = time(NULL); // 只调用一次 time() 函数，避免多次系统调用
    for (i = 0; i < MAX_ID_SIZE; i++) {
        if (ID_list[i].expire_time < current_time) { // 检查ID是否已过期
            ID_list[i].user_id = user_id;
            ID_list[i].client_address = client_address;
            ID_list[i].expire_time = ID_EXPIRE_TIME + current_time;
            break; // 在找到第一个过期ID并分配新值后终止循环
        }
    }
    if (i == MAX_ID_SIZE) {
        return UINT16_MAX; // 如果没有可用的ID，返回最大值表示失败
    }
    return i; // 返回分配ID的索引位置
}

void init_ID_list() {
    for (int i = 0; i < MAX_ID_SIZE; i++)
    {
        ID_list[i].user_id = 0;
        ID_list[i].expire_time = 0;
        memset(&(ID_list[i].client_address), 0, sizeof(struct sockaddr_in));
    }
}