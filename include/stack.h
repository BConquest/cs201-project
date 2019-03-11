#ifndef __stack_h__
#define __stack_h__

#include <stdlib.h>
#include <stdio.h>

struct stackNode
{
	int data;
	struct stackNode* next;
};

int pop(struct stackNode **);

void push(struct stackNode **, int);

#endif
