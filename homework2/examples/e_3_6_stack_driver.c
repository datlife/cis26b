/***************************************************
    Example 3.6
    Driver program for stack and queue functions

/***************************************************/

#include <stdio.h>
#include <stdlib.h>

typedef struct node NODE;
struct node
{
    int          data;
    struct node *next;
};

int main (void)
{
    NODE *push(NODE *stack, int data);
    NODE *pop(NODE **stack);

    NODE *stack = NULL;
    NODE *top;

    stack = push(stack, 3);
    stack = push(stack, 4);
    stack = push(stack, 5);

    top = pop(&stack);
    if (top)
    {
        printf("Top node of stack is %d\n", top->data);
        free(top);
    }
    else printf("Empty stack!\n");

    top = pop(&stack);
    if (top)
    {
        printf("Top node of stack is %d\n", top->data);
        free(top);
    }
    else printf("Empty stack!\n");

    top = pop(&stack);
    if (top)
    {
        printf("Top node of stack is %d\n", top->data);
        free(top);
    }
    else printf("Empty stack!\n");

    top = pop(&stack);
    if (top)
    {
        printf("Top node of stack is %d\n", top->data);
        free(top);
    }
    else printf("Empty stack!\n");


    return 0;
}
/***************************************************
    Stack Insert: insert in the beginning
*/
NODE *push(NODE *stack, int data)
{
    NODE *pnew;

    pnew = (NODE *) malloc(sizeof (NODE));
    if (!pnew)
    {
        printf("... error in push!\n");
        exit(1);
    }
    pnew->data = data;
    pnew->next = stack;
    stack = pnew;

    return stack;
}

/***************************************************
    Stack Delete: delete the first node
*/
NODE *pop(NODE **stack)
{
    NODE *first;

    if (*stack == NULL) return NULL;
    first = *stack;
    *stack = (*stack)->next;
    first->next = NULL;

    return first;
}
