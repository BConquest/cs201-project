#include "../include/queue.h"

void init(int *head, int *tail)
{
	*head = 0;
	*tail = 0;
}

void enqueue(int *queue, int *tail, int element)
{
	queue[(*tail)++] = element;
}

int dequeue(int *queue, int *head)
{
	return queue[(*head)++];
}

int empty(int head, int tail)
{
	return tail == head;
}

int full(int tail, const int size)
{
	return tail == size;
}
