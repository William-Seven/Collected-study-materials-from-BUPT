#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void generate_collatz_sequence(int n) {
    while (n != 1) {
        printf("%d, ", n);
        if (n % 2 == 0) {
            n /= 2;
        } else {
            n = 3 * n + 1;
        }
    }
    printf("1\n");
}

int main() {
    int n;
    printf("Please enter a positive integer: ");
    scanf("%d", &n);

    if (n <= 0) {
        fprintf(stderr, "Please provide a positive integer greater than 0.\n");
        return 1;
    }

    pid_t pid = fork();

    if (pid < 0) {
        // Fork failed
        perror("fork");
        return 1;
    } else if (pid == 0) {
        // Child process
        printf("Collatz sequence for %d: ", n);
        generate_collatz_sequence(n);
        exit(0);
    } else {
        // Parent process
        wait(NULL);  // Wait for child to finish
        printf("Child process has finished. Parent process exiting.\n");
    }

    return 0;
}