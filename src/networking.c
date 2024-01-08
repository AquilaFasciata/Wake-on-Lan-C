#include <stdio.h>
#include <errno.h>

int create_magic_packet(char *address, int sizeAddress,  char *destination, int sizeDestination) {
    int i = 0;
    sizeDestination /= sizeof(*destination);

    if (sizeDestination != 204) {
        printf("This isn't a valid magic packet allocation; please allocate an array of 204.\n");
      printf("The current allocation is %i.\n", sizeDestination);
        return EINVAL;
    }
    if (sizeAddress != 12) {
        printf("This isn't a valid MAC address. Please insert a valid MAC address.\n");
        return EINVAL;
    }

    // Adds 6 bytes of FF as per WoL Spec
    for (i = 0; i < 12; i++) {
        *(destination + i) = 'f';
    }

    for (i = i; i < 204; i++) {
        *(destination + i) = *(address + (i % 12));
    }

    return 0;
}

