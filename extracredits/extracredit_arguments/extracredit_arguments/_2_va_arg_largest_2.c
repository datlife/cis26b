/*********************************************************
   CIS 26B -  Advanced C Programming
   Write a function named findMax that finds the maximum of
   any number of integer arguments. Use as a sentinel value 0.
   The first parameter is to represent one of the numbers.

   Extra Credit: Dat Nguyen
/*********************************************************/

#include <stdio.h>
#include <stdarg.h>

int findMax(int first_val, ...);

int main(void)
{
    printf("The largest is: %d\n", findMax(99, 20, 90, 10, 0));
    printf("The largest is: %d\n", findMax(40, 20, 10, 50, 30, 0));
    printf("The largest is: %d\n", findMax(25, 20, 10, 0));
    printf("The largest is: %d\n", findMax(10, 13, 0));
    printf("The largest is: %d\n", findMax(5, -20, 2, -50, -30, -90, 0));

    return 0;

}

/**
  Finds the maximum of any number of integer arguments.
*/
int findMax(int first_val, ...) {
	va_list argp;
	va_start(argp, first_val);

	int max = first_val;
	int tmp = va_arg(argp, int);
	while (tmp != 0) {
		max = (tmp > max) ? tmp : max;
		tmp = va_arg(argp, int);
	}
	va_end(argp);
	return max;
}

/*OUTPUT:
The largest is: 99
The largest is: 50
The largest is: 25
The largest is: 13
The largest is: 5
Press any key to continue . . .*/