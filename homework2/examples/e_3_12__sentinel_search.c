/*  Knuth (the author of "The Art of Computer Programming") states: 

    "When the inner loop of a program tests two or more conditions, we should 
    try to reduce the testing to just one condition."  

    To eliminate the test for the end of the list we copy the target at the end 
    of the list (the target is now a "sentinel"). We determine after the loop 
    completes whether we found actual data or the sentinel.

*/
#include <stdio.h>

#define MAX_ARY_SIZE 100

int main (void)
{
    int *sentinel_search (int  *list, int n, int target);

    int	ary[MAX_ARY_SIZE + 1] = { 89, 72,  3, 15, 21};
                       // ^^^ + 1 for the sentinel value
	int size = 5;
	//int target = 15;
	int target = 10;
	int *ploc;

	if (ploc = sentinel_search (ary, size, target))
	    printf("%3d found at location:       %2d\n", *ploc, ploc - ary);
	else
	    printf("%3d NOT found!\n", target);

	printf("End of search.\n");
	return 0;
}// main

/*************************************************************
	Sentinel Search: Locate the target in an unordered list
	of n elements. Returns NULL if not found; returns pointer
	to the first element equal to the target value if found.
*/
int *sentinel_search (int  *list, int  n, int  target)
{
	int *psent = list + n;
	int *ploc = list;

    *psent = target;  // copy target(sentinel) at the end of the list
	while (target != *ploc)
	   ploc++;
    return ploc == psent ? NULL : ploc;
}
