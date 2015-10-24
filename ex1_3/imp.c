#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include<malloc.h>

#include"myhead.h"

int Find(int tag, void *memory, void *args)
{
	Term *thisTerm = memory;
	Term *findTerm = args;
	if (thisTerm->e == findTerm->e)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int PrintItem(int tag, void *memory, void *args)
{
	Term *thisTerm = memory;
	if (thisTerm->c == 1)
	{
		printf("x^%d ", thisTerm->e);
	}
	else if (thisTerm->c == 0)
	{
	}
	else
	{
		printf("%dx^%d ", thisTerm->c, thisTerm->e);
	}
	return 0;
}

int FindInsertPosition(int tag, void *memory, void *args)
{
	Term *thisTerm = memory;
	Term *insertTerm = args;
	if (thisTerm->e < insertTerm->e)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void pause()
{
	printf("\nPress any key to continue...");
	setbuf(stdin, NULL);
	getchar();
}

void AddTerm(SLList *L)
{
	Term newTerm = { 0 };
	printf("Please input the c: ");
	scanf("%d", &(newTerm.c));
	printf("Please input the e: ");
	scanf("%d", &(newTerm.e));
	if (newTerm.c != 0)
	{
		SLList *find = SLWalk(L, Find, &newTerm);
		if (find == NULL)  /* �������������, �Ѹ�����뵽������, ��������������  */
		{
			SLList *insertPos = SLWalk(L, FindInsertPosition, &newTerm); /* Ѱ�Ҳ���λ�� */
			if (insertPos == NULL)
			{
				SLAppend(L, 0, &newTerm, sizeof(Term));
			}
			else
			{
				SLAdd(SLGetPri(L, insertPos), 0, &newTerm, sizeof(Term));
			}

		}
		else  /* �����Ѵ�����������, ��ϲ����� */
		{
			Term *oldTerm = SLGetData(find, NULL, NULL);
			newTerm.c += oldTerm->c;
			if (newTerm.c == 0)  /* ����ϲ��� ϵ��Ϊ0, ��ɾ������ */
			{
				SLDeleteNext(SLGetPri(L, find));
			}
			else
			{
				SLUpdate(find, 0, &newTerm, sizeof(Term));
			}
		}
	}
}

void Combine(SLList *L1, SLList *L2, int commond) /* commond: 1��ʾ���, 2��ʾ��� */
{
	SLList *L = NULL;
	SLInit(&L);
	SLList *head = L1;
	while (head->next != NULL)
	{
		head = head->next;
		SLAppend(L, head->tag, head->object, head->size);
	}
	head = L2;

	while (head->next != NULL)
	{
		head = head->next;
		SLList *find = SLWalk(L, Find, head->object);
		if (find == NULL) /* ������û�д��� */
		{
			SLList *insertPos = SLWalk(L, FindInsertPosition, head->object);
			if (insertPos == NULL) /* ������β */
			{
				SLAppend(L, head->tag, head->object, head->size);
			}
			else  /* instet before insertPos */
			{
				SLAdd(SLGetPri(L, insertPos), head->tag, head->object, head->size);
			}
		}
		else  /*�������Ѵ��ڴ��� */
		{
			Term *oldTerm = find->object;
			Term *newTerm = head->object;
			if (commond == 1)
			{
				oldTerm->c += newTerm->c;
			}
			else if (commond == 2)
			{
				oldTerm->c -= newTerm->c;
			}

			if (oldTerm->c == 0)
			{
				SLDeleteNext(SLGetPri(L, find));
			}
			else
			{
				SLUpdate(L, 0, oldTerm, sizeof(Term));
			}
		}
	}
	SLWalk(L, PrintItem, NULL);
	SLDestory(L);
}

void menu()
{
	printf(" ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ \n");
	printf("      1.show a             \n");
	printf("      2.show b                 \n");
	printf("      3.show a+b                         \n");
	printf("      4.show a-b                        \n");
	printf("      5.add a term to a          \n");
	printf("      6.add a term to b          \n");
	printf("      0.exit                       \n");
	printf(" ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ \n");
}