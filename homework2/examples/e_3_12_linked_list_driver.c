/***************************************************
    Examples: 3.7 - 3.12
    This program initializes, inserts into, deletes
    from, searches, and traverses an ordered linked
    list with a string key.
/***************************************************/

#include <stdio.h>
#include <stdlib.h>  // malloc(), free(), exit()
#include <string.h>

#define DUMMY_TRAILER '\177'
                // octal ASCII code of the
                // last character in the ASCII table

typedef struct node NODE;
struct node
{
    char  data[20];
    NODE *next;
};

int main (void)
{
    NODE *init_list(void);
    int   insert(NODE *list, char *data);
    int   delete(NODE *list, char *data);
    NODE *find(NODE *list, char *data);
    void  traverse(NODE *list);

    NODE *list, *nodeptr;
    char data[20];
    int  found, duplicate;

    // build list
    list = init_list();
    while (printf("Enter string(or quit): "), gets(data),
           strcmp(data, "quit"))
    {
        duplicate = insert(list, data);
        if(duplicate)
        {
            printf("\"%s\" already in the list!\n", data);
        }
    }
    // print out strings in list nodes
    traverse(list);

    printf("\n\nTesting INSERT: \n");
    while (printf("Enter string(or quit): "), gets(data),
           strcmp(data, "quit"))
    {
        duplicate = insert(list, data);
        if(duplicate)
        {
            printf("\"%s\" already in the list!\n", data);
        }
    }
    // print out strings in list nodes
    traverse(list);

    printf("\n\nTesting DELETE:\n");
    while (printf("Enter string(or quit): "), gets(data),
           strcmp(data, "quit"))
    {
        found = delete(list, data);
        printf("\"%s\" %s\n", data, found ? "deleted!" : "not found!");
    }

    // print out strings in list nodes
    traverse(list);

    printf("\n\nTesting SEARCH:\n");
    while (printf("Enter string(or quit): "), gets(data),
           strcmp(data, "quit"))
    {
        nodeptr = find(list, data);
        if (nodeptr)
        {
             printf("\"%s\" found\n", nodeptr->data);
        }
        else
        {
            printf("\"%s\" not found\n", data);
        }

    }

    // memory leak: call the destroy function here
    return 0;
}
/***************************************************
    Initialization of a linked list with two
    sentinel nodes
*/
NODE *init_list(void)
{
    NODE *list;

    // allocate the first sentinel node
    list = (NODE *) malloc(sizeof (NODE));
    if (!list)
    {
        printf("Error in init_list!\n");
        exit(1);
    }
    list->data[0] = '\0';

    // allocate the last sentinel node
    list->next = (NODE *) malloc(sizeof (NODE));
    if (!(list->next))
    {
        printf("Error in init_list!\n");
        exit(2);
    }
    list->next->data[0] = DUMMY_TRAILER;
    list->next->data[1] = '\0';
    list->next->next = NULL;

    return list;
}

/***************************************************
    Insert a node in a sorted linked list
        return 1 - if duplicate
        return 0 - otherwise
*/
int insert(NODE *list, char *data)
{
    NODE *curr = list->next;
    NODE *prev = list;
    NODE *pnew;
    int   duplicate = 1;

    // search
    while (strcmp(data,curr->data) > 0)
    {
        prev = curr;
        curr = curr->next;
    }

    if (strcmp(data, curr->data) )
    {
        duplicate = 0; // not a duplicate
        pnew = (NODE *) malloc(sizeof (NODE));
        if (!pnew)
        {
            printf("Fatal memory allocation error in insert!\n");
            exit(3);
        }
        strcpy(pnew->data, data);
        pnew->next = curr;
        prev->next = pnew;
    }
    return duplicate;
}

/***************************************************
    Delete a node from a sorted linked list
        return 0 - not found
        return 1 - found and deleted
*/
int delete(NODE *list, char *data)
{
    NODE *curr = list->next;
    NODE *prev = list;
    int   found = 0;

    // search
    while (strcmp(data, curr->data) > 0)
    {
        prev = curr;
        curr = curr->next;
    }
    if (strcmp(data, curr->data) == 0)
    {
        found = 1;
        prev->next = curr->next;
        free(curr);
    }
    return found;
}

/***************************************************
    Find a node in a sorted linked list
        return NULL - not found
        return pointer to the node - found
*/
NODE *find(NODE *list, char *data)
{
    list = list->next; // skip the dummy node
    while (strcmp(data, list->data) > 0)
    {
        list = list->next;
    }
    return strcmp(data, list->data) == 0 ? list : NULL;
}

/***************************************************
    Traverse a linked list to print out the
    contents of each node
*/
void traverse(NODE *list)
{
    list = list->next; // skip the dummy node
    while (list->data[0] != DUMMY_TRAILER)
    {
        printf("%s\n", list->data);
        list = list->next;
    }
    return;
}














