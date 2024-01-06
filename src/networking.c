#include <sys/socket.h>
#include <stdio.h>
#include <errno.h>

int create_magic_packet(int *address, int sizeAddress,  int *destination, int sizeDestination) {
    int i = 0;
    sizeDestination /= sizeof(*destination);

    if (sizeDestination != 102) {
        printf("This isn't a valid magic packet allocation; please allocate an array of 102.\n");
      printf("The current allocation is %i.\n", sizeDestination);
        return EINVAL;
    }
    sizeAddress /= sizeof(*address);
    if (sizeAddress != 6) {
        printf("This isn't a valid MAC address. Please insert a valid MAC address.\n");
        return EINVAL;
    }

    // Adds 6 bytes of FF as per WoL Spec
    for (i = 0; i < 6; i++) {
        *(destination + i) = 255;
    }

    for (i = i; i < sizeDestination; i++) {
        *(destination + i) = *(address + (i % sizeAddress ));
    }

    return 0;
}

