#ifndef __stack2_h__
#define __stack2_h__

#include <stdio.h>
#include <stdlib.h>

struct stackNode
{
    int data;
    struct stackNode* next;
};

struct stackNode* newNode(int);
int isEmpty(struct stackNode *);

void push(struct stackNode **, int);
int pop(struct stackNode **);

#endif