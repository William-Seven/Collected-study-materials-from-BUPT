/*
���ļ�����ʵ��DNS���Ľṹ�����ִ�֮���ת���ȱ��Ĳ���
*/

#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "DNS_convert.h"
#include "DNS_config.h"
#include "DNS_print.h"

// �ӻ������л�ȡָ��������λ��8, 16, 32����������Ӧ��ֵ
size_t read_bits(uint8_t** buffer, int bits) {
    if (bits == 8) {
        uint8_t val;
        memcpy(&val, *buffer, 1);
        *buffer += 1;
        return val;
    }
    if (bits == 16) {
        uint16_t val;
        memcpy(&val, *buffer, 2);
        *buffer += 2;
        return ntohs(val); // �����ֽ���ת��Ϊ�����ֽ���
    }
    if (bits == 32) {
        uint32_t val;
        memcpy(&val, *buffer, 4);
        *buffer += 4;
        return ntohl(val); // �����ֽ���ת��Ϊ�����ֽ���
    }
}

// �����յ���DNS���Ĳ��洢��msg�ṹ����
void string_to_dnsstruct(Dns_Mes* pmsg, uint8_t* buffer, uint8_t* start) {
    // ���ٿռ�
    pmsg->header = malloc(sizeof(Dns_Header));
    pmsg->question = malloc(sizeof(Dns_Question));
    pmsg->answer = malloc(sizeof(Dns_rr));

    if (debug_mode == 1)
        printf("�յ��ı������£�\n");

    // ��ȡ����ͷ
    buffer = get_dnsheader(pmsg, buffer);  // bufferָ���ȡ�걨ͷ��ĵ�ַ
    if(debug_mode==1)
        print_header(pmsg);

    // ��ȡѯ������
    buffer = get_dnsquestion(pmsg, buffer, start);  // bufferָ���ȡ��ѯ�����ݺ�ĵ�ַ
    if (debug_mode==1)
        print_question(pmsg);

    // ��ȡӦ������
    buffer = get_dnsanswer(pmsg, buffer, start);  // bufferָ���ȡ��Ӧ�����ݺ�ĵ�ַ
    if (debug_mode==1)
        print_answer(pmsg);
}

// �ӻ������ж�ȡDNS����ͷ��Ϣ���洢��msg�ṹ����
uint8_t* get_dnsheader(Dns_Mes* msg, uint8_t* buffer) {
    msg->header->id = read_bits(&buffer, 16); // ��ȡID

    uint16_t val = read_bits(&buffer, 16); // ��ȡ��־�ֶ�

    // ������־�ֶεĸ�������
    msg->header->qr = (val & QR_MASK) >> 15;
    msg->header->opcode = (val & OPCODE_MASK) >> 11;
    msg->header->aa = (val & AA_MASK) >> 10;
    msg->header->tc = (val & TC_MASK) >> 9;
    msg->header->rd = (val & RD_MASK) >> 8;
    msg->header->ra = (val & RA_MASK) >> 7;
    msg->header->rcode = (val & RCODE_MASK) >> 0;

    // ��ȡ���������ش�����Ȩ����¼�������Ӽ�¼��
    msg->header->qdcount = read_bits(&buffer, 16);
    msg->header->ancount = read_bits(&buffer, 16);
    msg->header->nscount = read_bits(&buffer, 16);
    msg->header->arcount = read_bits(&buffer, 16);

    return buffer;
}

// �ӻ������ж�ȡDNS��ѯ���Ⲣ�洢��msg�ṹ����
uint8_t* get_dnsquestion(Dns_Mes* msg, uint8_t* buffer, uint8_t* start) {
    int i;
    for (i = 0; i < msg->header->qdcount; ++i) {
        char name[DNS_RR_NAME_MAX_SIZE] = { 0 };
        Dns_Question* p = malloc(sizeof(Dns_Question));

        // �ӻ������л�ȡ��ѯ����
        buffer = get_domain(buffer, name, start);

        // �����ڴ沢��������
        p->q_name = malloc(strlen(name) + 1);
        memcpy(p->q_name, name, strlen(name) + 1);

        p->q_type = read_bits(&buffer, 16); // ��ȡ��ѯ����
        p->q_class = read_bits(&buffer, 16); // ��ȡ��ѯ��

        // ����������뵽���������ͷ��
        p->next = msg->question;
        msg->question = p;
    }

    return buffer;
}

