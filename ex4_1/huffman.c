#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<assert.h>

#include "huffman.h"

/* 统计文本中字符出现的次数并存储到letter中 
  返回的是出现的字符种类数 */
int wighted_count(letter_t *letter, char *filename)
{
	int count[128] = {0};
	letter_t temp[128] = {0};
	int size = 0;
	int i, j;
	
	FILE *fp = fopen(filename, "r");
	if (fp == NULL)
	{
		printf("open %s failed\n", filename);
		exit(1);
	}
	while(1)
	{
		int a = fgetc(fp);
		if (feof(fp) != 0)
		{
			break;
		}
		if (a>127 || a < 0)
		{
			continue;
		}
		count[a]++;
	}
	fclose(fp);
	
	for(i=0; i<128; i++)
	{
		if (count[i] != 0)
		{
			temp[size].data = i;
			temp[size].wighted = count[i];
			size++;
		}
	}
	
	memset(letter, 0, sizeof(letter_t) * size);
	for (i=0; i<size; i++)
	{
		for(j=i; j<size; j++)
		{
			if (temp[i].wighted >temp[j].wighted)
			{
				letter_t exchange = temp[i];
				temp[i] = temp[j];
				temp[j] = exchange;
			}
		}
		letter[i] = temp[i];
	}
	return size;
}

/* 从key文件中读取权值 */
int read_wighted(letter_t *letter, char *filename)
{
	FILE *fp;
	fp = fopen(filename, "rb");
	if (fp == NULL)
	{
		printf("open %s failed\n", filename);
		exit(1);
	}
	int count=0;
	while(1)
	{
		
		fread(&(letter[count]), sizeof(letter_t), 1, fp);
		if(feof(fp))
		{
			break;
		}
		count++;
	}
	fclose(fp);
	return count;
}

/* 保存权值到文件  */
int save_wighted(letter_t *letter, char *filename, int size)
{
	int ret;
	FILE *fp;
	fp = fopen(filename, "wb");
	if (fp == NULL)
	{
		printf("creat key file failed\n");
		exit(1);
	}
	ret = fwrite(letter, sizeof(letter_t), size, fp);
	if (ret != size)
	{
		printf("write wrighted failed\n");
		exit(1);
	}
	fclose(fp);
	return 0;
}

int creat_tree(HTnode_t *tree, letter_t *letter, int size)
{
	int i, j, tree_size;
	tree_size = size * 2 - 1;
	
	for (i=0; i< size; i++)
	{
		tree[i].data = letter[i].data;
		tree[i].wighted = letter[i].wighted;
		tree[i].left = tree[i].right = -1;
		tree[i].parent = 0;
	}
	for(i=size; i<tree_size; i++)
	{
		tree[i].data = '*';
		tree[i].wighted = 0;
		tree[i].left = tree[i].right = -1;
		tree[i].parent = 0;
	}
	
	/* 构建好哈弗曼树结构 */
	for (i=size; i< tree_size; i++)
	{
		int min1, min2; /* 权值最小的两个 min1<min2 */
		                
		/*初始化 min1, min2 */
		for (j=0; j<i; j++)
		{
			if (tree[j].parent == 0)
			{
				break;
			}
		}
		min1 = j;
		
		for(j=j+1; j<i; j++)
		{
			if (tree[j].parent == 0)
			{
				break;
			}			
		}
		min2 = j; 
		
		for(j=j+1; j<i; j++) /* loop1: 求数组中最小的两个数*/
		{
			if(tree[j].parent == 0)
			{
				if (tree[j].wighted < tree[min2].wighted)
				{
					if (tree[j].wighted < tree[min1].wighted)
					{
						min2 = min1;
						min1 = j;
					}
					else
					{
						min2 = j;
					}
				}
			}
		} /* end of loop1 */

		tree[i].wighted = tree[min1].wighted + tree[min2].wighted;
		tree[i].left = min1;
		tree[i].right = min2;
		tree[min1].parent = i;
		tree[min2].parent = i;
	}
	
	/* 把哈弗曼编码写入节点中 */
	for(i=size*2 -2 ; i >= 0; i--)
	{
		char buf[32];
		memset(buf, '0', 32);
		int parent = tree[i].parent;
		int child = i;
		j = 31;
		while(parent != 0)
		{
			if (tree[parent].left == child)
			{
				buf[j]='1';
			}
			else
			{
				buf[j]='0';
			}
			child = parent;
			parent = tree[parent].parent;
			j--;
		}
		memcpy(tree[i].code, buf + j + 1, 31 - j);
		tree[i].code[31- j] = '\0';
	}

}

