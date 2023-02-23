#include "stack.h"


Stack* initStack()
{
	Stack* s = (Stack*)malloc(sizeof(Stack));
	s->size = 0;
	s->top = NULL;
	return s;
}


void destroyStack(Stack* s)
{
	if(s != NULL)
	{
		//Empty stack
		while(s->size != 0)
			pop(s);
	}
	
	//free stack
	free(s);
}

void emptyStack(Stack* s)
{
	if(s != NULL)
	{
		//Empty stack
		while(s->size != 0)
			pop(s);
	}

}


void push(Stack* s,void* content)
{
	if(s != NULL)
	{
		//Create new node
		Node* new_node = (Node*)malloc(sizeof(Node));
		new_node->content = content;
		new_node->prev = s->top;
		
		//Update stack
		s->top = new_node;
		s->size++;
	}
}


void* pop(Stack* s)
{
	void* value = NULL;
	if(s != NULL)
	{
		if(s->top != NULL || s->top != 0)
		{
			Node* to_remove = s->top;
			value = s->top->content;
			s->top = s->top->prev;
			s->size--;
			free(to_remove);
		}
		else
		{
			printf("[STACK] pop em uma pilha vazia!!");
			exit(1);
		}
		
	}
	
	return value;
}

