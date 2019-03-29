#include "../include/stack2.h"

struct stackNode* newNode(int data)
{
    struct stackNode* stackNode =
              (struct stackNode*) malloc(sizeof(struct stackNode));
    stackNode->data = data;
    stackNode->next = NULL;
    return stackNode;
}

int isEmpty(struct stackNode *root)
{
    return !root;
}

void push(struct stackNode** root, int data)
{ 
    struct stackNode* stackNode = newNode(data);
    stackNode->next = *root;
    *root = stackNode;
}

int pop(struct stackNode** root)
{
    if (isEmpty(*root))
        return -1;
    struct stackNode* temp = *root;
    *root = (*root)->next;
    int popped = temp->data;
    free(temp);

    return popped;
}