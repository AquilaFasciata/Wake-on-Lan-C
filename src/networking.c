#include <sys/socket.h>

int create_magic_packet(int *address[],  int *destination[]) {
    int i = 0;

    // TODO Implement Program Error Signals
    if (sizeof(*destination) > 102) {
        
    }

    for (i = 0; i < 6; i++) {
        *(destination + i) = *(address + i);
    }
}