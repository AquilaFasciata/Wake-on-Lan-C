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
#include <unistd.h>
#include <getopt.h>

/* 
    ASCII Values
    0-9 = 48-57
    A-Z = 65-90
    a-z = 97-122
*/

#define VERSION "0.02"

int isSymbol(char character) {
    if (character < 48) {return 1;}
        else if (character > 57 && character < 65) {return 1;}
        else if (character > 90 && character < 97) {return 1;}
        else if (character > 122) {return 1;}
        else {return 0;}
}

int main(int argc, char *argv[]) {
    char address[18];
    char addressArr[12];
    char magicPacket[102];
    int port = 1;
    char opt;
    
    while ((opt = getopt(argc, argv, "p:hv")) != -1) {
        switch (opt) {
            case 'v':
                printf("Version: ");
                printf(VERSION);
                printf("\n\n");
                return 0;
            case 'p':
                port = strtol(optarg, NULL, 10);
                break;
            case 'h':
                printf("Usage: wol [options] <MAC Address>\n");
                printf("   or: wol\n\n");
                printf("Sends a magic packet to the specified MAC Address\n\n");
                printf("Options:\n");
                printf("-p <port>       Specifies the port on which to send the packet\n");
                printf("-h              Display this dialog\n");
                printf("-v              Display version info\n\n");
                return 0;
            default:
                break;
        }
    }
    if (argv[optind] != NULL) {
        strncpy(address, argv[optind], sizeof(address));
    }

    int i = 0;
    for (i = 0; i < sizeof(magicPacket); i++) {
        magicPacket[i] = '\0';
    }

    int socket_desc = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    int broadcast = 1;
    setsockopt(socket_desc, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(int));

    struct sockaddr_in recv_addr;
    recv_addr.sin_addr.s_addr = INADDR_BROADCAST;
    recv_addr.sin_family = AF_INET;
    recv_addr.sin_port = htons(port);

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    
    bind(socket_desc, (struct sockaddr*)&server_addr, sizeof(server_addr));    


    if (argc == 1) {
        printf("What is the MAC address?\n");
        scanf("%17s", address);
    }
    else {
        if (strlen(argv[1]) > 18) {
            printf("%s is not a valid MAC address.\n", argv[1]);
            return EINVAL;
        }
        for (i = 0; i < strlen(argv[1]); i++) {
            address[i] = *((argv[1]) + i);
        }
    }

    for (i = 0; i < strlen(address); i++) {
        address[i] = toupper(address[i]);
    }

    // Take input from array and remove seperators
    int j = 0;
    for (i = 0; i < strlen(address); i++) {
        if (!isalnum(address[i])) {continue;}
        addressArr[j] = address[i];
        j++;
    }

    int magicReturn = create_magic_packet(addressArr, sizeof(addressArr), magicPacket, sizeof(magicPacket));
    if (magicReturn != 0) {
        return magicReturn;
    }

    for (int i = 0; i < 3; i++) {
        int sendStatus = sendto(socket_desc, &magicPacket, sizeof(magicPacket), 0, (struct sockaddr*)&recv_addr, sizeof(recv_addr));
        if (sendStatus != sizeof(magicPacket)) {
            printf("There was an error sending the packet.\n");
            printf("The error code is %i: %s\n", errno, strerror(errno));
            return sendStatus;
        }
    }


    return 0;
}