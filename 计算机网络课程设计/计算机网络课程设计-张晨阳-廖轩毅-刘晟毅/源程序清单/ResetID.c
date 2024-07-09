#include"ResetID.h"

uint16_t reset_id(uint16_t user_id, struct sockaddr_in client_address) {
    uint16_t i;
    time_t current_time = time(NULL); // ֻ����һ�� time() ������������ϵͳ����
    for (i = 0; i < MAX_ID_SIZE; i++) {
        if (ID_list[i].expire_time < current_time) { // ���ID�Ƿ��ѹ���
            ID_list[i].user_id = user_id;
            ID_list[i].client_address = client_address;
            ID_list[i].expire_time = ID_EXPIRE_TIME + current_time;
            break; // ���ҵ���һ������ID��������ֵ����ֹѭ��
        }
    }
    if (i == MAX_ID_SIZE) {
        return UINT16_MAX; // ���û�п��õ�ID���������ֵ��ʾʧ��
    }
    return i; // ���ط���ID������λ��
}

void init_ID_list() {
    for (int i = 0; i < MAX_ID_SIZE; i++)
    {
        ID_list[i].user_id = 0;
        ID_list[i].expire_time = 0;
        memset(&(ID_list[i].client_address), 0, sizeof(struct sockaddr_in));
    }
}