#include"DNS_server.h"

// ANSI ��ɫ���룬�����ڿ���̨�����ͬ��ɫ���ı���
#define RED "\x1B[31m"
#define GREEN "\x1B[32m"
#define YELLOW "\x1B[33m"
#define BLUE "\x1B[34m"
#define RESET "\x1B[0m"

// �ͻ��˶˿ں͵�ַ���ȱ���
int clientPort;
int addressLength;
// DNS��������IP��ַ
char* dnsServerAddress = "10.3.9.4";

void initializeSocket()
{
        addressLength = sizeof(struct sockaddr_in);
        // ��ʼ��Winsock
        WORD wVersionRequested = MAKEWORD(2, 2);
        WSADATA wsaData;
        if (WSAStartup(wVersionRequested, &wsaData) != 0) {
            fprintf(stderr, "WSAStartup failed: %d\n", WSAGetLastError());
            exit(1);
        }

        // �����ͻ��˺ͷ�����socket
        clientSocket = socket(AF_INET, SOCK_DGRAM, 0);
        if (clientSocket == INVALID_SOCKET) {
            fprintf(stderr, "Error opening client socket: %d\n", WSAGetLastError());
            WSACleanup();
            exit(1);
        }

        serverSocket = socket(AF_INET, SOCK_DGRAM, 0);
        if (serverSocket == INVALID_SOCKET) {
            fprintf(stderr, "Error opening server socket: %d\n", WSAGetLastError());
            closesocket(clientSocket);
            WSACleanup();
            exit(1);
        }

        // ��ʼ����ַ�ṹ
        memset(&clientAddress, 0, sizeof(clientAddress));
        clientAddress.sin_family = AF_INET;
        clientAddress.sin_addr.s_addr = INADDR_ANY;
        clientAddress.sin_port = htons(DNS_PORT);

        memset(&serverAddress, 0, sizeof(serverAddress));
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_addr.s_addr = inet_addr(dnsServerAddress);
        serverAddress.sin_port = htons(DNS_PORT);

        // ���ö˿�����
        const int REUSEADDR_OPTION = 1;
        if (setsockopt(clientSocket, SOL_SOCKET, SO_REUSEADDR, (char*)&REUSEADDR_OPTION, sizeof(int)) == SOCKET_ERROR) {
            fprintf(stderr, "setsockopt(SO_REUSEADDR) failed: %d\n", WSAGetLastError());
            closesocket(clientSocket);
            closesocket(serverSocket);
            WSACleanup();
            exit(1);
        }

        // �󶨿ͻ���socket
        if (bind(clientSocket, (struct sockaddr*)&clientAddress, sizeof(clientAddress)) == SOCKET_ERROR) {
            fprintf(stderr, "Bind failed with error: %d\n", WSAGetLastError());
            closesocket(clientSocket);
            closesocket(serverSocket);
            WSACleanup();
            exit(1);
        }

        // ��ӡ��������Ϣ
        printf("DNS server: %s\n", dnsServerAddress);
        printf("Listening on port %d\n", DNS_PORT);
}

// �ر��׽��ֲ�����Winsock
void closeSocketServer()
{
      closesocket(clientSocket);
      closesocket(serverSocket);
      WSACleanup();
}

