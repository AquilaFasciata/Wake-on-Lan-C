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
    int i = 0;

    char address[18];
    char addressBytes[13] = "Garbled nons";
    char magicPacket[204];


    int socket_desc = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    struct sockaddr_in recv_addr;
    recv_addr.sin_addr.s_addr = INADDR_BROADCAST;
    recv_addr.sin_family = AF_INET;
    recv_addr.sin_port = htons(9);

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(6589);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    int broadcastOpt = 1;
    setsockopt(socket_desc, SOL_SOCKET, SO_BROADCAST, &broadcastOpt, sizeof(int));
    
    int bindStatus = bind(socket_desc, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (bindStatus < 0) {
        printf("Binding to a network socket failed.\n");
        printf("Status code: %i\n", bindStatus);
        return bindStatus;
    }


    printf("What is the MAC address?\n");
    scanf("%17s", address);

    int j = 0;
    for (i = 0; i < strlen(address); i++) {
        if (!isalnum(address[i])) {continue;}
        *(addressBytes + j) = address[i];
        j++;
    }
    addressBytes[strlen(addressBytes) + 1] = '\0';
    

    int magicReturn = create_magic_packet(addressBytes, strlen(addressBytes), magicPacket, sizeof(magicPacket));
    if (magicReturn != 0) {
        return magicReturn;
    }

    int sendStatus = sendto(socket_desc, &magicPacket, sizeof(magicPacket), 0, (struct sockaddr*) &recv_addr, sizeof(recv_addr));
    if (sendStatus != sizeof(magicPacket)) {
        printf("There was an error sending the packet.\n");
        printf("Return code: %i\n", sendStatus);
        printf("Error was %d: %s\n", errno, strerror(errno));
        return sendStatus;
    }

    return 0;
}