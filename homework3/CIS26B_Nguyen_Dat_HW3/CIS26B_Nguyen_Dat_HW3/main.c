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
#define MAX_BUCKETS	   3
#define INPUT_BUFFER   100
#define ID_LEN		   5
#define NAME_LEN       20
#define INPUT_PROMPT   "Enter your input file (or press Enter for default choice):"
#define DEFAULT_FILE   "input.txt"
#define FLUSH          while(getchar() != '\n')
#define CHECK_ID	   "0123456789"
#define CHECK_NAME	   "abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTYUVWXYZ ()"

typedef struct {
	char		  id[ID_LEN];		// 4-digit only
	char		  name[NAME_LEN];	// letters, spaces, '(', ')' ONLY
	unsigned int  qty;				//  0-2000
}Record;

typedef struct {
	Record buckets[MAX_BUCKETS];
	int    num_collisions;
}HashNode;

typedef enum { INSERT, SEARCH, DELETE }Menu;

int main(int argc, char *argv[]) {
	// ================== Hash Operations =======================
	unsigned long hashFunc(char *id);
	int   insert(Record r, FILE *);		
	int   search(Record r, FILE *);		
	int   delete(Record r, FILE *);		
	FILE *init_table(char *output_file); // should be an argument

	// ================ Function Prototypes =====================
	void   menu_driver(FILE *fp);
	void   demo(FILE *fp, Menu option);
	int    read_text(char *filename, FILE *);
	int    error_check(const Record *input);	
	void   record_tokenizer(Record *record, char *input);
	void   find_bucket(FILE*, Record, int *, int *, HashNode *);
	char  *get_input(char *message);

	// ==================== Main Program ========================
	// Initialize empty table
	FILE *fp = init_table("hash_table.dat");

	// Insert records into binary file using argument
 	read_text(argv[1], fp);

	// Display menu
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
FILE *init_table(char *output_file) {

	HashNode table[INIT_HASH_SIZE] = { "" };
	//Write empty hash to bin file.
	printf("Saving empty hash table....");
	FILE *fp;
	fp = fopen(output_file, "r");
	if (!fp) {					 // File is not created yet
		fp = fopen(output_file, "w+b");
		fwrite(&table[0], sizeof(HashNode), INIT_HASH_SIZE, fp);
		printf("....Saved\n\n");
	}
	else {						// File is existed
		char choice[INPUT_BUFFER];
		while (1) {
			printf("\n\nError: %s is existed. Would you like to overwrite? (y/n)", output_file);
			fgets(choice, INPUT_BUFFER, stdin);
			if (toupper(choice[0]) == 'Y') {
				fp = fopen(output_file, "w+b");
				fwrite(&table[0], sizeof(HashNode), INIT_HASH_SIZE, fp);
				printf("\nFile %s is overwritten.\n\n", output_file); 
				break;
			}
			else if (toupper(choice[0]) == 'N') {
				printf("\nFile %s is not overwritten.\n", output_file); 
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
	char *id_buffer[ID_LEN], *product_buffer[NAME_LEN];
	int  tmp_qty;
	while (fscanf(fp, " %4s ,  %[a-zA-Z0-9() ] : %d", id_buffer, product_buffer, &tmp_qty) != EOF) {
		Record tmp = { "" };
		strcpy(tmp.id, id_buffer); 
		strcpy(tmp.name, product_buffer);
		tmp.qty = tmp_qty;
		int success = insert(tmp, table);
	}
	return 0;
}
void   menu_driver(FILE *fp) {
	char buffer[INPUT_BUFFER];
	char QUIT_SIGNAL = 0;
	do {
		printf("\n ============== MAIN MENU ======================");
		printf("\n 1. Insert a single product.");
		printf("\n 2. Batch insertion.");
		printf("\n 3. Look up a product.");
		printf("\n 4. Delete a product.");
		printf("\n 5. Quit");
		printf("\n ===============================================");
		printf("\n Select an option: ");
		fgets(buffer, INPUT_BUFFER, stdin);
		if (isdigit(buffer[0]) || strlen(buffer) == 1) {
			int num = buffer[0] - 48;  // Convert ANSCII to number
			printf("");
			switch (num) {
			case 1:
				printf("\n====== INSERT ========\n");
				demo(fp, INSERT);
				break;
			case 2:
				printf("\n===== BATCH INSERT ======\n");
				char *input = get_input("Enter a text file(or 'q' to exit): ");
				read_text(input, fp);
				free(input);
				break;
			case 3:
				printf("\n===== SEARCH ==========\n");
				demo(fp, SEARCH);
				break;
			case 4:
				printf("\n===== DELETE =========\n");
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

	fclose(fp);

}

void   demo(FILE *fp, Menu option) {
	char input[INPUT_BUFFER];
	while (1) {
		printf("\nPlease enter a record('q' to quit): ");
		//Get user input
		fgets(input, INPUT_BUFFER, stdin);
		input[strcspn(input, "\n")] = 0;	// remove new line
		if (strcmp(input, "q") == 0) break;
		else {
			Record r = { "" };
			switch (option) {
			case INSERT: 
				if ((strpbrk(input, ",")) == NULL ||						//Format check if user enters correct format for a record
					strpbrk(input, ":") == NULL ||
					strcspn(input, ",") > strcspn(input, ":")){
					printf("\n\n**Format error** Enter as following format: ID, Name: Quanity\n");
				}
				else {	
					record_tokenizer(&r, input);	//String tokenize
					insert(r, fp);
				}
				break;
			case SEARCH:
				record_tokenizer(&r, input);		// search only need ID
				search(r, fp);
				break;
			case DELETE:
				record_tokenizer(&r, input);
				delete(r, fp);
				break;
			}
		}
	}
}
void   record_tokenizer(Record *record, char *input) {
	char *id	  = strtok(input, ",");
	char *product = strtok(NULL, ":");
	char *qty	  = strtok(NULL, "\t\n ");		 

	if (id != NULL)
		id[strspn(id, CHECK_ID)] = 0; //search for first characters that IS NOT digits
		strcpy(record->id,  id);	
	if (product != NULL) {
		//Remove leading/trailing spaces
		int leading_spaces = 0;
		int trailing_spaces = strlen(product);

		for (int i = 0; i < strlen(product); i++){
			if (isspace(product[i]) != 0)
				leading_spaces++;
			else break;
		}
		for (int i = (strlen(product) -1 ) ; i > 0; i--){
			if (isspace(product[i]) != 0) 
				trailing_spaces--;
			else break;				
	    }
		product[trailing_spaces] = 0;
		strcpy(product, product + leading_spaces);
		if (product!= NULL)
			strcpy(record->name, product);
	}
	if (qty != NULL)
		record->qty = strtol(qty, NULL, 10);
}
int error_check(const Record *f) {
	if (strspn(f->id, CHECK_ID) != ID_LEN - 1) {
		printf("**Invalid ID**");
		return -1;
	}
	int b = strspn(f->name, CHECK_NAME) == 0;
	int c = strspn(f->name, CHECK_NAME) > NAME_LEN;
	int d = strspn(f->name, CHECK_NAME);
	int e = strlen(f->name);
	if (strspn(f->name, CHECK_NAME) == 0|| 
		strspn(f->name, CHECK_NAME) > NAME_LEN || 
		strspn(f->name, CHECK_NAME) != strlen(f->name)) {
		printf("**Invalid Product Name**");
		return -2;
	}
	if (f->qty > 2000 || f->qty < 0) {
		printf("**Invalid Quanity**");
		return -3;
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

void find_bucket(FILE* fp, Record r, int *i, int *matched, HashNode *curr_node) {
	unsigned long key = hashFunc(r.id);
	fseek(fp, sizeof(HashNode)*key, SEEK_SET);	//Seek to current correct hash node
	fread(curr_node, sizeof(HashNode), 1, fp);		   //Copy hashnode into memory

	// Move to available bucket while comparing ID
	while (*i < curr_node->num_collisions) {
		if (strcmp(r.id, curr_node->buckets[*i].id) == 0) {
			*matched = *i;
			break;
		}
		(*i)++;
	}
}
int insert(Record r, FILE *fp) {
	int i = 0, matched = -1;
	HashNode curr_node = { "" };
	find_bucket(fp, r, &i, &matched, &curr_node);
	//Complete error check
	if (error_check(&r) != 0) {
		printf("**Failed to insert %s, %-14s :%-4d\n", r.id, r.name, r.qty);
		return -1;
	}
	if (matched == i) {
		printf("Duplicated ID %s is not allowed. \n", r.id);
		return -1;
	}
	if (i == MAX_BUCKETS) {
		printf("**Failed to add  %s, %-14s :%-3d...Node %d is full\n", r.id, r.name, r.qty, hashFunc(r.id));
		return -2;
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
	printf("Added %s,%-14s:%-4d into HashTable at Node %d, bucket %d\n", curr_node.buckets[i].id, curr_node.buckets[i].name,  curr_node.buckets[i].qty, hashFunc(r.id),  i+1);
	return 0;
}

int   search(Record r, FILE *fp) {
	int i = 0, matched = -1;
	HashNode curr_node;
	find_bucket(fp, r, &i, &matched, &curr_node);
	while (i < curr_node.num_collisions) {
		if (strcmp(r.id, curr_node.buckets[i].id) == 0) {
			printf("\nRecord is found at Node %d, bucket %d.\n", hashFunc(r.id), i+1);
			printf("\nProduct info: %s, %-14s :%-3d\n\n", curr_node.buckets[i].id, curr_node.buckets[i].name, curr_node.buckets[i].qty);
			return i;
		}
		i++;
	}
	printf("\nRecord is not found in database.\n");
	return -1;
}
int    delete(Record r, FILE *fp) {
	int i = 0, pos = -1;
	HashNode curr_node;
	find_bucket(fp, r, &i, &pos, &curr_node);
	if (pos != -1) {
		Record empty = { "" };
		printf("\Deleted %s, %-14s :%-3d\n\n", curr_node.buckets[i].id, curr_node.buckets[i].name, curr_node.buckets[i].qty);
		curr_node.buckets[i] = empty;
		int move = -1;
		fseek(fp, sizeof(HashNode)*move, SEEK_CUR);		
		fwrite(&curr_node, sizeof(HashNode), 1, fp);

	}
	else {
		printf("\nRecord is not in database, so nothing is deleted.\n");
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


/*
===================== SAMPLE OUTPUT 1 =================================

Saving empty hash table....

Error: hash_table.dat is existed. Would you like to overwrite? (y/n)y

File hash_table.dat is overwritten.

Added 6745,MOLLY BOLT    :57   into HashTable at Node 4, bucket 1
Added 5675,SCREW DRIVER  :199  into HashTable at Node 33, bucket 1
Added 1235,WIDGET        :28   into HashTable at Node 17, bucket 1
Added 2341,WING NUT      :89   into HashTable at Node 28, bucket 1
Added 8624,SLEDGE HAMMER :27   into HashTable at Node 8, bucket 1
Added 9162,FLASH LIGHT   :25   into HashTable at Node 26, bucket 1
Added 7146,CEMENT BAGS   :113  into HashTable at Node 16, bucket 1
Added 2358,VISE          :44   into HashTable at Node 24, bucket 1
Added 1622,HAMMER        :15   into HashTable at Node 33, bucket 2
Added 1832,THERMOSTAT    :78   into HashTable at Node 36, bucket 1
**Invalid Quanity****Failed to insert 3271, NAIL           :2345
Added 4717,BRACE         :234  into HashTable at Node 7, bucket 1
Added 9524,CLAMP         :523  into HashTable at Node 38, bucket 1
Added 1524,SANDER        :99   into HashTable at Node 14, bucket 1
Added 5219,SAW           :211  into HashTable at Node 39, bucket 1
Added 6275,SAW BLADE     :675  into HashTable at Node 36, bucket 2
Added 5392,BOLT (REGULAR):1311 into HashTable at Node 1, bucket 1
Added 5192,SCREW DRIVER  :789  into HashTable at Node 39, bucket 2

============== MAIN MENU ======================
1. Insert a single product.
2. Batch insertion.
3. Look up a product.
4. Delete a product.
5. Quit
===============================================
Select an option: 2

===== BATCH INSERT ======
Enter a text file(or 'q' to exit): test_batch.txt
Added 1238,WELDING TORCH :18   into HashTable at Node 36, bucket 3
Added 1327,WALL MOUNT    :90   into HashTable at Node 35, bucket 1
**Failed to add  8123, PLANE          :67 ...Node 36 is full
Added 5934,SOCKET SET    :147  into HashTable at Node 9, bucket 1
Duplicated ID 9524 is not allowed.
Added 5349,LEVEL         :122  into HashTable at Node 9, bucket 2
**Failed to add  2756, RIVET          :89 ...Node 36 is full
Added 3495,BOLT (HEX)    :987  into HashTable at Node 9, bucket 3

============== MAIN MENU ======================
1. Insert a single product.
2. Batch insertion.
3. Look up a product.
4. Delete a product.
5. Quit
===============================================
Select an option: 3

===== SEARCH ==========

Please enter a record('q' to quit): 5349

Record is found at Node 9, bucket 2.

Product info: 5349, LEVEL          :122

Please enter a record('q' to quit): q

============== MAIN MENU ======================
1. Insert a single product.
2. Batch insertion.
3. Look up a product.
4. Delete a product.
5. Quit
===============================================
Select an option: 4

===== DELETE =========
Please enter a record('q' to quit): 5349
Deleted 5349, LEVEL          :122

Please enter a record('q' to quit): q

============== MAIN MENU ======================
1. Insert a single product.
2. Batch insertion.
3. Look up a product.
4. Delete a product.
5. Quit
===============================================
Select an option: 5

No Memory Leak
Press any key to continue . . .
*/


/*
======================== SAMPLE OUTPUT 2===============================
Saving empty hash table....

Error: hash_table.dat is existed. Would you like to overwrite? (y/n)acdasd%$%

Invalid choice. Please type again

Error: hash_table.dat is existed. Would you like to overwrite? (y/n)y

File hash_table.dat is overwritten.

Added 6745,MOLLY BOLT    :57   into HashTable at Node 4, bucket 1
Added 5675,SCREW DRIVER  :199  into HashTable at Node 33, bucket 1
Added 1235,WIDGET        :28   into HashTable at Node 17, bucket 1
Added 2341,WING NUT      :89   into HashTable at Node 28, bucket 1
Added 8624,SLEDGE HAMMER :27   into HashTable at Node 8, bucket 1
Added 9162,FLASH LIGHT   :25   into HashTable at Node 26, bucket 1
Added 7146,CEMENT BAGS   :113  into HashTable at Node 16, bucket 1
Added 2358,VISE          :44   into HashTable at Node 24, bucket 1
Added 1622,HAMMER        :15   into HashTable at Node 33, bucket 2
Added 1832,THERMOSTAT    :78   into HashTable at Node 36, bucket 1
**Invalid Quanity****Failed to insert 3271, NAIL           :2345
Added 4717,BRACE         :234  into HashTable at Node 7, bucket 1
Added 9524,CLAMP         :523  into HashTable at Node 38, bucket 1
Added 1524,SANDER        :99   into HashTable at Node 14, bucket 1
Added 5219,SAW           :211  into HashTable at Node 39, bucket 1
Added 6275,SAW BLADE     :675  into HashTable at Node 36, bucket 2
Added 5392,BOLT (REGULAR):1311 into HashTable at Node 1, bucket 1
Added 5192,SCREW DRIVER  :789  into HashTable at Node 39, bucket 2

============== MAIN MENU ======================
1. Insert a single product.
2. Batch insertion.
3. Look up a product.
4. Delete a product.
5. Quit
===============================================
Select an option: 2

===== BATCH INSERT ======
Enter a text file(or 'q' to exit): adasdas

File not found. Using default file input.txt

Duplicated ID 6745 is not allowed.
Duplicated ID 5675 is not allowed.
Duplicated ID 1235 is not allowed.
Duplicated ID 2341 is not allowed.
Duplicated ID 8624 is not allowed.
Duplicated ID 9162 is not allowed.
Duplicated ID 7146 is not allowed.
Duplicated ID 2358 is not allowed.
Duplicated ID 1622 is not allowed.
Duplicated ID 1832 is not allowed.
**Invalid Quanity****Failed to insert 3271, NAIL           :2345
Duplicated ID 4717 is not allowed.
Duplicated ID 9524 is not allowed.
Duplicated ID 1524 is not allowed.
Duplicated ID 5219 is not allowed.
Duplicated ID 6275 is not allowed.
Duplicated ID 5392 is not allowed.
Duplicated ID 5192 is not allowed.

============== MAIN MENU ======================
1. Insert a single product.
2. Batch insertion.
3. Look up a product.
4. Delete a product.
5. Quit
===============================================
Select an option: 1

====== INSERT ========

Please enter a record('q' to quit): srq51 sadasd


**Format error** Enter as following format: ID, Name: Quanity

Please enter a record('q' to quit): 316161, sdasda %@%^ adas: 500
**Invalid ID****Failed to insert 31616sdasda %@%^ adas, sdasda %@%^ adas :500

Please enter a record('q' to quit): 1241, 28375895$$ :60
**Invalid Product Name****Failed to insert 1241, 28375895$$     :60

Please enter a record('q' to quit): 1251, qweqwe qwe   :40
Added 1251,qweqwe qwe    :40   into HashTable at Node 15, bucket 1

Please enter a record('q' to quit): 1251, qweqwe qwe   :5550
**Invalid Quanity****Failed to insert 1251, qweqwe qwe     :5550

Please enter a record('q' to quit): q

============== MAIN MENU ======================
1. Insert a single product.
2. Batch insertion.
3. Look up a product.
4. Delete a product.
5. Quit
===============================================
Select an option: 4

===== DELETE =========

Please enter a record('q' to quit): adasdas

Record is not in database, so nothing is deleted.

Please enter a record('q' to quit): 1451

Record is not in database, so nothing is deleted.

Please enter a record('q' to quit): 1251
Deleted 1251, qweqwe qwe     :40


Please enter a record('q' to quit): q

============== MAIN MENU ======================
1. Insert a single product.
2. Batch insertion.
3. Look up a product.
4. Delete a product.
5. Quit
===============================================
Select an option: 5

No Memory Leak
Press any key to continue . . .
*/
