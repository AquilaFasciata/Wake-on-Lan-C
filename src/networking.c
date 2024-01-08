#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int create_magic_packet(char *address, int sizeAddress,  unsigned long *destination, int sizeDestination) {
    int i = 0;
    sizeDestination /= sizeof(*destination);
    sizeAddress /= sizeof(*address);

    if (sizeDestination != 17) {
        printf("This isn't a valid magic packet allocation; please allocate an array of 17.\n");
      printf("The current allocation is %i.\n", sizeDestination);
        return EINVAL;
    }
    if (sizeAddress != 14) {
        printf("This isn't a valid MAC address. Please insert a valid MAC address.\n");
        return EINVAL;
    }

    *destination = 0xffffffff;

    unsigned long addressValue = 0;
    addressValue = strtoul(address, NULL, 16);

    for (i = 1; i < sizeDestination; i++) {
        *(destination + i) = addressValue;
    }
    
    return 0;
}

