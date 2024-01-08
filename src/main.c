#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/socket.h>
#include <bits/socket-constants.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <errno.h>
#include "networking.h"

/* 
    ASCII Values
    0-9 = 48-57
    A-Z = 65-90
    a-z = 97-122
*/


int isSymbol(char character) {
    if (character < 48) {return 1;}
        else if (character > 57 && character < 65) {return 1;}
        else if (character > 90 && character < 97) {return 1;}
        else if (character > 122) {return 1;}
        else {return 0;}
}

int main() {
    char address[18];
    int addressBytes[6];
    int magicPacket[102];

    int socket_desc = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    int broadcast = 1;
    setsockopt(socket_desc, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(int));

    struct sockaddr_in recv_addr;
    recv_addr.sin_addr.s_addr = INADDR_BROADCAST;
    recv_addr.sin_family = AF_INET;
    recv_addr.sin_port = htons(9);

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(9);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    
    bind(socket_desc, (struct sockaddr*)&server_addr, sizeof(server_addr));    

    int i = 0;

    printf("What is the MAC address?\n");
    scanf("%17s", address);

    for (i = 0; i < strlen(address); i++) {
        address[i] = toupper(address[i]);
    }

    // Convert the string to an array of integers
    int j = 0;
    for (i = 0; i < strlen(address); i++) {
        char pair[3];
        address[i] = (char) toupper(address[i]);

        // If there is a non-character or non-hex value entered, skip
        if ( isSymbol(address[i+1]) ) {continue;}
        if ( isSymbol(address[i]) ) {continue;}
        if (address[i] > 'F') {continue;}

        pair[0] = address[i];
        pair[1] = address[i+1];
        pair[2] = '\0';

        addressBytes[j] = (int) strtol(pair, NULL, 16);
        j++;
    }

    int magicReturn = create_magic_packet(addressBytes, sizeof(addressBytes), magicPacket, sizeof(magicPacket));
    if (magicReturn != 0) {
        return magicReturn;
    }

    int sendStatus = sendto(socket_desc, &magicPacket, sizeof(magicPacket), 0, (struct sockaddr*)&recv_addr, sizeof(recv_addr));
    if (sendStatus != sizeof(magicPacket)) {
        printf("There was an error sending the packet.\n");
        printf("The error code is %i: %s\n", errno, strerror(errno));
        return sendStatus;
    }


    return 0;
}