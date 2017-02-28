/*******************************************************
    Examples: 6.9 Demonstration of formula to
    OVERLAY a bit pattern on a range of bits
/*******************************************************/

#include <stdio.h>

int main (void)
{
    void printbits(unsigned short wrd);
    unsigned short overlay(unsigned short wrd,
                           int startbit,
                           int numbits,
                           unsigned short pattern);
    unsigned short wrd     = 127; // 1111111 in binary
    unsigned short pattern = 11;   // 1011 in binary
    int startbit = 0;
    //int startbit = 1;
    //int startbit = 2;
    int numbits = 4;

    // Version 1
    printf("Start at bit#%d\n", startbit);
    printf("Overlay the right most %d bits from the following pattern:\n", numbits);
    printbits(pattern);
    printbits(wrd);

    // A. Turn off the range of bits
    wrd &= ~(~((unsigned short)~0 << numbits) << startbit);
    // B. Shift the pattern to match the range of bits
    pattern <<= startbit;
    // C. Use inclusive or: |
    wrd |= pattern;

    printbits(wrd);

    // Version 2
    wrd = 127;
    pattern = 11;
    printf("Start at bit#%d\n", startbit);
    printf("Overlay the right most %d bits from the following pattern:\n", numbits);
    printbits(pattern);
    printbits(wrd);
    wrd = overlay(wrd, startbit, numbits, pattern);
    printbits(wrd);
    return 0;
}
/**************************************************************
   Overlaying a bit pattern on a range of bits
*/
 unsigned short overlay(unsigned short wrd,
                           int startbit,
                           int numbits,
                           unsigned short pattern)
{
    wrd &= ~(~((unsigned short) ~0 << numbits) << startbit);
    wrd |= pattern << startbit;
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

