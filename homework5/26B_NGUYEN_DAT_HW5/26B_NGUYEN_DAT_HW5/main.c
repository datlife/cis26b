#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "bst.h"

#ifdef _MSC_VER
#include <crtdbg.h>  // needed to check for memory leaks (Windows only!)
#endif

int main(int argc, char **argv) {
	//========================== Function declaration =============================
	void display(NODE *root, FILE *input);
	void checkArgs(int argc, char *infile, char *outfile, FILE **fin, FILE **fout);
	void printSourceCode(FILE *input);
	void printSourceCodeToFile(FILE *input, FILE *output);

	void saveOutput(char* filename, NODE *tree, FILE *input, FILE *output);
	void close(FILE *input, FILE *output);

	//============================ Main Function ==================================
	FILE *input, *output;
	printf("Input file is :%s\n", argv[1]);
	checkArgs(argc, argv[1], argv[2], &input, &output);
	NODE *tree = buildTree(argv[1], input);
	display(tree, input);
	saveOutput(argv[2], tree, input, output);
	close(input, output);
	destroyTree(tree);

#ifdef _MSC_VER
	printf(_CrtDumpMemoryLeaks() ? "\nMemory Leak\n" : "\nNo Memory Leak\n");
#endif
	return 0;
}

void display(NODE *tree, FILE *input) {
	time_t time_val;
	time(&time_val); // get current time
	printf("/*************************** Cross Reference Listing ***************************\n");
	printf("\nCross reference listing made at: %s \n", asctime(localtime(&time_val)));
	printTreeInorder(tree);
	printSourceCode(input);
}

void printSourceCode(FILE *fp) {
	rewind(fp);
	int	   line_number = 1;
	char   a_line[MAX_LEN];
	char   comment_flag = 0;
	while ((fgets(a_line, MAX_LEN, fp) != NULL)) {						// Stop at the end of file
		printf("%-3d: ", line_number);
		if (comment_flag == 0 && strstr(a_line, "/*") == NULL) { 		// Check if this a start of comment block
			if (strstr(a_line, "//") != NULL) {							// Check if this a comment line.
				printf("\n");
				line_number++;
				continue;
			}
			else {
				printf("%s", a_line);
			}
		}
		else if (strstr(a_line, "*/") != NULL) {							// end of block comment
			comment_flag = 0;
			printf("\n");
		}
		else {
			comment_flag = 1;											// still in comment block
			printf("\n");
			line_number++;
			continue;
		}
		line_number++;
	}
}
void printSourceCodeToFile(FILE *fp, FILE *output) {
	rewind(fp);
	int	   line_number = 1;
	char   a_line[MAX_LEN];
	char   comment_flag = 0;
	while ((fgets(a_line, MAX_LEN, fp) != NULL)) {						// Stop at the end of file
		fprintf(output, "%-3d: ", line_number);
		if (comment_flag == 0 && strstr(a_line, "/*") == NULL) { 		// Check if this a start of comment block
			if (strstr(a_line, "//") != NULL) {					// Check if this a comment line.
				fprintf(output, "\n");
				line_number++;
				continue;
			}
			else {
				fprintf(output, "%s", a_line);
			}
		}
		else if (strstr(a_line, "*/") != NULL) {							// end of block comment
			fprintf(output, "\n");
			comment_flag = 0;
		}
		else {
			comment_flag = 1;											// still in comment block
			fprintf(output, "\n");
			line_number++;
			continue;
		}
		line_number++;
	}
}
void checkArgs(int argc, char *infile, char *outfile, FILE **fin, FILE **fout) {
	if (argc != 3){
		printf("Wrong numer of arguments on command line.\n");
		exit(1);
	}
	if ((*fin = fopen(infile, "r")) == NULL)
	{
		perror("Cannot open input file");
		exit(1);
	}
	*fout = fopen(outfile, "r");
	if (!*fout) { // File is not created yet
		*fout = fopen(outfile, "w");
	}
	else {     // File is existed
		char choice;
		while (1) {
			printf("File %s is existed. Do you want to overwrite? (y/n)", outfile);
			scanf("%c", &choice);
			if (toupper(choice) == 'Y') {
				*fout = fopen(outfile, "w");
				break;
			}
			else if (toupper(choice) == 'N') exit(1);
			else {
				printf("\nInvalid choice. Please type again\n");
				FLUSH;
			}
		}
	}
}
void saveOutput(char* filename, NODE *tree, FILE *input, FILE *output) {
	//ASSUMPTION:
	// file name has been validated if existed in checkArgs()
	time_t time_val;
	time(&time_val); // get current time
	fprintf(output, "/*************************** Cross Reference Listing ***************************\n");
	fprintf(output, "\nCross reference listing made at: %s \n", asctime(localtime(&time_val)));
	printTreeInorderToFile(tree, output);
	printSourceCodeToFile(input, output);
}
void close(FILE *input, FILE *output) {
	// Close the file
	if (fclose(input) == EOF) {
		printf("Error closing input file."); exit(201);
	}
	// Close the file
	if (fclose(output) == EOF) {
		printf("Error closing input file."); exit(201);
	}
}


