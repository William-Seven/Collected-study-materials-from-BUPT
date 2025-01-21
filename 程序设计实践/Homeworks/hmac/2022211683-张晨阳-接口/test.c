#include <stdio.h>
#include <string.h>
#include "hmac.h"

void test_hmac(const char* algorithm) {
    const char* src = "kjhdskfhdskfjhdskjfdskfdskfjsdkfjds";
    const char* key = "kjshfkds";
    char result[EVP_MAX_MD_SIZE * 2 + 1];  // 确保缓冲区足够大
    int status = hmac(src, strlen(src), key, strlen(key), algorithm, result, sizeof(result));

    if (status == 0) {
        printf("%s result = [%s]\n", algorithm, result);
    } else if (status == -1) {
        printf("Error: invalid algorithm %s\n", algorithm);
    } else if (status == -2) {
        printf("Error: output buffer too small for algorithm %s\n", algorithm);
    }
}

int main() {
    test_hmac("md5");
    test_hmac("sha1");
    test_hmac("sha224");
    test_hmac("sha256");
    test_hmac("sha384");
    test_hmac("sha512");
    test_hmac("xxx");  // xxx是不存在的算法
}
