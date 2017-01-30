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
    NODE *dequeue(NODE **queue, NODE **rear);
    void  enqueue(NODE **queue, NODE **rear, int data);

    NODE *queue = NULL, *rear = NULL;
    NODE *front;

    enqueue(&queue, &rear, 3);
    enqueue(&queue, &rear, 4);
    enqueue(&queue, &rear, 5);

    front = dequeue(&queue, &rear);
    if (front)
    {
        printf("Front node of queue is %d\n", front->data);
        free(front);
    }
    else printf("Empty queue!\n");

    front = dequeue(&queue, &rear);
    if (front)
    {
        printf("Front node of queue is %d\n", front->data);
        free(front);
    }
    else printf("Empty queue!\n");


    front = dequeue(&queue, &rear);
    if (front)
    {
        printf("Front node of queue is %d\n", front->data);
        free(front);
    }
    else printf("Empty queue!\n");

    front = dequeue(&queue, &rear);
    if (front)
    {
        printf("Front node of queue is %d\n", front->data);
        free(front);
    }
    else printf("Empty queue!\n");

    return 0;
}
/***************************************************
    Queue Insert: insert at the end
*/
void enqueue(NODE **queue, NODE **rear, int data)
{
    NODE *pnew;

    pnew = (NODE *) malloc(sizeof (NODE));
    if (!pnew)
    {
        printf("... error in enqueue!\n");
        exit(1);
    }
    pnew->data = data;
    pnew->next = NULL;
    if (*queue == NULL) *queue = pnew;
    else (*rear)->next = pnew;
    *rear = pnew;
    return;
}

/***************************************************
    Queue Delete: remove the first node
*/
NODE *dequeue(NODE **queue, NODE **rear)
{
    NODE *first;

    if (*queue == NULL) return NULL;
    first = *queue;
    *queue = (*queue)->next;
    if (*queue == NULL) *rear = NULL;
    first->next = NULL;

    return first;
}
