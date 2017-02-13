/*******************************************************
    Examples: 3.15 - 3.19 - class
    Driver program to demonstrate hashing using
    collision resolution by chaining.

    hash - has two parameters
    insert - minor modification
    traverse - using STUDENTREC * instead of STUDENTREC **
/*******************************************************/

#include <stdio.h>
#include <stdlib.h>  // malloc(), free(), exit()
#include <string.h>

#define NUMPOINTERS 5

typedef struct node STUDENTREC;
struct node
{
    char ss[10];
    struct node *next;
};

int main (void)
{
    int hash(char ss[], int size);
    STUDENTREC *insert(char ss[],
                   STUDENTREC *student_body[],
                   int hashval);
    void traverse(STUDENTREC *student_body[]);

    STUDENTREC *student_body[NUMPOINTERS] = {NULL};
    STUDENTREC *person;
    char ss[10];
    int hashval;

    while(printf("Enter Social Security Number: "), strcmp(gets(ss), "quit"))
    {
        hashval = hash(ss, NUMPOINTERS);
        person = insert(ss, student_body, hashval);
        if (person) // not NULL => duplicate
        {
            printf("Duplicate record!\n");
        }
        else
        {
            printf("%s has been placed in the list at location %d.\n",
                ss, hashval);
        }
    }
    traverse(student_body);
    return 0;
}
/***************************************************
    Hash Social Security number by summing the cubes
    of the ASCII value of characters and then take
    the modulo of this sum.
*/
int hash(char ss[], int size)
{
    long sum = 0;

    while (*ss) // != '\0'
    {
        sum += *ss * *ss * *ss;
        ss++;
    }
    return sum % size;
}

/***************************************************
    Insert a new Social Security number into the
    array of student records, at index equal to
    hashvalue
*/
STUDENTREC *insert(char ss[],
                   STUDENTREC *student_body[],
                   int hashval)
{
    STUDENTREC **mover;

    mover = &student_body[hashval];
    while (*mover)
    {
        if (strcmp(ss,(*mover)->ss) == 0) return *mover;
        mover = &((*mover)->next);
    }
    if ((*mover = (STUDENTREC *) malloc(sizeof(STUDENTREC))) == NULL)
    {
        printf("Malloc error in insert!\n");
        exit(1);
    }
    strcpy((*mover)->ss, ss);
    (*mover)->next = NULL;    // set the link of the new node to NULL
    // printf("%s has been placed in the list at location %d.\n", (*mover)->ss, hashval);
    // move the printf in main() - to have all printing in one place
    return NULL;
}
/***************************************************
    Traversing the lists in a hash table
*/
void traverse(STUDENTREC *student_body[])
{
    int i;
    //STUDENTREC **mover;  // Use ** for fun and practice
    STUDENTREC *mover;

    for (i = 0; i < NUMPOINTERS; i++)
    {
        printf("Contents of list %2d\n", i);
        printf("--------------------\n");
        for (mover = student_body[i]; mover; mover = mover->next)
        {
            printf("%s\n", mover->ss);
        }
        printf("\n");
    }
    return;
}
