#include <sys/socket.h>
#include <stdio.h>
#include <errno.h>

int create_magic_packet(int *address,  int *destination) {
    int i = 0;

    if (sizeof(*destination) / sizeof(int) != 102) {
        printf("This isn't a valid magic packet allocation; please allocate an array of 102.\n");
        return EINVAL;
    }
    if (sizeof(*address) / sizeof(int) != 6) {
        printf("This isn't a valid MAC address. Please insert a valid MAC address.\n");
        return EINVAL;
    }

    // Adds 6 bytes of FF as per WoL Spec
    for (i = 0; i < 6; i++) {
        *(destination + i) = 255;
    }

    for (i = i; i < sizeof(*destination) / sizeof(int); i++) {
        *(destination + i) = *(address + (i % sizeof(address)) );
    }

    return 0;
}