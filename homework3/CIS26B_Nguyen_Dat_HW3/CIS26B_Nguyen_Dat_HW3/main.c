#define _CRT_SECURE_NO_WARNINGS			// to avoid using fopen_s and strcpy_s on Visual Studio

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define INIT_HASH_SIZE 40
#define MAX_BUCKETS	   4
#define INPUT_BUFFER   100
#define INPUT_PROMPT   "Enter your input file (or press Enter for default choice):"
#define DEFAULT_FILE   "input.txt"
#define FLUSH          while(getchar() != '\n')


typedef struct {
	char id[4];			// 4-digit only
	char name[20];		// letters, spaces, '(', ')' ONLY
	unsigned int  qty; //  0-2000
}Record;

typedef struct {
	unsigned long    key;
	Record			 buckets[MAX_BUCKETS];
	int				 num_collisions;
}HashNode;



int main(void) {
	// ================== Hash Operations =====================
	unsigned long hashFunc(char *key);
	int init_table(char *output_file, HashNode **);
	int insert(char *id, HashNode **);		// (c) Report/Reject record additions
	int delete(char *id, HashNode **);
	int search(char *id, HashNode **);
	// ============== Function Prototypes =====================
	int read_text(char *filename, HashNode **);
	int write_bin(char *filename, HashNode **);
	char  *get_input(char *message);
	int error_check(char *input);	// required to use strtok

	// =============== Main Program ==================
	printf("Hello, World! This is a native C program compiled on the command line.\n");
	HashNode *hash_table[40];
	init_table("test.dat", &hash_table);
	read_text("blabla.txt", hash_table);

	return 0;
}

int init_table(char *output_file, HashNode **ht){
FILE *fp;
	fp = fopen(output_file, "r");
	if (!fp) { // File is not created yet
		fp = fopen(output_file, "wb");
		fwrite(&ht, sizeof(HashNode)*INIT_HASH_SIZE, 1, fp);
	}
	else {     // File is existed
		printf("Error: filename is existed. Would you like to overwrite?");
	}
	return 1;
}
int read(char *filename) {
	FILE *fp;

	if (!filename) {
		printf("File not found. using default name");
	}
	return 0;
}
/****** HASH FUNCT *************
The hash key is product id
sum the cube of the ASCII values of the characters 
making up the product id before dividing by 40
*/
unsigned long hashFunc(char *key) {
	unsigned long sum = 0;
	for (int i = 0; i < 4; i++) {
		sum += pow(key[i], 3);
	}
	return sum / INIT_HASH_SIZE;
}
int id_matched(char *id) {
	return 0;

}
int name_matched(char *name) {
	return 0;

}
int qty_matched(int qty) {
	return 0;
}
int error_check(char *input) {
	enum {MATCHED}; // MATCHED = 0
	// Assume parse data successfully

	Record *file = NULL;

	if (id_matched(file->id) != MATCHED)     return -1;
	if (name_matched(file->name) != MATCHED) return -1;
	if (qty_matched(file->qty) != MATCHED)	 return -1;
	return 1;
}
/*===========================================================
* get_input
* =========================================================
* Get user input
* 	Pre:  message: prompt to display to ask user
*	Post: user input
*/
char *get_input(char *message) {
	char *fname = (char*)malloc(INPUT_BUFFER);
	if (fname == NULL) {
		printf("Fatal malloc error in get_node!\n");
		exit(1);
	}
	printf(message);
	fgets(fname, INPUT_BUFFER, stdin);
	fname[strcspn(fname, "\n")] = 0;
	return fname;
}