/*******************************************************
    Examples: 6.6 Demonstration of the
    Bitwise Left Shift:  <<
/*******************************************************/

#include <stdio.h>
#include <math.h>
int main (void)
{
    unsigned short a = 1, b, c, d, e;

    // shift one by one
    printf("%hu\n", a);
    a = a << 1;
    printf("<< 1: %hu\n", a);
    a = a << 1;
    printf("<< 1: %hu\n", a);
    a = a << 1;
    printf("<< 1: %hu\n\n", a);

    // shift 6
    a = 1;
    printf("%hu\n", a);
    a = a << 6;
    printf("<< 6: %hu\n", a);

    a = 1;
    printf("%hu\n", a);
    a = a * (2*2*2*2*2*2); // 2 to 6
    printf("multiply by 2 to 6: %hu\n\n", a);

    // shift 15
    a = 1;
    printf("%hu\n", a);
    a = a << 15;
    printf("<< 15: %hu\n", a);

    a = 1;
    printf("%hu\n", a);
    a = a * (unsigned short)pow(2, 15);
    printf("multiply by 2 to 15: %hu\n\n", a);

    // shift 16
    a = 1;
    a = a << 16;
    printf("<< 16: %hu\n", a);

    a = 1;
    a = a * (unsigned short)pow(2, 16);
    printf("multiply by 2 to 16: %hu\n\n", a);

    // precedence
    a = 1, b = 2;
    c = a << b + 1;
    d = a << (b + 1);
    e = (a << b) + 1;
    printf("%d %d %d %d %d\n", a, b, c, d, e); // 1 2 8 8 5

    return 0;
}

