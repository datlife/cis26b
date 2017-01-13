/***
 CIS 26B: Homework 1A
 ********************
 NAME: Dat Nguyen
 IDE(compiler): Visual Studio 2016
*************************************************************************
   Review: Functions, Structures, Pointers, Arrays, and Sorting
   Sort an array of STUDENT structures using the insertion sort algorithm.
   
   Your task:
        1. Write function named printList() that displays the list to the screen and call it in main() to print the unsorted data
        2. Write a second sort function that sorts the array in descending order 
           by the final exam score, then call it.
        3. Call the printList() function again to show the results of the second sort.
        4. Replace the "Sample Output" below with the new resuls
*/

#include <stdio.h>
#include <string.h>

#define NUM_STU 6

typedef struct
{
    char  name[31];
    int   midterm[2];
    int   final;
} STUDENT;


void insertionSort 	   (STUDENT  list[], STUDENT *pLast);

void insertionSortFinal(STUDENT list[], STUDENT *pLast);

void printer		   (STUDENT  list[], STUDENT *pLast, char format_description[]);

int main (void)
{
	STUDENT *pStu, *pLast;
	STUDENT  stuList[NUM_STU] =
    {
	    {"Taylor, Noah",    {85, 94}, 92},
	    {"Smith, Olivia",   {91, 89}, 86},
	    {"Brown, Liam",     {87, 88}, 90},
	    {"Davis, Emma",     {96, 88}, 97},
	    {"Garcia, Mason",   {79, 93}, 92},
        {"Lopez, Sophia",   {83, 78}, 95}
	};

    pLast = stuList + NUM_STU - 1;
    
	printf("Unsorted data:\n");
	for (pStu = stuList; pStu <= pLast; pStu++)
    {
	   printf("%-30s %4d %4d %4d\n",
	           pStu->name,
	           pStu->midterm[0],
	           pStu->midterm[1],
	           pStu->final);
    }
	printf("\n");
 
	insertionSort (stuList, pLast);
	 
	printf("Sorted data:\n");
    printf("Unsorted data:\n");
    for (pStu = stuList; pStu <= pLast; pStu++)
    {
        printf("%-30s %4d %4d %4d\n",
               pStu->name,
               pStu->midterm[0],
               pStu->midterm[1],
               pStu->final);
    }
    printf("\n");
	return 0;
}
/*	========================================================
	Sort list using Insertion Sort.
	   Pre   list[] must contain at least one element
	         size is index to last element in list
	   Post  list has been rearranged.
*/
void insertionSort (STUDENT  list[], STUDENT *pLast)
{
	STUDENT  temp;
	STUDENT *pCurr;
	STUDENT *pWalk;

	for (pCurr = list + 1; pCurr <= pLast; pCurr++)
    {
	   temp    = *pCurr;
	   pWalk = pCurr - 1;
       while (pWalk >= list && strcmp(temp.name, pWalk->name) < 0)
       {
             *(pWalk + 1) = *pWalk;
	          pWalk--;
	   }
	   *(pWalk + 1)  = temp;
    }
	
}
/*	================= Sample Output ================= */
/*	
 Unsorted data:
 Taylor, Noah                     85   94   92
 Smith, Olivia                    91   89   86
 Brown, Liam                      87   88   90
 Davis, Emma                      96   88   97
 Garcia, Mason                    79   93   92
 Lopez, Sophia                    83   78   95
 
 Sorted data:
 Unsorted data:
 Brown, Liam                      87   88   90
 Davis, Emma                      96   88   97
 Garcia, Mason                    79   93   92
 Lopez, Sophia                    83   78   95
 Smith, Olivia                    91   89   86
 Taylor, Noah                     85   94   92
*/