// �ӻ������ж�ȡDNS�ش���Ϣ���洢��msg�ṹ����
uint8_t* get_dnsanswer(Dns_Mes* msg, uint8_t* buffer, uint8_t* start) {
    int i;
    for (i = 0; i < msg->header->ancount; ++i) {
        char name[DNS_RR_NAME_MAX_SIZE] = { 0 };
        Dns_rr* p = malloc(sizeof(Dns_rr));

        // �ӻ������л�ȡ�ش�����
        buffer = get_domain(buffer, name, start);

        // �����ڴ沢��������
        p->name = malloc(strlen(name) + 1);
        memcpy(p->name, name, strlen(name) + 1);

        p->type = read_bits(&buffer, 16); // ��ȡ��Դ��¼����
        p->rr_class = read_bits(&buffer, 16); // ��ȡ��Դ��¼��
        p->ttl = read_bits(&buffer, 32); // ��ȡTTLֵ
        p->rd_length = read_bits(&buffer, 16); // ��ȡ��Դ���ݳ���

        // ���ݲ�ͬ�����ͽ��д�����Դ����
        switch (p->type) {
            case DNS_TYPE_A:    // IPv4��ַ
                for (int j = 0; j < 4; j++) {
                    p->rd_data.a_record.IP_addr[j] = read_bits(&buffer, 8);
                }
                break;
            case DNS_TYPE_AAAA: // IPv6��ַ
                for (int j = 0; j < 16; j++) {
                    p->rd_data.aaaa_record.IP_addr[j] = read_bits(&buffer, 8);
                }
                break;
            case DNS_TYPE_CNAME: // CNAME��¼
                p->rd_data.cname_record.cname = malloc(p->rd_length + 1);
                memcpy(p->rd_data.cname_record.cname, buffer, p->rd_length);
                p->rd_data.cname_record.cname[p->rd_length] = '\0';
                buffer += p->rd_length;
                break;
            case DNS_TYPE_MX: // MX��¼
                p->rd_data.mx_record.preference = read_bits(&buffer, 16);
                p->rd_data.mx_record.exchange = malloc(p->rd_length - 2 + 1);
                buffer = get_domain(buffer, p->rd_data.mx_record.exchange, start);
                break;
            case DNS_TYPE_TXT: // TXT��¼
                p->rd_data.txt_record.text = malloc(p->rd_length + 1);
                memcpy(p->rd_data.txt_record.text, buffer, p->rd_length);
                p->rd_data.txt_record.text[p->rd_length] = '\0';
                buffer += p->rd_length;
                break;
            case DNS_TYPE_SOA: // SOA��¼
                p->rd_data.soa_record.MName = malloc(strlen(buffer) + 1);
                buffer = get_domain(buffer, p->rd_data.soa_record.MName, start);
                p->rd_data.soa_record.RName = malloc(strlen(buffer) + 1);
                buffer = get_domain(buffer, p->rd_data.soa_record.RName, start);
                p->rd_data.soa_record.serial = read_bits(&buffer, 32);
                p->rd_data.soa_record.refresh = read_bits(&buffer, 32);
                p->rd_data.soa_record.retry = read_bits(&buffer, 32);
                p->rd_data.soa_record.expire = read_bits(&buffer, 32);
                p->rd_data.soa_record.minimum = read_bits(&buffer, 32);
                break;
            default:    // �������͵ļ�¼
                buffer += p->rd_length; // ������֧�ֵ���Դ����
                break;
        }

        // ���»ش���뵽�ش������ͷ��
        p->next = msg->answer;
        msg->answer = p;
    }
    return buffer;
}

// �ӻ������л�ȡ����
uint8_t* get_domain(uint8_t* buffer, char* name, uint8_t* start) {
    uint8_t* ptr = buffer;
    int i = 0, j = 0;
    int len = 0;

    // ����һ���ֽڵ�ǰ2λΪ11�����ʾָ�룬��14λΪƫ��������ת��DNS���Ķ���ʼ��ַ + ƫ������
    if (*ptr >= 0xc0) {
        uint16_t offset = *ptr;
        offset &= 0x3f;
        offset <<= 8;
        offset += *(ptr + 1);  // ��ȡ��14λƫ����
        get_domain(start + offset, name, start);
        return buffer + 2;
    }

    while (1) {
        uint8_t val = *ptr;
        ptr++;

        // ����00��ָ�룬�������������
        if (val == 0 || val >= 0xc0) {
            return ptr;
        }

        // ����ʱ�����ַ���Ϊ0����ʼ�����ַ�
        else if (len == 0) {
            len = val;
            if (i != 0) {
                name[i++] = '.';
            }
        }
        else if (len != 0) {
            name[i++] = val;
            len--;
        }
    }

    if (*ptr >= 0xc0) {
        char name2[DNS_RR_NAME_MAX_SIZE] = { 0 };
        uint16_t offset = (*ptr & 0x3f) << 8 + *(ptr + 1);  // ��ȡ��14λƫ����
        uint16_t* end = get_domain(start + offset, name, start);
        for (j = 0; j < strlen(name2); j++) {
            name[i + j] = name2[j];
        }
        ptr += 2;
    } else if (*ptr == 0) {
        ptr++;
    }

    return ptr;
}

// ��ָ��������λ��8, 16, 32�����õ���������
void write_bits(uint8_t** buffer, int bits, int value) {
    if (bits == 8) {
        **buffer = (uint8_t)value;
        (*buffer)++;
    }
    if (bits == 16) {
        uint16_t val = htons((uint16_t)value);
        memcpy(*buffer, &val, 2);
        *buffer += 2;
    }
    if (bits == 32) {
        uint32_t val = htonl(value);
        memcpy(*buffer, &val, 4);
        *buffer += 4;
    }
}

