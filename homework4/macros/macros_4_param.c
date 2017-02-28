/**
    Example 1
  
   #define MIN(x, y) ((x) > (y) ? (x) : (y))
              ^ // NO SPACE between the macro name and the paranthesis
                // WHY?
   MACROS VS FUNCTIONS
   Advantages
   . faster program (no time needed to pass parameters)
   . generic: same macro works with different types (no type conversions, etc)
   
   Disadvantages
   . type of the parameters - not checked
   . object module - larger
   . no pointers to macros (yes pointers to functions)
   . multiple evaluation of the same parameter
/********************************************************************************/ 

#include <stdio.h>

#define MIN(x, y) ((x) > (y) ? (x) : (y))
#define IS_ODD(num) ((num) % 2)
//#define IS_ODD(num) num % 2

#define GUESS(x) ('a' <= (x) && (x) <= 'z' ? (x) - 'a' + 'A' : (x))
 
int main (void)
{
    int n = 25;
    int a = 10, b = 20;
    double u = 23.6, v = 19.5;
    
    if (IS_ODD(n))
        printf("ODD\n");
    else
        printf("EVEN\n");
    printf("n = %d\n\n", n);

    if (IS_ODD(n + 3))
        printf("ODD\n");
    else
        printf("EVEN\n");   
    printf("n = %d\n\n", n + 3);

    printf("%d %d %d\n\n", a, b, MIN(a, b));
    printf("%.2f %.2f %.2f\n\n", u, v, MIN(u, v));

    a = b = 19;
    printf("%d %d %d\n\n", a, b, MIN(a++, b));
    // ((a++) > (b) ? (a++) : (b))
    // difficult to find: AVOID side effects as macro arguments!
    return 0;
}

