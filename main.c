#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    int addressBytes[18];
    int i = 0;

    printf("What is the MAC address?\n");
    scanf("%17s", &address);

    for (i = 0; i < strlen(&address); i++) {
        char pair[2];
        if ( isSymbol(address[i+1]) ) {continue;}

           
    }

    return 0;
}