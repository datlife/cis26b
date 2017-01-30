/***************************************************
    Examples: 3.14
    Programmer-Controlled Memory Management
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
    NODE *get_node(NODE **stack); // Programmer-Controlled Memory Management

    //NODE *init_list(void);
    NODE *init_list(NODE **stack);
    //int   insert(NODE *list, char *data);
    int   insert(NODE *list, NODE **stack, char *data);
    //int   delete(NODE *list, char *data);
    int   delete(NODE *list, NODE **stack, char *data);
    void  traverse(NODE *list);

    NODE *stack = NULL;   // to keep track of the deleted nodes
    NODE *list, *nodeptr;
    char data[20];
    int  found, duplicate;

    // build list
    //list = init_list();
    list = init_list(&stack);
    while (printf("Enter string(or quit): "), gets(data),
           strcmp(data, "quit"))
    {
        //duplicate = insert(list, data);
        duplicate = insert(list, &stack, data);
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
        //found = delete(list, data);
        found = delete(list, &stack, data);
        printf("\"%s\" %s\n", data, found ? "deleted!" : "not found!");
    }

    // print out strings in list nodes
    traverse(list);

    printf("\n\nTesting INSERT: \n");
    while (printf("Enter string(or quit): "), gets(data),
           strcmp(data, "quit"))
    {
        //duplicate = insert(list, data);
        duplicate = insert(list, &stack, data);
        if(duplicate)
        {
            printf("\"%s\" already in the list!\n", data);
        }
    }
    // print out strings in list nodes
    traverse(list);

    printf("\n\nTesting DELETE again:\n");
    while (printf("Enter string(or quit): "), gets(data),
           strcmp(data, "quit"))
    {
        //found = delete(list, data);
        found = delete(list, &stack, data);
        printf("\"%s\" %s\n", data, found ? "deleted!" : "not found!");
    }

    // print out strings in list nodes
    traverse(list);
    // memory leak: call the destroy function here
    return 0;
}
/***************************************************
    Gets a free node from the free stacl (if not
    empty) or from a malloc'ed block of structs
*/
NODE *get_node(NODE **stack)
{
    //#define BLOCKSIZE 100
    #define BLOCKSIZE 3

    static NODE *block = NULL, *blockrear;
    NODE *first;

    if (*stack != NULL) // pop node off the free stack
    {
        first = *stack;
        *stack = (*stack)->next;
        first->next = NULL; // detach from stack
    }
    else if (block != NULL) // get node from block
    {
        first = block;
        if (block == blockrear) block = NULL;
        else block++;   // move to the next struct
    }
    else // stack and block are NULL!
    {
        if ((block = (NODE *) malloc(BLOCKSIZE * sizeof(NODE))) == NULL)
        {
            printf("Fatal malloc error in get_node!\n");
            exit(1);
        }
        memset(block, 0, BLOCKSIZE * sizeof(NODE));
        blockrear = block + BLOCKSIZE - 1;
        first = block;
        block++;
    }
    return first;
}


/***************************************************
    Initialization of a linked list with two
    sentinel nodes
*/
//NODE *init_list(void)
NODE *init_list(NODE **stack)
{
    NODE *list;

    // allocate the first sentinel node
    /*
    list = (NODE *) malloc(sizeof (NODE));
    if (!list)
    {
        printf("Error in init_list!\n");
        exit(1);
    }
    */
    list = get_node(stack);
    list->data[0] = '\0';

    // allocate the last sentinel node
    /*
    list->next = (NODE *) malloc(sizeof (NODE));
    if (!(list->next))
    {
        printf("Error in init_list!\n");
        exit(2);
    }
    */
    list->next = get_node(stack);
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
//int insert(NODE *list, char *data)
int   insert(NODE *list, NODE **stack, char *data)
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
        /*
        pnew = (NODE *) malloc(sizeof (NODE));
        if (!pnew)
        {
            printf("Fatal memory allocation error in insert!\n");
            exit(3);
        }
        */
        pnew = get_node(stack);
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
//int delete(NODE *list, char *data)
int   delete(NODE *list, NODE **stack, char *data)
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
        //free(curr);         // DO NOT FREE!
        curr->next = *stack;  // push the node onto the free stack!
        *stack = curr;
    }
    return found;
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














