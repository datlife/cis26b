
### CIS 26B - malloc()
January 12, 2017

[MD Cheatsheet](https://github.com/adam-p/markdown-here/wiki/Markdown-Cheatsheet)

#### Malloc Allocation
```
# define MEM_ERROR printf("Not enough memory! \n")

...
// Local definitions
 double *ptr;
  
 ptr = (double *) malloc(sizeof(dobule));
 if (ptr == NULL):
 {
    MEM_ERROR;
    exit(100);      <---- try to stay away from this
 }
// if (!ptr) MEM_ERROR, exit(100);

```
#### calloc  - for array
'calloc' clear the memory for us.
```
int *list;
int n = 10;

list = (int *) calloc(n, sizeof(int));

if (!list) MEM_ERROR, exit(100);
```

#### 'ralloc' - dynamically allocated list from existing size.
 How vectors work in C++.

```
int *list;
int *temp;

temp = (int *) re
```
