/*
Keep track of all line numbers where a Node in BST appears
*/
#ifndef QUEUE_HW5_H
#define QUEUE_HW5_H
#include <stdio.h>
#include <stdlib.h>

typedef struct queueNode {
	int line_number;
	struct queueNode *next;
}QueueNode;

int enqueue(QueueNode **front, QueueNode **rear, int num);
QueueNode *dequeue(QueueNode *front, QueueNode *rear);
#endif // !QUEUE_HW5_H

