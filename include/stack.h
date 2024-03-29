#ifndef __stack_h__
#define __stack_h__

#include <stdio.h>
#include <stdlib.h>
/*
https://www.geeksforgeeks.org/stack-data-structure-introduction-program/
*/
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