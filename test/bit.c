#include<stdio.h>
int main(int argc, char **argv)
{
	int i;
	for(i=0; i<9; i++)
	{
		unsigned char a = 0;
		a |= (1<<i);
		/* a = a | (1 << i) */
		printf("%d\n",a);
	}
	return 0;
}