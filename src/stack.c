#include "../include/stack.h"

int pop(struct stackNode **root)
{
	int buff;
	struct stackNode *temp;
	if (*root == NULL)
	{
		printf("STACK UNDERFLOW\n");
		return -1;
	}
	else
	{
		temp = *root;
		buff = temp->data;
		*root = temp->next;
		free(temp);
		return buff;
	}
}

void push(struct stackNode **top, int data)
{
	struct stackNode *newnode = malloc(sizeof(struct stackNode));

	if (newnode == NULL)
	{
		printf("STACK OVERFLOW\n");
	}
	else
	{
		newnode->data = data;
		newnode->next = (*top);
		(*top) = newnode;
	}
}
