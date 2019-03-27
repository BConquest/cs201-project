#include "../include/queue.h"

void print(struct stackNode *master, struct stackNode *notmaster)
{
	while (master != NULL)
	{
		printf("%d -> ", master->data);
		master = master->next;
	}

	while (notmaster != NULL)
	{
		printf("%d -> ", notmaster->data);
		notmaster = notmaster->next;
	}
	printf("\n");
}

void enqueue(struct queue *q, int key)
{
	push(&q->stack1, key);
}

int dequeue(struct queue *q)
{
	int x;
	if (q->stack1 == NULL && q->stack2 == NULL)
	{
		printf("QUEUE IS EMPTY\n");
		return -1;
	}

	if (q->stack2 == NULL)
	{
		while (q->stack1 != NULL)
		{
			x = pop(&q->stack1);
			push(&q->stack2, x);
		}
	}
	x = pop(&q->stack2);
	return x;
}
