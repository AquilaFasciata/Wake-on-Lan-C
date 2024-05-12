#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <ctype.h>

int create_magic_packet(char *address, int sizeAddress,  char *destination, int sizeDestination) {
    sizeDestination /= sizeof(*destination);
    sizeAddress /= sizeof(*address);
    int i = 0;

    char tempAddr[8];

    if (sizeDestination != 102) {
        printf("This isn't a valid magic packet allocation; please allocate an array of 102.\n");
      printf("The current allocation is %i.\n", sizeDestination);
        return EINVAL;
    }
    if (sizeAddress != 12) {
        printf("This isn't a valid MAC address. Please insert a valid MAC address.\n");
        return EINVAL;
    }
    printf("The address is: ");
    for (; i < sizeAddress; i++) {
        printf("%c", *(address + i));
    }

    for (i = 0; i < 7; i++) {
        *(destination + i) = 0xff;
    }

    for (; i < sizeDestination; i++) {
        *(destination + i) = *(address + (i % 8));
    }

    printf("The packet is: ");
    for (i = 0; i < sizeDestination; i++) {
        printf("%c", *(destination + i));
    }
    
    return 0;
}