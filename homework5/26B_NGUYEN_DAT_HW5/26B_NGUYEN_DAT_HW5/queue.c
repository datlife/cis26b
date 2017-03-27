#include "queue.h"

int enqueue(QueueNode **front, QueueNode **rear, int num){

	// Assumption: since we inserted new line in order, I only compare to the rear Node if
	// the new line number is already existed.
	if (*rear != NULL && num == (*rear)->line_number)
		return 1;
	QueueNode *pnew = (QueueNode *)malloc(sizeof(QueueNode));
	if (!pnew)
	{
		printf("... error in enqueue!\n");
		exit(1);
	}
	pnew->line_number = num;
	pnew->next = NULL;
	if (*front == NULL) *front = pnew;
	else (*rear)->next = pnew;
	*rear = pnew;
	return 0;
}

QueueNode *dequeue(QueueNode *front, QueueNode *rear) {
	return NULL;
}