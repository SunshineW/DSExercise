#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
#include<assert.h>

typedef struct Strack
{
	int size;
	int top;
	char *listarray;
}Strack;

void init(Strack *S, int size)
{
	S->listarray = malloc(size);
	S->size = size;
	S->top = 0;
}

void clear(Strack *S)
{
	S->top = 0;
}

void push(Strack *S, char c)
{
	assert(S->top < S->size);
	S->listarray[(S->top)++] = c;
}

char pop(Strack *S)
{
	assert(!isEmpty(S));
	return S->listarray[--(S->top)];
}

int isEmpty(Strack *S)
{
	return S->top == 0 ? 1 : 0 ;
}

char topValue(Strack *S)
{
	assert(isEmpty(S)!= 1);
	return S->listarray[(S->top)-1];
}


int main()
{
	int i;
	int size;
	Strack L;
	char buf[256] = {0};
	printf("please input a word: ");
	scanf("%s", buf);
	size = strlen(buf);
	init(&L, size);
	for(i=0;i < size/2; i++)
	{
		push(&L, buf[i]);
	}
	for(i=(size+1)/2; i<size; i++)
	{
		if(topValue(&L) == buf[i])
		{
			pop(&L);
		}
		else
		{
			printf("NO\n");
			return 0;
		}
	}
	printf("YES\n", buf);
	return 0;
}