// ��װ��Ҫ������DNS����
uint8_t* dnsstruct_to_string(Dns_Mes* pmsg, uint8_t* buffer, uint8_t* ip_addr) {
    uint8_t* start = buffer;

    // ��װ��ͷ
    buffer = set_dnsheader(pmsg, buffer, ip_addr);
    // ��װѯ��
    buffer = set_dnsquestion(pmsg, buffer);
    // ��װ�ش�
    buffer = set_dnsanswer(pmsg, buffer, ip_addr);

    return buffer;
}

// ��DNS����ͷ��Ϣת��Ϊ�����ֽ��򲢴洢����������
uint8_t* set_dnsheader(Dns_Mes* msg, uint8_t* buffer, uint8_t* ip_addr) {
    Dns_Header* header = msg->header;
    header->qr = 1;       // ����Ϊ�ش���
    header->aa = 1;       // ����ΪȨ������������
    header->ra = 1;       // ����Ϊ���õݹ�
    header->ancount = 1;  // ���ûش���Ϊ1

    if (ip_addr[0] == 0 && ip_addr[1] == 0 && ip_addr[2] == 0 && ip_addr[3] == 0) {
        // ��IP��ַΪ0.0.0.0����ʾ������������
        header->rcode = 3;  // ���ִ���
    } else {
        header->rcode = 0;  // �޲��
    }

    write_bits(&buffer, 16, header->id); // ����ID

    int flags = 0;
    // ���ñ�־�ֶεĸ�������
    flags |= (header->qr << 15) & QR_MASK;
    flags |= (header->opcode << 11) & OPCODE_MASK;
    flags |= (header->aa << 10) & AA_MASK;
    flags |= (header->tc << 9) & TC_MASK;
    flags |= (header->rd << 8) & RD_MASK;
    flags |= (header->ra << 7) & RA_MASK;
    flags |= (header->rcode << 0) & RCODE_MASK;

    write_bits(&buffer, 16, flags); // ���ñ�־�ֶ�
    write_bits(&buffer, 16, header->qdcount); // ����������
    write_bits(&buffer, 16, header->ancount); // ���ûش���
    write_bits(&buffer, 16, header->nscount); // ����Ȩ����¼��
    write_bits(&buffer, 16, header->arcount); // ���ø��Ӽ�¼��

    return buffer;
}

// ��DNS��ѯ����ת��Ϊ�����ֽ��򲢴洢����������
uint8_t* set_dnsquestion(Dns_Mes* msg, uint8_t* buffer) {
    for (int i = 0; i < msg->header->qdcount; i++) {
        Dns_Question* p = msg->question;
        buffer = set_domain(buffer, p->q_name); // ��������

        write_bits(&buffer, 16, p->q_type); // ���ò�ѯ����
        write_bits(&buffer, 16, p->q_class); // ���ò�ѯ��

        p = p->next;
    }
    return buffer;
}

// ��DNS�ش���Ϣת��Ϊ�����ֽ��򲢴洢����������
uint8_t* set_dnsanswer(Dns_Mes* msg, uint8_t* buffer, uint8_t* ip_addr) {
    int i;

    buffer = set_domain(buffer, msg->question->q_name);

    write_bits(&buffer, 16, 1);  // type
    write_bits(&buffer, 16, 1);  // rr_class
    write_bits(&buffer, 32, 4);  // ttl
    write_bits(&buffer, 16, 4);  // rd_length

    for (i = 0; i < 4; i++) {
        *buffer = ip_addr[i];
        buffer++;
    }

    return buffer;
}

// ������ת��Ϊ�����ֽ��򲢴洢����������
uint8_t* set_domain(uint8_t* buffer, char* name) {
    uint8_t* ptr = name;
    char tmp[DNS_RR_NAME_MAX_SIZE] = { 0 };
    int i = 0;

    uint8_t* s = buffer;

    while (1) {
        if (*ptr == 0) {
            *buffer = i;
            buffer++;
            memcpy(buffer, tmp, i);
            buffer += i;

            *buffer = 0;
            buffer++;
            break;
        } else if (*ptr != '.') {
            tmp[i++] = *ptr;
        } else if (*ptr == '.') {
            *buffer = i;
            buffer++;
            memcpy(buffer, tmp, i);
            buffer += i;
            memset(tmp, 0, sizeof(tmp));
            i = 0;
        }
        ptr++;
    }

    return buffer;
}

// �ͷ�DNS���Ľṹ����ռ���ڴ�
void free_message(Dns_Mes* msg) {
    free(msg->header);

    Dns_Question* p = msg->question;
    while (p) {
        Dns_Question* tmp = p;
        p = p->next;
        free(tmp);
    }

    Dns_rr* q = msg->answer;
    while (q) {
        Dns_Question* tmp = q;
        q = q->next;
        free(tmp);
    }

    free(msg);
}