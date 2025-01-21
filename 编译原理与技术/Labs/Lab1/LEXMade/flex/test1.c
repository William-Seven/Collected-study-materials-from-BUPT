#include <stdio.h>

// This is a single line comment

/*
  This is a multi-line comment
  It spans multiple lines
*/

int main() {
    int a = 10;          // This is an integer
    float b = 20.5;      // This is a floating point number
    char c = 'a';        // This is a character
    double d = 30.5e-2;  // This is a double

    if (a > 5) {
        printf("a is greater than 5\n");
    } else {
        printf("a is not greater than 5\n");
    }

    while (a < 20) {
        a++;
    }

    do {
        b -= 1.5;
    } while (b > 0);

    for (int i = 0; i < 10; i++) {
        c = 'A' + i;
    }

    switch (c) {
        case 'A':
            printf("Uppercase A\n");
            break;
        case 'a':
            printf("Lowercase a\n");
            break;
        default:
            printf("Other character\n");
    }

    return 0;
}