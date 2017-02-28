/*******************************************************
    Examples: 6.11 Check if a number is odd or even
/*******************************************************/

#include <stdio.h>
int main (void)
{
    unsigned short a = 9, b = 6;

    // explicit
    //if ((a & 1) != 0) // != has a higher precedence than &
    //if (a & 1 != 0)
    //if( a & (1 != 0)) // ???
    if (a & 1)
    {
        printf("%hu is ODD\n", a);
    }
    else
    {
        printf("%hu is EVEN\n", a);
    }

    // terse
    printf("%hu is %s\n\n", b, (b & 1) ? "ODD" : "EVEN");

    printf("a = %hu\nThe rightmost bit is %hu\n\n", a, a & 1);
    printf("b = %hu\nThe rightmost bit is %hu\n\n", b, b & 1);

    return 0;
}
