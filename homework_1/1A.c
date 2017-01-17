/*******************
CIS 26B: Homework 1A
********************
NAME: Dat Nguyen

IDE(compiler): Visual Studio 2016
Last Update  : 9:54 AM 1/15/2017
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


void insertionSort(STUDENT  list[], STUDENT *pLast);
void insertionSortFinal(STUDENT list[]);
void printList(char title[], STUDENT  list[], STUDENT *pLast, char format_title[], char format_content[]);

int main(void)
{
	STUDENT *pStu, *pLast;
	STUDENT  stuList[NUM_STU] =
	{
		{ "Taylor, Noah",{ 85, 94 }, 92 },
		{ "Smith, Olivia",{ 91, 89 }, 86 },
		{ "Brown, Liam",{ 87, 88 }, 90 },
		{ "Davis, Emma",{ 96, 88 }, 97 },
		{ "Garcia, Mason",{ 79, 93 }, 92 },
		{ "Lopez, Sophia",{ 83, 78 }, 95 }
	};
	pLast = stuList + NUM_STU - 1;
	pStu = 	stuList;
	char *format_content = "%-30s %8d %8d %8d\n";
	char *format_title   = "%-30s %9s %8s %8s\n";

	printList("Unsorted Data", stuList, pLast, format_title, format_content);

	insertionSort(stuList, pLast);
	printList("Sorted Data by Name", stuList, pLast, format_title, format_content);

	insertionSortFinal(stuList);
	printList("Sorted Data by Final Score", stuList, pLast, format_title, format_content);
	return 0;
}

/*========================================================
Insertion Sort. [ by Student First Name ]
=========================================================
Pre   list[] must contain at least one element
size is index to last element in list
Post  list has been rearranged.
*/
void insertionSort(STUDENT  list[], STUDENT *pLast)
{
	STUDENT  temp;
	STUDENT *pCurr;
	STUDENT *pWalk;

	for (pCurr = list + 1; pCurr <= pLast; pCurr++)
	{
		temp = *pCurr;
		pWalk = pCurr - 1;
		while (pWalk >= list && strcmp(temp.name, pWalk->name) < 0)
		{
			*(pWalk + 1) = *pWalk;
			pWalk--;
		}
		*(pWalk + 1) = temp;
	}

}


/*=========================================================
insertionSortFinal()
============================================================
Sort in Descending order by Final Score
	Pre:   list[] must contain at least one element
		   pLast: last element of student array

	Post:  sorted list of students by final score
*/
void insertionSortFinal(STUDENT list[]) {
	STUDENT temp;
	STUDENT *p_current;
	STUDENT *p_walk;

	for(p_current = list + 1; p_current <= list + NUM_STU - 1; p_current++){
		temp = *p_current;	// copy current student to temp
		p_walk = p_current - 1; // save previous element
		while (p_walk >= list && (temp.final > p_walk->final)){
			*(p_walk + 1) = *p_walk;
			 *p_walk--;
		}
		*(p_walk + 1) = temp;	
	}
}


/*=========================================================
printList()
============================================================
Display list of students to output console

Pre:   list[] must contain at least one element
	   pLast: last element of student array
	   format_description: used in printf to format output

Post:  display to output console
*/
void printList(char title[], STUDENT  list[], STUDENT *pLast, char format_title[], char format_content[]) {

	printf("\n%s\n", title);
	printf(format_title, "Student Name", "Midterm 1", "Midterm 2", "Final");
	for(STUDENT *pStu = list; pStu <= pLast; pStu++)
	{
		printf(format_content,
			pStu->name,
			pStu->midterm[0],
			pStu->midterm[1],
			pStu->final);
	}
	printf("\n");
}


/*	================= Sample Output ================= */
/*
Unsorted Data
Student Name                   Midterm 1 Midterm 2    Final
Taylor, Noah                         85       94       92
Smith, Olivia                        91       89       86
Brown, Liam                          87       88       90
Davis, Emma                          96       88       97
Garcia, Mason                        79       93       92
Lopez, Sophia                        83       78       95


Sorted Data by Name
Student Name                   Midterm 1 Midterm 2    Final
Brown, Liam                          87       88       90
Davis, Emma                          96       88       97
Garcia, Mason                        79       93       92
Lopez, Sophia                        83       78       95
Smith, Olivia                        91       89       86
Taylor, Noah                         85       94       92


Sorted Data by Final Score
Student Name                   Midterm 1 Midterm 2    Final
Davis, Emma                          96       88       97
Lopez, Sophia                        83       78       95
Garcia, Mason                        79       93       92
Taylor, Noah                         85       94       92
Brown, Liam                          87       88       90
Smith, Olivia                        91       89       86

*/
