#ifndef HUFFMAN_H_
#define HUFFMAN_H_

typedef struct
{
	char data;
	int wighted;
}letter_t;

typedef struct HTnode_t
{
	char code[32];
	char data;
	int wighted;
	int parent, left, right;
}HTnode_t;

/* 统计文本中字符出现的次数并存储到letter中 
  返回的是出现的字符种类数 */
int wighted_count(letter_t *letter, char *filename);

/* 从key文件中读取权值 */
int read_wighted(letter_t *letter, char *filename);

/* 保存权值到文件  */
int save_wighted(letter_t *letter, char *filename, int size);

int creat_tree(HTnode_t *tree, letter_t *letter, int size);

int print_tree(HTnode_t *tree, int size);

int save_code_to_file(HTnode_t *tree, int size, char *sourcefile, char *dest);

int print_code_to_terminal(HTnode_t *tree, char *sourcefile, int size);

/*对flename文件进行加密，加密后的文件存储为filname.code,
  解密用到的文件存储为filename.key */
void encrypt(char *filename);

/* 对文件进行解密并打印 */
void decipher(char *sourcefile, char *keyfile);

#endif