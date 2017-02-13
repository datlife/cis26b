#define _CRT_SECURE_NO_WARNINGS			// to avoid using fopen_s and strcpy_s on Visual Studio

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <errno.h>

#ifdef _MSC_VER
#include <crtdbg.h>  // needed to check for memory leaks (Windows only!)
#endif

#define INIT_HASH_SIZE 40
#define MAX_BUCKETS	   4
#define INPUT_BUFFER   100
#define ID_LEN		   5
#define PRODUCT_LEN    20
#define INPUT_PROMPT   "Enter your input file (or press Enter for default choice):"
#define DEFAULT_FILE   "input.txt"
#define FLUSH          while(getchar() != '\n')


typedef struct {
	char		  id[ID_LEN];			// 4-digit only
	char		  name[PRODUCT_LEN];	// letters, spaces, '(', ')' ONLY
	unsigned int  qty;					//  0-2000
}Record;

typedef struct {
	unsigned long    key;
	Record			 buckets[MAX_BUCKETS];
	int				 num_collisions;
}HashNode;

int main(void) {
	// ================== Hash Operations =======================
	unsigned long hashFunc(char *key);
	HashNode *init_table(char *output_file);
	int insert(Record r, HashNode *);		// (c) Report/Reject record additions
	int delete(char *id, HashNode *);
	int search(char *id, HashNode *);

	// ================ Function Prototypes =====================
	int read_text(char *filename, HashNode *table);
	int write_bin(char *filename, HashNode *);
	char  *get_input(char *message);
	int error_check(char *input);	// required to use strtok

	// ==================== Main Program ========================
	HashNode *table = init_table("test.dat");
	char *input = get_input(INPUT_PROMPT);
	int test = read_text(input, table);
	//Batch Insertion
	write_bin("data2.bin", table);

	free(table);
	free(input);
#ifdef _MSC_VER
	printf(_CrtDumpMemoryLeaks() ? "\nMemory Leak\n" : "\nNo Memory Leak\n");
#endif
	system("pause");
	return 0;
}

/*
init_table()

- Dynamically Allocate Array of HashNode 
- Initialize initial values.
- write an empty hash file to bin
*/
HashNode *init_table(char *output_file){
	// Dynamically Allocate an empty hash table
	HashNode *table = (HashNode*)malloc(sizeof(HashNode)* INIT_HASH_SIZE);
	if (!table) {
		printf("Error allocating Hash Table.");
		exit(101);
	}
	//Initialize here
	for (int i = 0; i < INIT_HASH_SIZE; i++) {
		table[i].num_collisions = 0;
	}
	//Write empty hash to bin file.
	printf("Saving empty hash table....", output_file); 
	write_bin(output_file, table);
	return table;
}
int read_text(char *filename, HashNode *table) {
	FILE  *fp = NULL;
	//Open a file
	if (strcmp(filename, "") == 0) {
		strcpy(filename, DEFAULT_FILE);
		printf("File not found. Using default file %s\n\n", DEFAULT_FILE);
	}
	fp = fopen(filename, "r");
	if (!fp) {
		strcpy(filename, DEFAULT_FILE);
		printf("\nFile not found. Using default file %s\n\n", DEFAULT_FILE);
		if (!(fp = fopen(filename, "r"))) {
			printf("File %s not found\n", filename);
			exit(101);
		}
	}
	int count = 0;  								// store the loop counts = number of lines in file
	rewind(fp); 									// Make sure we are at first pos
	// TODO: better buffer
	char *id_buffer[ID_LEN];
	char* product_buffer[PRODUCT_LEN];
	int  tmp_qty;
	while (fscanf(fp, " %4s, %[a-zA-Z0-9() ]:%d", id_buffer, product_buffer, &tmp_qty) != EOF) {
		Record tmp;
		strcpy(tmp.id, id_buffer);
		strcpy(tmp.name, product_buffer);
		tmp.qty = tmp_qty;
		int success = insert(tmp, table);
		if (success != 0){
			if (success == -2)
				printf("....ID is invalid.\n");
			if (success == -2)
				printf("....Product name is invalid.\n");
			if (success == -3)
				printf("....Quanity is invalid.\n");

		}
	}
	return 0;
}
int write_bin(char *output_file, HashNode *table) {
	//Write file to bin
	FILE *fp;
	fp = fopen(output_file, "r");
	if (!fp) { // File is not created yet
		fp = fopen(output_file, "wb");
		fwrite(&table[0], sizeof(HashNode)*INIT_HASH_SIZE, 1, fp);
		printf("Saved\n\n");
	}
	else {     // File is existed
		char choice;
		while (1) {
			printf("\n\nError: %s is existed. Would you like to overwrite? (y/n)", output_file);
			scanf("%c", &choice);
			if (toupper(choice) == 'Y') {
				fp = fopen(output_file, "wb");
				fwrite(&table[0], sizeof(HashNode)*INIT_HASH_SIZE, 1, fp);
				printf("\nFile %s is overwritten.\n", output_file); FLUSH;
				break;
			}
			else if (toupper(choice) == 'N'){
				printf("\nFile %s is not overwritten.\n", output_file); FLUSH;
				break;
			} 
			else {
				printf("\nInvalid choice. Please type again");
			}
		}
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
	return sum % INIT_HASH_SIZE;
}
int insert(Record r, HashNode *table) {
	unsigned long key = hashFunc(r.id);
	int i = 0;

	// Move to correct bucket while comparing if ID is duplicated
	while (i < table[key].num_collisions) {
		if (strcmp(r.id, table[key].buckets[i].id) == 0) {
			printf("\nDuplicate ID is not allowed.\n");
			return -1;
		}
		i++;
	}
	if (i > MAX_BUCKETS) {
		printf("\nBucket is full. This Hash Table does not support overflow. \n");
		return -1;
	}
	//Complete error check before adding new record
	int checkpoint = error_check(&r);
	if (checkpoint != 0){
		printf("\nFailed to add     %s, %-14s :%-3d into HashTable **FORMAT ERROR**", r.id, r.name, r.qty);
		return checkpoint;
	}
	// Start insert
	strcpy(table[key].buckets[i].id, r.id);
	strcpy(table[key].buckets[i].name, r.name);
	table[key].buckets[i].qty = r.qty;
	printf("\nSuccesfully Added %s, %-14s :%-3d into HashTable at key %d\n", table[key].buckets[i].id, table[key].buckets[i].name, table[key].buckets[i].qty, key);
	table[key].num_collisions++;
	return 0;

}


int delete(char *id, HashNode *table) {
	return 0;
}
int search(char *id, HashNode *table) {
	return 0;
}

int id_matched(char *id) {
	return 0;

}
int name_matched(char *name) {
	return 0;

}
int qty_matched(int qty) {
	if(qty > 2000 || qty < 0) 
		return -1;
	else
		return 0;
}
int error_check(Record *file) {
	enum {MATCHED}; // MATCHED = 0
	// Assume parse data successfully
	if (id_matched(file->id) != MATCHED)     return -1;
	if (name_matched(file->name) != MATCHED) return -2;
	if (qty_matched(file->qty) != MATCHED)	 return -3;
	return 0;
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
