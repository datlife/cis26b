/*******************************************************
    Examples: 6.8 Demonstration of formula to
    TURN OFF a range of bits
/*******************************************************/

#include <stdio.h>

int main (void)
{
    void printbits(unsigned short wrd);
    unsigned short a = 31, b = 19, c, mask;
    int numbits = 3;
    //int numbits  = 4;
    //int numbits  = 5;
    //int startbit = 2;
    int startbit = 1;

    mask = (unsigned short)~0;
    mask <<= numbits;
    mask = ~mask;
    mask <<= startbit;
    mask = ~mask;
    c = a & mask;

    printf("Turn OFF %d bits starting at bit#%d\n", numbits, startbit);
    printf("%d\n", a);
    printbits(a);
    printbits(c);
    printf("%d\n", c);

    a = 31;
    mask = ~((~(((unsigned short) ~0) << numbits)) << startbit);
    c = a & mask;
    printf("Turn OFF %d bits starting at bit#%d\n", numbits, startbit);
    printf("%d\n", a);
    printbits(a);
    printbits(c);
    printf("%d\n", c);

    a = 31;
    printf("Turn OFF %d bits starting at bit#%d\n", numbits, startbit);
    printf("%d\n", a);
    printbits(a);
    //a &= ~((~(((unsigned short)~0) << numbits)) << startbit);
    a &= ~(~((unsigned short)~0 << numbits) << startbit);
    printbits(a);
    printf("%d\n", a);

    printf("Turn OFF %d bits starting at bit#%d\n", numbits, startbit);
    printf("%d\n", b);
    printbits(b);
    b &= ~(~((unsigned short)~0 << numbits) << startbit);
    printbits(b);
    printf("%d\n", b);
    return 0;
}


/**************************************************************
   Return 1 if bit_to_test is set and 0 if it is unset
*/
int  testbit(unsigned short wrd, int bit_to_test)
{
    wrd >>= bit_to_test;
    wrd &= 1;
    return wrd;
}

/**************************************************************
   This uses a trick to print an unsigned short as a string of
   16 bits
*/
void printbits(unsigned short wrd)
{
    int  testbit(unsigned short wrd, int bit_to_test);
    int i;

    for (i = 15; i >= 0; i--)
        printf("%1d", testbit(wrd, i));
    printf("\n");
    return;
}

