#pragma once
#define DNS_PORT 53
#define BUFFER_SIZE 1500  // DNS报文的最大尺寸
#define ID_LIST_SIZE 128  // ID映射表大小

#include"DNS_config.h"
#include"DNS_Trie.h"
#include"ResetID.h"

int socketMode;           // 阻塞/非阻塞模式
int clientSocket;         // 客户端socket
int serverSocket;         // 服务端socket
struct sockaddr_in clientAddress;
struct sockaddr_in serverAddress;
int addressLength;

int clientPort;           // 客户端端口号
char* dnsServerAddress;   // 远程主机（BUPT的DNS服务器）

int islisten;

void initializeSocket();
void closeSocketServer();
void setNonBlockingMode();
void setBlockingMode();
void receive_client();
void receive_server();