/*******************************************************
 Homework 4: Part A
 
 Biwise Operators
 
 There are three requirements:
 1. Define and use a macro to turn on a range of bits
 2. Define and use a macro to turn off a range of bits
 3. Define and use a macro to toggle a range of bits
 4. Write a function that takes an unsigned short parameter and returns an unsigned short 
 with the bits in the parameter turned backwards. 
 Thus, if the parameter has a binary value of
 11111111111100000000000000000000
 your function will return a value whose binary representation is
 00000000000011111111111111111111
 
 NAME:
 IDE:
 *******************************************************/

#include <stdio.h>

int  testbit(unsigned short wrd, int bit_to_test);
void printbits(unsigned short wrd);

int main (void)
{
    unsigned short wrd = 65, a = 32, b, mask;
    int numbits = 3;
    int startbit = 2;
    
    printbits(wrd);
    
    mask = (~(((unsigned short)~0) << numbits)) << startbit; // replace this by a macro with arguments
    b = a | mask;
    printf("Turn ON %d bits starting at bit#%d\n", numbits, startbit);
    printf("%d\n", a);
    printbits(a);
    printbits(b);
    printf("%d\n", b);
    
    a = 31;
    mask = ~((~(((unsigned short) ~0) << numbits)) << startbit); // replace this by a macro with arguments
    b = a & mask;
    printf("Turn OFF %d bits starting at bit#%d\n", numbits, startbit);
    printf("%d\n", a);
    printbits(a);
    printbits(b);
    printf("%d\n", b);
    
    a = 85;
    // mask = ??? // define this mask as a macro with arguments
    // c = ???
    printf("Toggle %d bits starting at bit#%d\n", numbits, startbit);
    printf("%d\n", a);
    printbits(a);
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
    {
        printf("%1d", testbit(wrd, i));
        if (!(i % 4))
            printf(" ");
    }
    printf("\n");
    return;
}
