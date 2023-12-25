#include <stdio.h>

int main() {
    char address[9];
    printf("What is the MAC address?\n");
    scanf("%8s\n", &address);

    printf("The string was %s.", address);

    return 0;
}