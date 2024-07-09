#pragma once

#define MAX_NUM 65535     // �ֵ������������
#define MAX_SIZE 300      // ������󳤶�
#define MAX_CACHE 100     // �����������
#define PORT 53           // �����˿ں�
#define BUFFER_SIZE 1500  // DNS���ĵ����ߴ�
#define ID_LIST_SIZE 128  // IDӳ����С
#define ID_EXPIRE_TIME 4  // ID����ʱ��

/* Resource Record���� */
#define RR_A 1
#define RR_CNAME 5
#define RR_SOA 6
#define RR_PTR 12
#define RR_MX 15
#define RR_TXT 16
#define RR_AAAA 28