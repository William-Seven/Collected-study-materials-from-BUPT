#include <stdio.h>

int main() {
    // Decimal numbers
    int decimal = 100;  // Decimal number

    // Octal numbers
    int octal = 0144;  // Octal number

    // Hexadecimal numbers
    int hex = 0x64;  // Hexadecimal number

    // Float numbers with different bases
    float pi = 3.14159;         // Decimal float
    float e = 2.71828;          // Decimal float
    float hexFloat = 0x1.2p10;  // Hexadecimal float

    // Exponential notation
    double exp = 1e10;  // Exponential notation

    printf("Decimal: %d\n", decimal);
    printf("Octal: %o\n", octal);
    printf("Hex: %x\n", hex);
    printf("Float in hex: %a\n", hexFloat);
    printf("Exponential: %e\n", exp);

    // Array with different bases
    int bases[] = {10, 07, 0x1A};

    // Loop to print array elements
    for (int i = 0; i < sizeof(bases) / sizeof(bases[0]); i++) {
        printf("Array element in base 10: %d\n", bases[i]);
    }

    return 0;
}