#include"DNS_struct.h"
#include"DNS_config.h"

int main(int argc, char* argv[]) {
    /* 初始化系统 */
    init(argc, argv);

    /* 以非阻塞模式运行 */
    if (socketMode == 0) {
        setNonBlockingMode();
    }

    /* 以阻塞模式（poll）运行 */
    if (socketMode == 1) {
        setBlockingMode();
    }

    /* 关闭连接 */
    closeSocketServer();

    return 0;
}