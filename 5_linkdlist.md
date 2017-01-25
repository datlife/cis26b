CIS 26B - Data Structures
=========================
January 24, 2017

[MD Cheatsheet](https://github.com/adam-p/markdown-here/wiki/Markdown-Cheatsheet)

#### 1.  Compare List array

| Array         |    LinkedList      |
| --------------|--------------------|
|       | asdasdas           |
| dasdasdas     |
#### 2. Declare `struct`
```
# First way
typdef struct node{
    int     data;
    struct node *next;
 }NODE;

 # Second way
 typedef struct node NODE;
 struct node{
    int          data;
    struct node *next;
 };
```

#### 3. LinkedList of Cities
````
# First way - better because we don't have to assign pointer
typedef struct {
    char state[3];
    int  year;
    char *name;
}CITY;

typedef struct nodeTag{
    CITY            city;
    struct nodeTag *next'
}


# Second way
typedef struct nodeTag {
    char state[3];
    int  year;
    char *name;

    struct nodeTag* next;
}CITY;
````

#### 4. STACK
````
# STACK : push(), pop(), peak()
# QUEUE : enque(), dequeue()


NODE *push(NODE *stack, int data){
    NODE *pNew = (NODE*) malloc(sizeof(NODE));
    if (!pNew){
        //Error
        exit(1);
     }
     pNew->data = data;
     return pNew;
}

NODE *pop(NODE **stack){
    NODE *first;
    if (*stack == NULL)
        return NULL;
    first = *stack;
    *stack = (*stack)->next;  // <--- move stack to below
    first->next = NULL;       // <--- disconect next to original stack
    return first;
}

//Calling push
NODE *push(NODE *stack, int data);
NODE *s = NULL;
s = push(s, 8);
s = push(s, 9);
s = push(s, 3);
out = pop(&s);
````

#### 5. QUEUE
```
void enqueue(NODE **queue, NODE **rear, int data){
    NODE *pNEW = (NODE *)malloc(sizeof(NODE));
    if (!pNew){
        // Error
    }
    pNew->data = data;
    pNew-> next = NULL;
    if (*queue == NULL) *queue = pNEw;
    else (*rear)->next = pNew;    <------- becarefull !!!
    *rear = pNew;
    return pNew;
}

NODE *dequeue(NODE **queue, NODE **rear){

    NODE *first;
    if (*queue == NULL) return NULL;
    first = *queue;
    *queue = (*queue)->next;
    if (*queue == NULL) *rear = NULL;
    first->next = NULL;
}

// Calling queue

```