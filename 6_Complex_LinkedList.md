CIS 26B - Complex Linked List
=============================
January 26, 2017

#### 1. HEADER Structure
* Advantages:
    - No need double pointer



#### 2. Sentinel Node // Dummy Node


#### 3. Sentinel Search
```
int *sentinel_search(int *list, int n, int target){
    int *psent = list + n;
    int *ploc  = list;

    *psent = target;
    while (target != *ploc)
        plocc++;
     return ploc == psent ? NULL : ploc;

}
````

#### 4. Circularly Linked list
```
typedef struct nodeTag{
    struct nodeTag *forw;
    int             data;
    struct nodeTag *back;
}Node;

```
#### 5. Delete a Node  in Circularly Linked list
```
1. Search for current element in list  (*pCurr = list[i])

2. set pPre = pCurr->back, pNext = pCurr->forw

3 Delete the pointer
    pPre->forw = pNext;
    pNext->back = pPre;

```
#### 6. Allocate new node not using
```
NODE *get_node(NODE **stack){
    #define BLOCKSIZE 3

    static NODE *block = NULL, *blockrear;
    if (
}
```