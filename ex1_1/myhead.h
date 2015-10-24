#ifndef EX1_1_H_
#define EX1_1_H_

#include"lib/sllist.h"

static int staffID = 10000;

typedef struct Staff
{
	char id[8];
	char name[10];
	char tel[15];
}Staff;

int PrintStaff(int tag, void *memory, void *args);

int FindStaff(int tag, void *memory, void *args);

int GetLength(SLList *L);  /* not include the head node */

void pause();

void ShowStaff(SLList *L);

void AddStaff(SLList *L);

void DelStaff(SLList *L);

void UpdateStaff(SLList *L);

void Length(SLList *L);

void Insert(SLList *L);

void menu();

#endif
