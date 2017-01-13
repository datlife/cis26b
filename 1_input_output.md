[MD Cheatsheet](https://github.com/adam-p/markdown-here/wiki/Markdown-Cheatsheet)
---
### CIS29 - Intput/Output
January 12, 2017

#### Display Numbers
````
int   score = 10;
int   age   = 25;
// Print integer, second number formatted in signed int
printf("%d %+d\n", age, score)
 
int  num = 10000;
// Save a column space 10, left-indented for an integer
printf("%-10d is an integer number", num);

float  x = 52.26f;         <------------- Note cann't assign double to float
double y = 52.26;
float  z = 25.316;
printf("%f %f\n", x, y);

printf("%.2f $.2f $.2f\n", x, y, z); <--- It might be get rounded accidentially
````

#### Display Characters
```
int  a  =  65;
char b  = 'A';
printf("%d %c", a, b); \\ 65 A
printf("%d %d", a, b); \\ 65 65
printf("%c %c", a, b); \\ A A
```

#### Get an input
````
'scanf' : function skips leading white spaces
'fscanf': get input from a file
'sscanf': read input from a string (useful in parsing)

int  a;
char b;
char c;

scanf("%d %c %c", &a, &b, &c); // <------ Note: always have white space before %c

printf("Enter a number:")
scanf (" %f ", &a);              <------- Grab a number

// Input string 'str' : "10 ABC 2.5"
sscanf(str,"%d %s %lf", &num, &name, &score);
````
#### Point constant
```
int a = 10;
int *p = a;

printf(" %d \n", a); \\ 10
printf(" %p \n", p); \\ &a : address of a
printf(" %p \n", &p);\\ &p : address of p
```

### Pointer Variable
```
int a = 10;
int b;
int *ptr;

ptr = &a;  // ptr ---> a

b = a + 1;
// b = *ptr + 1;

a++;
// (*ptr)++;    <--- has to put parenthesis

```
