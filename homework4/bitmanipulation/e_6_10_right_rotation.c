/*******************************************************
    Examples: 6.10 Demonstration of
    Right Rotation of Bits
/*******************************************************/

#include <stdio.h>

int main (void)
{
    void printbits(unsigned short wrd);
    unsigned short rightrot(unsigned short wrd, int numbits);

    //unsigned short wrd = 3;
    unsigned short wrd = 59;
    //int numbits = 1;
    //int numbits = 2;
    int numbits = 4;

    printf("\nRight rotation of %hu by %d bit%c\n",
           wrd, numbits, numbits == 1 ? ' ' : 's');
    printbits(wrd);
    wrd = rightrot(wrd, numbits);
    printbits(wrd);

    //wrd = 59;
    printf("\nLeft rotation of %hu by %d bit%c\n",
           wrd, numbits, numbits == 1 ? ' ' : 's');
    printbits(wrd);
    wrd = rightrot(wrd, 8 * sizeof (short) - numbits); // left!
    printbits(wrd);

    return 0;
}
/**************************************************************
   Right Rotation of bits
*/
unsigned short rightrot(unsigned short wrd, int numbits)
{
    unsigned short nleft;

    nleft = wrd << (sizeof (short) * 8 - numbits);
    wrd >>= numbits;
    wrd |= nleft;
    return wrd;
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


