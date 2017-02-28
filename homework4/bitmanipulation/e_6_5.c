/*******************************************************
    Examples: 6.5 Demonstration of Exclusive OR for
    Data Encryption and Decryption
/*******************************************************/

#include <stdio.h>

int main (void)
{
    unsigned short a = 65;
    //unsigned short key = 1;
    //unsigned short key = 2;
    unsigned short key = 3;
    //unsigned short key = 10;

    printf("%hu %c\n", a, a);
    a = a ^ key;
    printf("%hu %c\n", a, a);
    a = a ^ key;
    printf("%hu %c\n", a, a);

    return 0;
}

