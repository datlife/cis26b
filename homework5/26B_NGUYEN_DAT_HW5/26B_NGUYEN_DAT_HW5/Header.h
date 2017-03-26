////
////  Header.h
////  homework
////
////  Created by Tram Nguyen on 3/21/17.
////
//
//#ifndef Header_h
//#define Header_h
//
//typedef struct linenumber LINENUMBER;
//struct linenumber
//{
//	long number;
//	struct linenumber *next;
//};
//
//typedef struct treenode TREENODE;
//struct treenode
//{
//	char *key;
//	struct treenode *left, *right;
//	struct linenumber *front, *rear;
//	int count;
//};
//
//FILE *openInputFile(char *filename);
//FILE *openOutputFile(char *filename);
//void enqueue(LINENUMBER **queue, LINENUMBER **rear, int data);
//LINENUMBER *dequeue(LINENUMBER **queue, LINENUMBER **rear);
//int insert(TREENODE **root, char* data, int lineNumber);
//int checkIfStartOfCommentBlock(char *str);
//int checkIfEndOfCommentBlock(char *str);
//int checkIfCommentLine(char *str);
//void deleteIrrelavantParts(char *str);
//void printFile(FILE *inputfile, FILE *outputFile);
//TREENODE *buildBinaryTree(FILE *file);
//void printTreeInorder(TREENODE *root, FILE *outputFile);
//void printTime(FILE *outputFile);
//void deleteNode(TREENODE *node);
//void deleteTree(TREENODE *root);
//
//#endif /* Header_h */
