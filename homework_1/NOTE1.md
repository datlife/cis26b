[MD Cheatsheet](https://github.com/adam-p/markdown-here/wiki/Markdown-Cheatsheet)
---
### CIS29 - Week1
January 12, 2017


**1. Why use typedef struct?**

To avoid calling "struct student ;"

```
typedef struct
{
    blab bla;
} STUDENT;

STUDENT a;
```

**2. Reference Parameters, malloc, caller ... using array notation for pointer
arrays** 

````
// RULE OF THUMB: Use Index-Notation

int *a = new int[20];
int *b = a;

b = b + 1;  //          <-----> &a[1]

a[2] = 99;  //          <----- index-notation
*(a + 2 ) = 99;         <----- NOT recommended

// Tricky question:
// *(i + a); i[a] <----- this work
````

**3. Detect Memory leak**
```
#ifdef _MSC_VER
#include <crtdbg.h>  // needed to check for memory leaks (Windows only!)
#endif
.....
int main()
{
    ....

    #ifdef _MSC_VER
    printf( _CrtDumpMemoryLeaks() ? "Memory Leak\n" : "No Memory Leak\n");
    #endif
       
    return 0;
}
```