/**
    Example 3
    Defining long macros

/********************************************************************************/

#include <stdio.h>

#define LEN   10
#define WIDTH 20
#define HEIGHT 3

#define VOLUME LEN *   \
               WIDTH * \
               HEIGHT

int main (void)
{
    printf("LEN    = %d\n\n", LEN);
    printf("WIDTH  = %d\n\n", WIDTH);
    printf("HEIGHT = %d\n\n", HEIGHT);
    printf("VOLUME = %d\n\n", VOLUME);

    return 0;
}

