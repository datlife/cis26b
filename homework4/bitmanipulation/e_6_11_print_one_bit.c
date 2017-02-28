/*******************************************************
    Examples: 6.11 Test one bit
/*******************************************************/

#include <stdio.h>
int main (void)
{
    unsigned short a = 6;     //  110
    //unsigned short a = 9;   // 1001

    printf("%d\n", a);
    printf("bit #0 is %hu\n", (a & 1));

    a >>= 1;
    printf("bit #1 is %hu\n", (a & 1));

    a >>= 1;
    printf("bit #2 is %hu\n", (a & 1));

    a >>= 1;
    printf("bit #3 is %hu\n", (a & 1));

    //a = 6;
    a = 9;
    a >>= 3;
    printf("bit #3 is %hu\n", (a & 1));


    return 0;
}
