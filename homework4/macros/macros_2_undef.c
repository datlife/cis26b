/**
    Example 2

    using undef

/********************************************************************************/

#include <stdio.h>

#define UPPER_LIMIT 101
#define RANGE_ERR printf("Out of range!\n")

void fun(void);

int main (void)
{
    int n = 200;

    if (n > UPPER_LIMIT)
        RANGE_ERR;
    printf("          n = %d\n", n);
    printf("UPPER_LIMIT = %d\n\n", UPPER_LIMIT);
    //fun();


    #undef UPPER_LIMIT
    #define UPPER_LIMIT 202
    if (n > UPPER_LIMIT)
        RANGE_ERR;
    printf("          n = %d\n", n);
    printf("UPPER_LIMIT = %d\n\n", UPPER_LIMIT);
    //fun();

    return 0;
}

/************************************************/
void fun(void)
{
    printf("UPPER_LIMIT = %d\n\n", UPPER_LIMIT);
    return;
}
