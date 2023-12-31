#include <sys/socket.h>

int * create_magic_packet(int* address[]) {
    int* packet[102];
    int i = 0;
    
    for (i = 0; i < 6; i++) {
        (*packet)[i] = *(address + i);
    }
}