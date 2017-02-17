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

#define INIT_HASH_SIZE 10
#define MAX_BUCKETS	   3
#define INPUT_BUFFER   100
#define ID_LEN		   5
#define NAME_LEN       20
#define INPUT_PROMPT   "Enter your input file (or press Enter for default choice):"
#define DEFAULT_FILE   "input.txt"
#define FLUSH          while(getchar() != '\n')
#define CHECK_ID	   "0123456789"
#define CHECK_NAME	   "abcdefghijklmnopqrstuvwyzABCDEFGHIJKLMNOPQRSTYUVWYZ ()"

typedef struct {
	char		  id[ID_LEN];		// 4-digit only
	char		  name[NAME_LEN];	// letters, spaces, '(', ')' ONLY
	unsigned int  qty;				//  0-2000
}Record;

typedef struct{
	Record buckets[MAX_BUCKETS];
	int    num_collisions;
}HashNode;

typedef enum{ INSERT, SEARCH, DELETE }Menu;

int main(int argc, char *argv[]) {
	// ================== Hash Operations =======================
	unsigned long hashFunc(char *id);
	int   insert(Record r, FILE *);		// (c) Report/Reject record additions
	int   search(Record r, FILE *);		// 
	int   delete(Record r, FILE *);		// 

	FILE *init_table(char *output_file); // should be an argument

	// ================ Function Prototypes =====================
	void   menu_driver(FILE *fp);
	int    read_text(char *filename, FILE *);
	int    error_check(const Record *input);	// required to use strtok
	void   demo(FILE *fp, Menu option);
	char  *get_input(char *message);

	// ==================== Main Program ========================
	// Initialize empty hash table into a binary file.
	FILE *fp = init_table("empty_hash.dat");
	// Insert records into binary file using text file input
	read_text(argv[1], fp);
	menu_driver(fp);

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
FILE *init_table(char *output_file){
	HashNode table[INIT_HASH_SIZE] = { "" };
	//Write empty hash to bin file.
	printf("Saving empty hash table....", output_file);
	//Write file to bin
	FILE *fp;
	fp = fopen(output_file, "r");
	if (!fp) { // File is not created yet
		fp = fopen(output_file, "w+b");
		fwrite(&table[0], sizeof(HashNode), INIT_HASH_SIZE, fp);
		printf("....Saved\n\n");
	}
	else {     // File is existed
		char choice;
		while (1) {
			printf("\n\nError: %s is existed. Would you like to overwrite? (y/n)", output_file);
			scanf("%c", &choice);
			if (toupper(choice) == 'Y') {
				fp = fopen(output_file, "w+b");
				fwrite(&table[0], sizeof(HashNode), INIT_HASH_SIZE, fp);
				printf("\nFile %s is overwritten.\n\n", output_file); FLUSH;
				break;
			}
			else if (toupper(choice) == 'N'){
				printf("\nFile %s is not overwritten.\n", output_file); FLUSH;
				break;
			}
			else
				printf("\nInvalid choice. Please type again");
		}
	}
	return fp;
}

int read_text(char *filename, FILE *table) {
	FILE  *fp = NULL;
	//Open a file
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
	char *id_buffer[ID_LEN], *product_buffer[NAME_LEN];
	int  tmp_qty;
	while (fscanf(fp, " %4s ,  %[a-zA-Z0-9() ] : %d", id_buffer, product_buffer, &tmp_qty) != EOF) {
		Record tmp;
		strcpy(tmp.id, id_buffer); strcpy(tmp.name, product_buffer); tmp.qty = tmp_qty;
		int success = insert(tmp, table);
		// No need to check success here - This feature is used during insertion
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
	for (int i = 0; i < 4; i++)
		sum += pow(key[i], 3);
	return sum % INIT_HASH_SIZE;
}

void   menu_driver(FILE *fp) {
	char buffer[INPUT_BUFFER];
	char QUIT_SIGNAL = 0;
	do {
		printf("\n ============== MAIN MENU ======================\n");
		printf("\n 1. Insert a single product.\n");
		printf("\n 2. Batch insertion.\n");
		printf("\n 3. Look up a product.\n");
		printf("\n 4. Delete a product.\n");
		printf("\n 5. Quit\n");
		printf("\n ===============================================\n");
		printf("\n Select an option: ");
		fgets(buffer, INPUT_BUFFER, stdin);
		if (isdigit(buffer[0])) {
			int num = buffer[0] - 48;
			printf("");
			switch (num) {
			case 1:
				printf("\n====== INSERT  ========\n");
				demo(fp, INSERT);
				break;
			case 2:
				printf("\n===== BATCH INSERT ======\n");
				char *input = get_input("Enter a text file: ");
				free(input);
				break;
			case 3:
				printf("\n===== SEARCH  ==========\n");
				demo(fp, SEARCH);
				break;
			case 4:
				printf("\n=====  DELETE  =========\n");
				demo(fp, DELETE);
				break;
			case 5:
				QUIT_SIGNAL = 1;
				break;
			default:
				printf("\nOut of range option\n");
				break;
			}
		}
		else
			printf("\n***Invalid input. Please try again.***\n");
	} while (QUIT_SIGNAL == 0);


}

void   demo(FILE *fp, Menu option) {
	Record temp;
	// Batch Insertion and Line Insertion
	char input[INPUT_BUFFER];
	while (1) {
		printf("\nPlease enter a record('q' to quit): ");
		fgets(input, INPUT_BUFFER, stdin);
		input[strcspn(input, "\n")] = 0;	// remove new line
		if (strcmp(input, "q") == 0) break;
		if ((strpbrk(input, ",")) == NULL || (strpbrk(input, ":") == NULL) || strcspn(input, ",") > strcspn(input, ":")) {
			printf("\n\n**Format error** Enter as following format: ID, Name: Quanity\n"); FLUSH;
			continue;   
		}
		else {
			strcpy(temp.id, strtok(input, " ,"));
			strcpy(temp.name, strtok(NULL, ":"));
			char* id = strtok(NULL, "\t\n ");
			if (id)
				temp.qty = strtol(id, NULL, 10);
			else
				temp.qty = -1;

			switch (option) {
			case INSERT:
				insert(temp, fp);
				break;
			case SEARCH:
				search(temp, fp);
				break;
			case DELETE:
				delete(temp, fp);
				break;
			}
		}
	}
}
int error_check(const Record *f) {
	if (strspn(f->id, CHECK_ID) != ID_LEN - 1) {
		printf("\n**Invalid ID**");
		return -1;
	}
	if (strspn(f->name, CHECK_NAME) > NAME_LEN ||
		strspn(f->name, CHECK_NAME) == 0) {
		printf("\n**Invalid Product Name**");
		return -2;
	}
	if (f->qty > 2000 || f->qty < 0) {
		printf("\n**Invalid Quanity**");
		return -3;
	}
	return 0;
}

int insert(Record r, FILE *fp) {
	//Complete error check before adding new record
	if (error_check(&r) != 0) {
		printf("\n**Failed to add %s, %-14s :%-4d\n", r.id, r.name, r.qty);
		return -1;
	}
	HashNode curr_node;
	unsigned long key = hashFunc(r.id);
	fseek(fp, sizeof(HashNode)*(key - 1), SEEK_SET); 	//Seek to current correct hash node
	fread(&curr_node, sizeof(HashNode), 1, fp);

	int i = 0; // Move to correct bucket while comparing if ID is duplicated
	while (i < curr_node.num_collisions) {
		if (strcmp(r.id, curr_node.buckets[i].id) == 0) {
			printf("\nDuplicated ID. \n");
			return -2;
		}
		i++;
	}
	if (i == MAX_BUCKETS) {
		printf("\n**Failed to add  %s, %-14s :%-3d...Bucket %d is full\n", r.id, r.name, r.qty, key);
		return -3;
	}
	// Start insert
	strcpy(curr_node.buckets[i].id, r.id);
	strcpy(curr_node.buckets[i].name, r.name);
	curr_node.buckets[i].qty = r.qty;
	curr_node.num_collisions += 1;

	//Move to correct HashNode
	int move = -1;
	fseek(fp, sizeof(HashNode)*move, SEEK_CUR);
	fwrite(&curr_node, sizeof(HashNode), 1, fp);
	printf("\nAdded %s, %-14s :%-3d into HashTable at key %d\n", curr_node.buckets[i].id, curr_node.buckets[i].name, curr_node.buckets[i].qty, key);
	return 0;
}

int   search(Record r, FILE *fp) {
	//Complete error check before starting a search
	if (error_check(&r) != 0) return -1;

	//Start search
	unsigned long key = hashFunc(r.id);
	//Copy HashNode 
	HashNode curr_node;
	fseek(fp, sizeof(HashNode)*(key - 1), SEEK_SET); 	//Seek to current correct hash node
	fread(&curr_node, sizeof(HashNode), 1, fp);
	int i = 0; // Move to correct bucket while comparing if ID is duplicated
	while (i < curr_node.num_collisions) {
		if (strcmp(r.id, curr_node.buckets[i].id) == 0) {
			printf("\nRecord is found at bucket %d.\n", key);
			return i;
		}
		i++;
	}
	printf("\nRecord is not found in database.\n");
	return -1;
}
int    delete(Record r, FILE *fp) {
	//Complete error check before starting a search
	if (error_check(&r) != 0) return -1;
	//Start search
	unsigned long key = hashFunc(r.id);
	//Copy HashNode into Memory
	HashNode curr_node;
	fseek(fp, sizeof(HashNode)*(key - 1), SEEK_SET); 	//Seek to current correct hash node
	fread(&curr_node, sizeof(HashNode), 1, fp);
	// Move to correct bucket while comparing if ID is duplicated
	int pos = -1;
	int i = 0;
	while (i < curr_node.num_collisions) {
		if (strcmp(r.id, curr_node.buckets[i].id) == 0) {
			pos = i;
			break;
		}
		i++;
	}
	if (pos != -1) {
		Record empty = { "" };
		fseek(fp, sizeof(HashNode)*(key - 1), SEEK_SET); 	//Seek to current correct hash node
		fwrite(&empty, sizeof(Record)*(pos - 1), 1, fp);
	}
}

/*=========================================================
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