// ������ģʽ
void setNonBlockingMode()
{
    // ���Խ��������Ϳͻ����׽�������Ϊ������ģʽ
    if (ioctlsocket(serverSocket, FIONBIO, &socketMode) != 0 ||
        ioctlsocket(clientSocket, FIONBIO, &socketMode) != 0) {
        fprintf(stderr, "Failed to set non-blocking socketMode: %d\n\n", WSAGetLastError());
        closesocket(serverSocket);
        closesocket(clientSocket);
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    // �ڷ�����ģʽ�£�ѭ���������Կͻ��˺ͷ�����������
    while (1) {
        receive_client();  // �������Կͻ��˵�����
        receive_server();  // �������Է�����������
    }
}

// ʹ��WSAPoll��������ģʽ�µ��¼�����
void setBlockingMode()
{
    // ʹ��WSAPoll��������ģʽ�µ��¼�����
    struct pollfd fds[2];           // ���ڴ洢��Ҫ�������׽��ֺ��¼�����
    fds[0].fd = clientSocket;       // ������Ҫ�������׽���
    fds[0].events = POLLIN;         // ָ���������¼�����Ϊ "�ɶ�"�������ݿɶ��������ѽ�����
    fds[1].fd = serverSocket;
    fds[1].events = POLLIN;

    // ѭ���ȴ�ֱ�����¼�����
    while (1) {
        //���� WSAPoll �ȴ� fds ���г����׽����ϵ��¼���-1 ������ʾ���޵ȴ���ֱ�����¼�������
        int ret = WSAPoll(fds, 2, -1);
        if (ret == SOCKET_ERROR) {
            fprintf(stderr, "WSAPoll failed: %d\n", WSAGetLastError());
            closesocket(serverSocket);
            closesocket(clientSocket);
            WSACleanup();
            exit(EXIT_FAILURE);
        } else if (ret > 0) {
            if (fds[0].revents & POLLIN) {
                receive_client(); // ����ͻ����¼�
            }
            if (fds[1].revents & POLLIN) {
                receive_server(); // ����������¼�
            }
        }
    }
}

// �������Կͻ��˵����ݲ����д���
void receive_client() {
    uint8_t buffer[BUFFER_SIZE];      // ���յı���
    uint8_t buffer_new[BUFFER_SIZE];  // �ظ����ͻ��˵ı���
    Dns_Mes msg;                  // ���Ľṹ��
    uint8_t ip_addr[4] = { 0 };         // ��ѯ�����õ���IP��ַ
    int msg_size = -1;                // ���Ĵ�С
    int is_found = 0;                 // �Ƿ�鵽

    msg_size = recvfrom(clientSocket, buffer, sizeof(buffer), 0, (struct sockaddr*)&clientAddress, &addressLength);
    if (debug_mode==1)
        printf(BLUE"received for one message from client!\n\n" RESET);

    if (msg_size >= 0) {
        uint8_t* start = buffer;
        /* �����ͻ��˷�����DNS���ģ����䱣�浽msg�ṹ���� */
        string_to_dnsstruct(&msg, buffer, start);

        /* �ӻ������ */
        is_found = cache_query(ip_addr,msg.question->q_name);

        /* ��cacheδ�鵽�����host�ļ����� */
        if (is_found == 0) {
            if (debug_mode == 1)
                printf(RED"Address not found in cache.  Try to find in local.\n\n" RESET);

            is_found = query_node(msg.question->q_name, ip_addr);

            /* ��δ�鵽�����Ͻ�Զ��DNS����������*/
            if (is_found == 0) {
                /* ����Ҫ����Զ��DNS�������İ�������ID */
                uint16_t newID = reset_id(msg.header->id, clientAddress);
                memcpy(buffer, &newID, sizeof(uint16_t));
                if (newID == ID_LIST_SIZE) {
                        printf("ID list is full.\n\n");
                } else {
                    islisten = 1;
                    sendto(serverSocket, buffer, msg_size, 0, (struct sockaddr*)&serverAddress, addressLength);
                    if (debug_mode == 1)
                        printf(RED"Address not found in local.  Send to Remote Server.\n\n" RESET);
                }
                return;
            }
        }

        uint8_t* end;
        end =dnsstruct_to_string(&msg, buffer_new, ip_addr);

        int len = end - buffer_new;

        /* ��DNSӦ���ķ��ؿͻ��� */
        sendto(clientSocket, buffer_new, len, 0, (struct sockaddr*)&clientAddress, addressLength);

        if (log_mode == 1) {
            write_log(msg.question->q_name, ip_addr);
        }
    }
}

// ��������Զ��DNS����������Ӧ��ת�����ͻ���
void receive_server() {
    uint8_t buffer[BUFFER_SIZE];  // ���յı���
    Dns_Mes msg;
    int msg_size = -1;  // ���Ĵ�С

    /* ����Զ��DNS������������DNSӦ���� */
    if (islisten == 1) {
        msg_size = recvfrom(serverSocket, buffer, sizeof(buffer), 0, (struct sockaddr*)&serverAddress, &addressLength);
        if (debug_mode == 1)
            printf(BLUE"received for one message from remote server!\n\n" RESET);
        string_to_dnsstruct(&msg, buffer, buffer);
    }

    /* ��DNSӦ����ת���ؿͻ��� */
    if (msg_size > 0 && islisten == 1) {
        /* IDת�� */
        uint16_t ID = msg.header->id;
        uint16_t old_ID = htons(ID_list[ID].user_id);
        memcpy(buffer, &old_ID, sizeof(uint16_t));  // �Ѵ����ؿͻ��˵İ�ID�Ļ�ԭID

        struct sockaddr_in ca = ID_list[ID].client_address;
        ID_list[ID].expire_time = 0;

        sendto(clientSocket, buffer, msg_size, 0, (struct sockaddr*)&clientAddress, addressLength);
        islisten = 0;

        if (log_mode == 1) {
            write_log(msg.question->q_name, NULL);
        }
    }
}