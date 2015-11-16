#include<stdio.h>
#include<stdlib.h>
#include "huffman.h"
int main(int argc, char **argv)
{
	if(argc == 2)
	{
		encrypt(argv[1]);
	}
	else if(argc == 3)
	{
		decipher(argv[1], argv[2]);
	}
	else
	{
		printf("encrypt  a file use: %s file              \n",argv[0]);
		printf("decipher a file use: %s codefile keyfile  \n", argv[0]);
	}
	return 0;
}