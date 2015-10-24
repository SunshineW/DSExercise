#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<malloc.h>
#include<assert.h>

#include"myhead.h"

int PrintStaff(int tag, void *memory, void *args)
{
	Staff *s = memory;
	assert(tag == 0);
	printf("%-10s %-10s %-15s\n", s->id, s->name, s->tel);
	return 0;
}

int FindStaff(int tag, void *memory, void *args)
{
	Staff *thisStaff = memory;
	Staff *s = args;
	assert(tag == 0);
	if (strcmp(s->id, thisStaff->id) == 0)
	{
		return -1;
	}
	else
	{
		return 0;
	}	
}

void pause()
{
	printf("Press any key to continue...");
	setbuf(stdin, NULL);
	getchar();
}

void ShowStaff(SLList *L)
{
	if (GetLength(L) == 0)
	{
		printf("no staff!\n");
	}
	else
	{
		printf("%-10s %-10s %-15s\n","id","name", "tel");
		SLWalk(L, PrintStaff, NULL);
	}
}

void AddStaff(SLList *L)
{
	int result = SL_SUCCESS;
	Staff newStaff = { 0 };
	printf("Please input the name: ");
	scanf("%s", newStaff.name);
	printf("Please input the tell: ");
	scanf("%s", newStaff.tel);
	sprintf(newStaff.id, "%d", ++staffID);
	result = SLAppend(L, 0, &newStaff, sizeof(Staff));
	if (result == SL_SUCCESS)
	{
		printf("add success!\n");
	}
	else
	{
		printf("add failure!\n");
	}
}

void DelStaff(SLList *L)
{
	SLList *removed = NULL;
	Staff p = { 0 };
	printf("please input the num: ");
	scanf("%s", p.id);
	removed = SLWalk(L, FindStaff, &p);
	if (removed == NULL)
	{
		printf("Do not exits!\n");
	}
	else
	{
		SLDeleteNext(SLGetPri(L,removed));
		printf("delete success!\n");
	}
}

void UpdateStaff(SLList *L)
{
	int result = SL_SUCCESS;
	SLList *oldStaff = NULL;
	Staff newStaff = { 0 };
	printf("please input the num: ");
	scanf("%s", newStaff.id);
	oldStaff = SLWalk(L, FindStaff, &newStaff);
	if (oldStaff == NULL)
	{
		printf("Do not exits!\n");
	}
	else
	{
		printf("Please input new name: ");
		scanf("%s", newStaff.name);
		printf("pleae input new tel: ");
		scanf("%s", newStaff.tel);
		result = SLUpdate(oldStaff, 0, &newStaff, sizeof(Staff));
		if (result == SL_SUCCESS)
		{
			printf("update success!\n");
		}
	}
}

int GetLength(SLList *L)  /* 节点的个数(不包括头结点) */
{
	int length = 0;
	SLList *head = L;
	while (head->next != NULL)
	{
		head = head->next;
		length++;
	}
	return length;
}

void Length(SLList *L)
{
	printf("Length is %d\n", GetLength(L));
}

void Insert(SLList *L)
{
	int result = SL_SUCCESS;
	int pos = 0;
	printf("the position you want to set: ");
	scanf("%d", &pos);
	if (pos > GetLength(L) || pos < 0)
	{
		printf("bad position!\n");
	}
	else
	{
		Staff newStaff = { 0 };
		printf("Please input the name: ");
		scanf("%s", newStaff.name);
		printf("Please input the tell: ");
		scanf("%s", newStaff.tel);
		sprintf(newStaff.id, "%d", ++staffID);
		SLList *head = L;
		int i = 0;
		for (i = 0; i < pos-1; i++)
		{
			head = head->next;
		}
		result = SLAdd(head, 0, &newStaff, sizeof(Staff));
		if (result == SL_SUCCESS)
		{
			printf("Insert success!\n");
		}
	}
}

void menu()
{
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("           1.show           \n");
	printf("           2.add            \n");
	printf("           3.delete         \n");
	printf("           4.update          \n");
	printf("           5.get numbers     \n");
	printf("           6.insert         \n");
	printf("           0.exit           \n");
	printf(" ~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

}