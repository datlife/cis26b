/*******************************************************
    Examples: 6.6 Demonstration of the
    Bitwise Right Shift:  >>
/*******************************************************/

#include <stdio.h>

int main (void)
{
    unsigned short a = 128;

    // shift one by one
    printf("%hu\n", a);
    a = a >> 1;
    printf(">> 1: %hu\n", a);
    a = a >> 1;
    printf(">> 1: %hu\n", a);
    a = a >> 1;
    printf(">> 1: %hu\n\n", a);

    // shift 3
    a = 128;
    printf("%hu\n", a);
    a = a >> 3;
    printf(">> 3: %hu\n", a);

    a = 128;
    printf("%hu\n", a);
    a = a / (2*2*2); // 2 to 3
    printf("divide by 2 to 3: %hu\n\n", a);

    return 0;
}

