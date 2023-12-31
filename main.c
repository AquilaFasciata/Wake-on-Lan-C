#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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
    int i = 0;

    printf("What is the MAC address?\n");
    scanf("%17s", &address);

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

    

    return 0;
}