#ifndef __queue_h__
#define __queue_h__

#include <stdio.h>

#include "./stack.h"

struct queue
{
	struct stackNode *stack1;
	struct stackNode *stack2;
};

void enqueue(struct queue *, int);
int dequeue(struct queue *);

void print(struct stackNode *, struct stackNode *);

#endif
