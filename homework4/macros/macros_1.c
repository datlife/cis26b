/**
    Example 1
  
    C program => preprocessor => modified C program => compiler => object module
  
    Preprocessor Directives        
        . macro definitions
            #define
            #undef - to remove a macro definition

        . file inclusion
            #include

        . conditional compilation - alow bloks of text to be included or excluded 
            #if, #ifdef, #ifndef, #elif, #else. #endif

/********************************************************************************/ 

#include <stdio.h>

#define UPPER_LIMIT 101
#define RANGE_ERR printf("Out of range!\n")  
#define TAX 8.5 // some comment could be written here

int main (void)
{
    int n = 200;
    double total, tax, price = 99.99;

    if (n > UPPER_LIMIT)
        RANGE_ERR;
    tax = price * TAX / 100;
    total = price + tax;
    printf("          n = %d\n", n);
    printf("UPPER_LIMIT = %d\n\n", UPPER_LIMIT);

    printf("TAX = %.2f%%\n", TAX);
    printf("price = %10.2f\n", price);
    printf("tax   = %10.2f\n", tax);
    printf("       ==========\n");
    printf("total = %10.2f\n", total);

    return 0;
}

/* program after preprocessing



 


int main (void)
{
    int n = 200;
    double total, tax, price = 99.99;

    if (n > 101)
        printf("Out of range!\n");
    tax = price * 8.5 / 100;
    total = price + tax;
    printf("          n = %d\n", n);
    printf("UPPER_LIMIT = %d\n\n", 101);

    printf("TAX = %.2f%%\n", 8.5);
    printf("price = %10.2f\n", price);
    printf("tax   = %10.2f\n", tax);
    printf("       ==========\n");
    printf("total = %10.2f\n", total);

    return 0;
}

*/