int print_tree(HTnode_t *tree, int size)
{
	int i;
	int tree_size = size * 2 -1;
	printf("%-4s%-8s%-6s%-16s%-7s%-7s%-7s%s\n", "pos", "wighted", "ascii", "code", "parent", "left", "right", "character");
	for(i=0; i<tree_size; i++)
	{
		//if (tree[i].left != -1)
		{
			printf("%-4d%-8d%-6d%-16s%-7d%-7d%-7d%c\n", i, tree[i].wighted, tree[i].data,tree[i].code, tree[i].parent, tree[i].left, tree[i].right, tree[i].data);
		}
	}
	return 0;
}


int save_code_to_file(HTnode_t *tree, int size, char *sourcefile, char *dest)
{
	FILE *r = fopen(sourcefile, "r");
	if (r == NULL)
	{
		printf("source file open failed\n", sourcefile);
		exit(1);
	}
	FILE *w = fopen(dest, "w");
	if (w == NULL)
	{
		printf("creat %s failed\n", dest);
		exit(1);
	}
	while(1)
	{
		int a = fgetc(r);
		if (feof(r) != 0)
		{
			break;
		}
		int i, j;
		for(i=size-1; i>=0; i--)
		{

			if (a == tree[i].data)
			{
				fprintf(w, "%s", tree[i].code);
				break;
			} 
		}
	}
	fclose(r);
	fclose(w);
}

int print_code_to_terminal(HTnode_t *tree, char *sourcefile, int size)
{
	int tree_size = size * 2 - 1;
	FILE *r = fopen(sourcefile, "r");
	if (r == NULL)
	{
		printf("file %s open failed\n", sourcefile);
		exit(1);
	}
	while(1)
	{
		int find = tree_size -1;
		while(1)
		{
			if(tree[find].left == -1)
			{
				printf("%c", tree[find].data);
				break;
			}
			else
			{	
				int a = fgetc(r);
				if (feof(r) != 0)
				{
					goto end;
				}
				if (a == '0')
				{
					find = tree[find].right;
				}
				else
				{
					find = tree[find].left;
				}
			}
		}
	}
end:
	fclose(r);
}

/*对flename文件进行加密，加密后的文件存储为filname.code,
  解密用到的文件存储为filename.key */
void encrypt(char *filename)
{
 	letter_t letter[128];
	char codename[128];
	char keyname[128];
	sprintf(codename, "%s%s", filename, ".code");
	sprintf(keyname, "%s%s", filename, ".key");
	
	int size = wighted_count(letter, filename);

	HTnode_t tree[size * 2 - 1];
	creat_tree(tree, letter, size);
	
	save_wighted(letter, keyname, size);
	save_code_to_file(tree, size, filename, codename);
	printf("%s encrypt success\n", filename);
	printf("the transrom file is %s, the key file is %s\n", codename, keyname);
}

/* 对文件进行解密并打印 */
void decipher(char *sourcefile, char *keyfile)
{
	letter_t letter[128];
	int size = read_wighted(letter, keyfile);
	HTnode_t tree[size * 2 - 1];

	creat_tree(tree, letter, size);
	print_code_to_terminal(tree, sourcefile, size);
	printf("\n");

}