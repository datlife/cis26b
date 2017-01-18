### CIS29 - File IO
January 17, 2017

[MD Cheatsheet](https://github.com/adam-p/markdown-here/wiki/Markdown-Cheatsheet)

#### Open/Close a File
```

// EOF = -1
// w: write mode, a: append mode

FILE *fp = fopen("DATA.TXT", "r");
if (fp == NULL){
    //File Not found
    exit(101);   <----- stdlib.h is required
}


// Close a file
int close_check;
int = fclose(fp);
if (close_check == EOF)
{
    printf("Error closing DATA.txt");
    exit(201);
}
```
### Useful functions
```
rewind(fp)                   : move to the beginning of the file
rename("OLDNAME", "NEWNAME") : rename a file
remove("filename")           : remove a file
```

### Character Input/Output:
```
int c;
c = getchar();   // get one char from keyboard and return it
putchar(c);      // write one char to screen

while( (c = getchar()) != EOF)  //declare 'c' as int to compare to EOF (-1)
{

}

fc = fgetc(fp) // get one char from  file
```

### Save a file
```
// open a file in writting mode
fprintf(fpOut, "%d", a_number)
```
### Read a file
```
//Open in reading mode

num_successful_conversion = fscanf(stdin, "%d %f", & year &price);

fscanf(fpDate, "%d%*c%d%*c%d", &year, &month, &day);

```

### Flush buffer

* Why? 
```
#define FLUSH while(getchar() != '\n')

do
{   
    printf("Enter a number from 1 to 9: ");
    iores = scanf("%d", &num);
    FLUSH;
} while ( (iosre != 1) || (num > 1) || (num < 9));

```

