/*******************************************************
    Exercise:     TOGGLE a range of bits
/*******************************************************/

#include <stdio.h>

int main (void)
{
    void printbits(unsigned short wrd);
    unsigned short a = 102, b = 85, c, mask;
    int numbits = 6;
    //int numbits  = 4;
    //int numbits  = 5;
    //int startbit = 2;
    int startbit = 0;

    // Variation A - one statement at a time
    

    printf("Toggle %d bits starting at bit#%d\n", numbits, startbit);
    printf("%d\n", a);
    printbits(a);
    printbits(c);
    printf("%d\n", c);

    // Variation B - one line formula
    a = 85;
    printf("Toggle %d bits starting at bit#%d\n", numbits, startbit);
    printf("%d\n", a);
    printbits(a);
    // write the statement below

    printbits(a);
    printf("%d\n", a);

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

