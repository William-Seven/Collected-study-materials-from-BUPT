#ifndef _HMAC_H_
#define _HMAC_H_

// 一个通用接口，用于使用不同的算法求得一个字符串的hash摘要字符串。
// 输入参数str: 要处理的字符串
// 输入参数str_length: 要处理的字符串的长度
// 输入参数key: 秘钥
// 输入参数key_length: 秘钥长度
// 输入参数algorithm: 算法名称，目前支持md5, sha1, sha256, sha512等
// 输入参数out_buffer: 用于存放输出摘要的缓冲区，必须至少是EVP_MAX_MD_SIZE * 2 + 1大小
// 输入参数buffer_size: out_buffer的大小
// 返回值：返回值为0表示成功，非0表示出错。如果返回值为-1，表示传入的算法无效；
// 如果返回值为-2，表示输出缓冲区不足。如果返回值为0，输出缓冲区包含摘要字符串（已经转换为asc格式）。
int hmac(const char* str, int str_length, const char* key, int key_length, const char* algorithm, char* out_buffer, int buffer_size);

#endif
