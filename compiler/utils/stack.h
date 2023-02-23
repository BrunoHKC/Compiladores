#ifndef __STACK__
#define __STACK__

#include <stdlib.h>
#include <stdio.h>


typedef struct Node
{
	struct Node* prev;
	void* content;

} Node;


typedef struct Stack
{
	int size;
	Node* top;

} Stack;


Stack* initStack();
void emptyStack(Stack* s);
void destroyStack(Stack* s);
void push(Stack* s,void* content);
void* pop(Stack* s);

#endif
