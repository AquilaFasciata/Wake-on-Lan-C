#include <stdio.h>

int main() {
    char address[9];
    printf("What is the MAC address?\n");
    scanf("%17s", &address);

    for (i = 0; i < strlen(address); i++) {
        // Check for the two common separator and skip them. 
        if (address[i] == '-' || address[i] == ':') { continue; }

        addressBytes[i] = (int) strtol(&address[i], NULL, 16);
        printf("%x %d\n", addressBytes[i], addressBytes[i]);
    }

    return 0;
}