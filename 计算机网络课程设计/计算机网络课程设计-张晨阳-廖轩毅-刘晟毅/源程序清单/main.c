#include"DNS_struct.h"
#include"DNS_config.h"

int main(int argc, char* argv[]) {
    /* ��ʼ��ϵͳ */
    init(argc, argv);

    /* �Է�����ģʽ���� */
    if (socketMode == 0) {
        setNonBlockingMode();
    }

    /* ������ģʽ��poll������ */
    if (socketMode == 1) {
        setBlockingMode();
    }

    /* �ر����� */
    closeSocketServer();

    return 0;
}