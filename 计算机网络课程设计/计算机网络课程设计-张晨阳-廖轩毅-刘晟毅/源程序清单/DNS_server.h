#pragma once
#define DNS_PORT 53
#define BUFFER_SIZE 1500  // DNS���ĵ����ߴ�
#define ID_LIST_SIZE 128  // IDӳ����С

#include"DNS_config.h"
#include"DNS_Trie.h"
#include"ResetID.h"

int socketMode;           // ����/������ģʽ
int clientSocket;         // �ͻ���socket
int serverSocket;         // �����socket
struct sockaddr_in clientAddress;
struct sockaddr_in serverAddress;
int addressLength;

int clientPort;           // �ͻ��˶˿ں�
char* dnsServerAddress;   // Զ��������BUPT��DNS��������

int islisten;

void initializeSocket();
void closeSocketServer();
void setNonBlockingMode();
void setBlockingMode();
void receive_client();
void receive_server();