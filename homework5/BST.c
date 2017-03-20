/****************************************************************************
**
** BUILDING A RANDOM BINARY SEARCH TREE
**
********************************************************

  Buid a random BST - to test the basic BST operations:
  - traverse // recursive
  - insert   // iterative and recursive
  - search   // iterative and recursive
  - delete
****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 50

typedef struct nodeTag{
   int data;
   struct nodeTag *left;
   struct nodeTag *right;
} NODE;

int main( void )
{
   NODE *buildBinaryTree( int n );
   void printTreeInorder( NODE *root );
   int insert( NODE **root, int data );
   NODE *find(NODE *root, int target);

   NODE *root, *ptr;
   int   n = 10, s = 10, r;

   srand(time(NULL));
   root = buildBinaryTree( n );
   printTreeInorder( root );

   while (s--)
   {
       r = rand() % MAX;
       ptr = find(root, r);
       if(ptr)
          printf("%3d found: %3d\n", r, ptr->data);
       else
          printf("%3d NOT found!\n", r);
   }
   printf( "\n\n" );
   return 0;
}

/****************************************************************
   INORDER
   Print a BST in Left-Root-Right sequence.
*/
void printTreeInorder( NODE *root )
{
   if( root ){
      printTreeInorder( root->left);
      printf( "%3d",  root->data );
	  printTreeInorder( root->right);
   }
   return;
}

/****************************************************************
   Build a random BST of integer numbers within the range
   0 to MAX - 1
*/
NODE *buildBinaryTree( int n )
{
   NODE *root = NULL;
   int   data;

   while(n){
        data   = rand( ) % MAX;
        if(insert(&root, data)) // not a duplicate!
            n--;
   }
   return root;
}

/****************************************************************
   ITERATIVE Insert
*/
int insert( NODE **root, int data )
{
   NODE **ptr_root = root;

   while(*ptr_root){
      if (data > (*ptr_root)->data)
         ptr_root = &(*ptr_root)->right;
      else if (data < (*ptr_root)->data)
         ptr_root = &(*ptr_root)->left;
      else
      {
          printf("Node already in the tree!\n");
          return 0; // duplicate
      }
   }
   if(!(*ptr_root = (NODE *) malloc (sizeof(NODE))))
      printf( "Fatal malloc error!\n" ), exit(1);
   (*ptr_root)->data  = data;
   (*ptr_root)->left  = (*ptr_root)->right = NULL;
   return 1; // data inserted
}

/****************************************************************
   RECURSIVE Insert

int insert( NODE **root, int data )
{

   if(!(*root)){ // parent found: insert data
      // allocate the new node
      if(!(*root = (NODE *) malloc (sizeof(NODE))))
         printf( "Fatal malloc error!\n" ), exit(1);
      (*root)->data  = data;
      (*root)->left  = (*root)->right = NULL;
      return 1; // data inserted
   }

   if (data > (*root)->data)
      return insert(&(*root)->right, data);
   else if (data < (*root)->data)
      return insert(&(*root)->left, data);
   else
   {
       printf("Node already in the tree!\n");
       return 0; // duplicate
   }
}
*/
/****************************************************************
   ITERATIVE Search
*/
NODE *find(NODE *root, int target)
{
   NODE *mover = root;

   while (mover)
   {
       if (target < mover->data)
           mover = mover->left;
       else
           if (target > mover->data)
               mover = mover->right;
           else
               return mover;
   }
   return NULL;
}

/****************************************************************
   RECURSIVE Search

NODE *find(NODE *root, int target)
{
   if (root)
   {
       if (target < root->data)
           return find(root->left, target);
       else
           if (target > root->data)
               return find(root->right, target);
           else
               return root;
   }
   return NULL;
}
*/
