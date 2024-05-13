#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <ctype.h>

int create_magic_packet(char *address, int sizeAddress,  char *destination, int sizeDestination) {
    sizeDestination /= sizeof(*destination);
    sizeAddress /= sizeof(*address);
    int i = 0;

    if (sizeDestination != 102) {
        printf("This isn't a valid magic packet allocation; please allocate an array of 102.\n");
      printf("The current allocation is %i.\n", sizeDestination);
        return EINVAL;
    }
    if (sizeAddress != 12) {
        printf("This isn't a valid MAC address. Please insert a valid MAC address.\n");
        return EINVAL;
    }
    printf("Sendin the packet to address: ");
    for (; i < sizeAddress; i++) {
        printf("%c", *(address + i));
    }
    printf("\n");

    for (i = 0; i < 6; i++) {
        *(destination + i) = 0xff;
    }

    int* j = (int *) malloc(sizeof(int)); // Freed @ Line #40
    *j = 0;
    for(i; i < sizeDestination; i++) {
        char pair[3];
        pair[0] = *(address + (*j % 12));
        pair[1] = *(address + ((*j % 12) + 1));
        pair[2] = '\0';
        *(destination + i) = strtol(pair, NULL, 16);
        *j += 2;
    }
    free(j);

    return 0;
}
