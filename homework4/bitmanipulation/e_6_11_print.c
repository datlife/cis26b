/*******************************************************
    Examples: 6.11 Testing Individual Bits and
    Printing Bit Strings
/*******************************************************/

#include <stdio.h>
int main (void)
{
    int  testbit(unsigned short wrd, int bit_to_test);
    void printbits(unsigned short wrd);
    //unsigned short wrd = 1;
    //unsigned short wrd = 2;
    unsigned short wrd = 65;
    //unsigned short wrd = 127;
    int i;

    for (i = 0; i < 10; i++)
    {
        printf("Bit %2d of word is %s\n", i, testbit(wrd, i) ? "ON" : "OFF");
    }
    printbits(wrd);
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
    return;
}
