### CIS 26B - String
January 17, 2017

[MD Cheatsheet](https://github.com/adam-p/markdown-here/wiki/Markdown-Cheatsheet)

#### String IO
```
scanf(), fscanf(), gets() fgets(),
printf(), fprintf(), puts(), fputs()
```
#### String
```
// C-string declaration
char s[] = "I can change this";  <--- modifiable
char p*  = "This is read-only"

*s = 'm'; <-- is okay
*p = 'a'; <-- not okay
p++;      <-- okay
s++;      <-- not okay. this is pointer constant


// DYNAMIC ALLOCATION A STRING

char *allocateString(char *tempString){
    // Find len of string
    // add +1 for '\0'
    // dynamic allocation
    char *string;
    int size;
    size = strlen(tempString) + 1;
    string = (char*)calloc();;
    //  Check if memory is still available
    
}

```

#### String functions
```
// READ FROM STRING
char s[] = "Lee, Mary; 1234 98 A";
char name[50];
char id[5];
int score;
char grade;

sscanf(s, "49[^;]%*c %4s %d %c", name, id, &score, grade); 
// name = "Lee, Mary"
// id = 1234
// score = 98
// grade = A


char name[20];
scanf("%19s", name);
FLUSH;              <---- remove the unwanted/extra characters
printf("%s", name);


// regular expression

char str[6] = "";
scanf("%5[0-7]", str);  <--- only allow from 0-7, else will be flush
FLUSH;
printf("%s", str);

// Input: 31580
// Output: 3150
```

#### Display String
```
fputs(message, stdout);
puts(message);   <---- include '\n'

```

#### String manipulation
```
gets(s1): get string, cannot find length
fgets(s, sizeof(s), stdin): get string length


// STRING COPY
char s[10] = "Victor";
char t[10] = "Alex";

strcpy(dest, source);
strncpy(dest, source, num); <--- copy by size

// STRING COMPARE
strcmp(s1, s2); <--- by character , stop at first different char
// == 0 : equal strings
// < 0  : s1 less than s2

strncmp(s1,s2, num);

// STRING CONCATENATION

strcat()

// STRING SEARCH
char s[10] = "Wiki";
char *ptr;

ptr = strrsearch
```

