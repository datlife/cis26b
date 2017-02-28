/*******************************************************
    Examples: 6.1234 Demonstration of bitwise
    NOT: ~
    AND: &
     OR: |
    XOR: ^
/*******************************************************/

#include <stdio.h>

int main (void)
{
    unsigned short a = 65534, b, c;

    // NOT
    b = ~a;
    printf(" a = %hu\n~a = %hu\n\n", a, b);

    // AND
    a = 11;
    b = 6;
    c = a & b;
    printf("a & b = %hu\n", c);  // 2

    // OR
    c = a | b;
    printf("a | b = %hu\n", c);  // 8+4+2+1 = 15

    // XOR
    c = a ^ b;
    printf("a ^ b = %hu\n", c);  // 8+4+1 = 13

    return 0;
}

