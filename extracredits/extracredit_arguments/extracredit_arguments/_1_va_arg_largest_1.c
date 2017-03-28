/*********************************************************
Name: Dat Thanh Nguyen

   CIS 26B -  Advanced C Programming
   Write a function named findMax that finds the maximum of
   any number of integer arguments.

/*********************************************************/

#include <stdio.h>
#include <stdarg.h> // enable argument list
// Function prototype
int findMax(int n, ...);

int main(void)
{
    printf("The largest is: %d\n", findMax(3, 20, 90, 10));
    printf("The largest is: %d\n", findMax(4, 20, 10, 50, 30));
    printf("The largest is: %d\n", findMax(2, 20, 10));
    printf("The largest is: %d\n", findMax(1, 13));
    printf("The largest is: %d\n", findMax(5, -20, 10, -50, -30, -90));

    return 0;
}
// Function declaration
int findMax(int n, ...) {
	va_list argp;
	va_start(argp, n);

	int max = va_arg(argp, int);
	for (int i = 1; i < n; i++) {
		int tmp = va_arg(argp, int);
		max = (tmp > max)? tmp : max;
	}
	va_end(argp);
	return max;
}
/*OUPUT:
The largest is: 90
The largest is: 50
The largest is: 20
The largest is: 13
The largest is: 10
Press any key to continue . . .
*/