/* SAMPLE OUPUT
Input file is :./test_case_2.txt
File ./output.txt is existed. Do you want to overwrite? (y/n)y
/*************************** Cross Reference Listing ***************************

Cross reference listing made at: Sun Mar 26 20:21:35 2017

FILE                   :  19   20   21   22   32   55   90
MAXCITIES              :  5    18
MAXLINE                :  6    58   60
NULL                   :  40   46   71
argc                   :  16   20   24   32   34
argv                   :  16   24
char                   :  10   16   20   32   58   71
checkArgs              :  20   24   32
city                   :  58   62   63   71   76
count                  :  12   21   22   25   26   57   63   66   67   68   70   76   80   81   85   90   94   96
define                 :  5    6
else                   :  66   78
exit                   :  37   43   49   74
fgets                  :  60
fin                    :  19   20   21   22   24   25   32   40   55   60
first                  :  57   65
float                  :  96
fopen                  :  40   46
for                    :  94
fout                   :  19   20   24   26   32   46   90   95
fprintf                :  95
highTemp               :  57   62   67   80
highTemps              :  18   21   25   26   55   63   67   68   70   76   80   81   90   95   96
hightemps              :  22
i                      :  92   94   95   96
if                     :  34   40   46   63   65   70
include                :  1    2    3    4
infile                 :  20   32   40
int                    :  11   12   16   20   21   22   32   55   57   90   92
line                   :  58   60   62
main                   :  16
malloc                 :  71
outfile                :  20   32   46
perror                 :  42   48   73
printf                 :  36
readIntoWeatherStructs :  21   25   55
return                 :  85
sscanf                 :  62
statecity              :  10   63   70   76   95
strcmp                 :  63
strcpy                 :  76
strlen                 :  71
struct                 :  8    18   21   22   55   90
tempsum                :  11   67   80   96
void                   :  20   22   32   90
weather                :  8    18   21   22   55   90
while                  :  60
writeAveragesToOutput  :  22   26   90

1  : #include <stdio.h>
2  : #include <stdlib.h>
3  : #include <string.h>
4  : #include <ctype.h>
5  : #define MAXCITIES 100
6  : #define MAXLINE    80
7  :
8  :      struct weather
9  :      {
10 :          char *statecity;
11 :          int   tempsum;
12 :          int   count;
13 :      };
14 :
15 :
16 :      int main(int argc, char **argv)
17 :      {
18 :          struct weather highTemps[MAXCITIES] = { { "", 0, 0 } };
19 :          FILE *fin, *fout;
20 :          void checkArgs(int argc, char *infile, char *outfile, FILE **fin, FILE **fout);
21 :          int readIntoWeatherStructs(struct weather *highTemps, FILE *fin), count;
22 :          void writeAveragesToOutput(struct weather *hightemps, int count, FILE *fin);
23 :
24 :      checkArgs(argc, argv[1], argv[2], &fin, &fout);
25 :          count = readIntoWeatherStructs(highTemps, fin);
26 :          writeAveragesToOutput(highTemps, count, fout);
27 :      }
28 :
29 :
30 :
31 :
32 :      void checkArgs(int argc, char *infile, char *outfile, FILE **fin, FILE **fout)
33 :      {
34 :          if (argc != 3)
35 :              {
36 :                      printf("Wrong number of arguments on command line!\n");
37 :                      exit(1);
38 :                  }
39 :
40 :              if ((*fin = fopen(infile, "r")) == NULL)
41 :              {
42 :                      perror("Cannot open input file");
43 :                      exit(1);
44 :                  }
45 :
46 :              if ((*fout = fopen(outfile, "w")) == NULL)
47 :              {
48 :                      perror("Cannot open output file");
49 :                      exit(1);
50 :                  }
51 :      }
52 :
53 :
54 :
55 :      int readIntoWeatherStructs(struct weather *highTemps, FILE *fin)
56 :      {
57 :          int count = 0, first = 1, highTemp;
58 :          char city[MAXLINE], line[MAXLINE];
59 :
60 :      while (fgets(line, MAXLINE, fin))
61 :              {
62 :                       sscanf(line, "%s %d", city, &highTemp);
63 :                       if (strcmp(city, highTemps[count].statecity) != 0)
64 :                      {
65 :                                    if (first) first = 0;
66 :                                    else count++;
67 :                                    highTemps[count].tempsum = highTemp;
68 :                                    highTemps[count].count = 1;
69 :
70 :                      if ((highTemps[count].statecity =
71 :                                                 (char *)malloc(strlen(city) + 1)) == NULL)
72 :                              {
73 :                                                perror("Malloc error!");
74 :                                                exit(1);
75 :                                            }
76 :                      strcpy(highTemps[count].statecity, city);
77 :                               }
78 :                       else
79 :                               {
80 :                                    highTemps[count].tempsum += highTemp;
81 :                                    highTemps[count].count++;
82 :                               }
83 :              }
84 :
85 :      return count;
86 :      }
87 :
88 :
89 :
90 :      void writeAveragesToOutput(struct weather *highTemps, int count, FILE *fout)
91 :      {
92 :           int i;
93 :
94 :      for (i = 0; i <= count; i++)
95 :              fprintf(fout, "%s %-5.1f\n", highTemps[i].statecity,
96 :                                       (float)highTemps[i].tempsum / highTemps[i].count);
97 :      }

No Memory Leak
Press any key to continue . . .
*/

//