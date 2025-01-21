#include <openssl/ssl.h>
#include <stdio.h>
#include <string.h>

int hmac(const char* str, int str_length, const char* key, int key_length, const char* algorithm, char* out_buffer, int buffer_size) {
    // 根据算法名称获得算法引擎
    const EVP_MD* engine = EVP_get_digestbyname(algorithm);
    if (engine == NULL) {
        return -1;  // 无效的算法名称
    }

    HMAC_CTX* ctx = HMAC_CTX_new();
    if (HMAC_Init_ex(ctx, key, key_length, engine, NULL) <= 0) {
        HMAC_CTX_free(ctx);
        return -1;
    }
    if (HMAC_Update(ctx, (unsigned char*)str, str_length) <= 0) {
        HMAC_CTX_free(ctx);
        return -1;
    }

    unsigned char output[EVP_MAX_MD_SIZE];  // 存放摘要输出的缓存
    unsigned int output_length;             // 存放实际输出的摘要长度
    if (HMAC_Final(ctx, output, &output_length) <= 0) {
        HMAC_CTX_free(ctx);
        return -1;
    }
    HMAC_CTX_free(ctx);

    // 检查输出缓冲区是否足够
    if (buffer_size < output_length * 2 + 1) {
        return -2;  // 缓冲区不足
    }

    // 将摘要结果转换为十六进制表示的asc码字符串
    static const char* hex_digits = "0123456789abcdef";
    for (unsigned int i = 0; i < output_length; i++) {
        out_buffer[i * 2] = hex_digits[output[i] >> 4];        // 偶数字节存放高四位对应的数字
        out_buffer[i * 2 + 1] = hex_digits[output[i] & 0x0F];  // 奇数字节存放低四位对应的数字
    }
    out_buffer[output_length * 2] = '\0';  // 末尾加上空字符

    return 0;  // 成功
}
