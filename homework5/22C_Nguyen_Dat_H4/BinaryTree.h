// Binary tree abstract base class
// Created by Frank M. Carrano and Tim Henry.
// Modified by: Dat Thanh Nguyen
 //Update: 9:53 PM 2/23/2016
// - Added Iterative depth-first traversals ( in-order, pre-order , post-order)
#ifndef _BINARY_TREE
#define _BINARY_TREE

#include "BinaryNode.h"
#include "Stack.h"
#include "Queue.h"
template<class T>
class BinaryTree
{
protected:
	BinaryNode<T>* rootPtr;		// ptr to root node
	int count;					// number of nodes in tree

public:
	// "admin" functions
 	BinaryTree() {rootPtr = 0; count = 0;}
	BinaryTree(const BinaryTree<T> & tree){ }
	virtual ~BinaryTree() { }
	BinaryTree & operator = (const BinaryTree & sourceTree);
   
	// common functions for all binary trees
 	bool isEmpty() const	{return count == 0;}
	int size() const	    {return count;}
	void clear()			{destroyTree(rootPtr); rootPtr = 0; count = 0;}
	void preOrder(void visit(T &)) const {_preorder(visit, rootPtr);}
	void inOrder(void visit(T &)) const  {_inorder(visit, rootPtr);}
	void postOrder(void visit(T &)) const{_postorder(visit, rootPtr);}
	void removeTree(BinaryNode<T>* root) { destroyTree(root); }
	//Breadth-First Traverse
	void BFT(BinaryNode<T>* root, Queue<T>& result);
	BinaryNode<T>* getroot() { return rootPtr; }
	//Extra credit

	void IpreOrder(void visit(T &)) const { _Ipreorder(visit, rootPtr); }
	void IinOrder(void visit(T &)) const { _Iinorder(visit, rootPtr); }
	void IpostOrder(void visit(T &)) const { _Ipostorder(visit, rootPtr); }
	// abstract functions to be implemented by derived class
	virtual bool insert(const T & newData) = 0; 
	virtual bool remove(const T & data) = 0; 
	virtual bool getEntry(T & returnedItem) const = 0;

private:   
	// delete all nodes from the tree
	void destroyTree(BinaryNode<T>* nodePtr);
	// copy from the tree rooted at nodePtr and returns a pointer to the copy
	BinaryNode<T>* copyTree(const BinaryNode<T>* nodePtr);


	// internal traverse
	void _preorder(void visit(T &), BinaryNode<T>* nodePtr) const;
	void _inorder(void visit(T &), BinaryNode<T>* nodePtr) const;
	void _postorder(void visit(T &), BinaryNode<T>* nodePtr) const;
	// Extra credit
	void _Ipreorder(void visit(T &), BinaryNode<T>* nodePtr) const;
	void _Iinorder(void visit(T &), BinaryNode<T>* nodePtr) const;
	void _Ipostorder(void visit(T &), BinaryNode<T>* nodePtr) const;
}; 

//////////////////////////////////////////////////////////////////////////


//********EXTRA CREDIT**************
/*I used stack to store data*/
template<class T>
void BinaryTree<T>::_Ipreorder(void visit(T &), BinaryNode<T>* nodePtr) const
{
	//PRE-ORDER : ROOT - LEFT - RIGHT
	Stack<BinaryNode<T>*> temp; //Stack to store result for display later
	temp.push(rootPtr);			//push ROOT in first
	
		while (!temp.isEmpty()){
			BinaryNode<T>* pNode;
			temp.pop(pNode);
			visit(pNode->getItem());
			if (pNode->getRightPtr() != nullptr) {
				temp.push(pNode->getRightPtr());
			}
			if (pNode->getLeftPtr() != nullptr) {
				temp.push(pNode->getLeftPtr());
		}
	}
}

template<class T>
void BinaryTree<T>::_Iinorder(void visit(T &), BinaryNode<T>* rootPtr) const
{
	//IN-ORDER: LEFT - ROOT - RIGHT
	bool finished = false;
	BinaryNode<T>* pNode = rootPtr;
	Stack<BinaryNode<T>*> temp;
	while (!finished) {

		if (pNode != nullptr) {
			temp.push(pNode);
			pNode = pNode->getLeftPtr();
		}
		else
		{
			if (!temp.isEmpty())	{
				temp.pop(pNode);
				visit(pNode->getItem());
				pNode = pNode->getRightPtr();
			}
			else
				finished = 1;
		}
	}

}

template<class T>
void BinaryTree<T>::_Ipostorder(void visit(T &), BinaryNode<T>* nodePtr) const
{
	//POST ORDER: : LEFT- RIGHT - ROOT
	if (!rootPtr) return;
	Stack<BinaryNode<T>*> temp;
	BinaryNode<T>* pNode = rootPtr;
	temp.push(rootPtr);

	BinaryNode<T> *parent = nullptr;
	while(!temp.isEmpty())
	{
		BinaryNode<T>* curr;
		temp.getTop(curr);
		if (!parent
			|| parent->getLeftPtr() == curr
			|| parent->getRightPtr() == curr) {
			if (curr->getLeftPtr()) 
				temp.push(curr->getLeftPtr());			
			else if (curr->getRightPtr()) 
				temp.push(curr->getRightPtr());	
		}
		else if (curr->getLeftPtr() == parent) {
			if (curr->getRightPtr())
				temp.push(curr->getRightPtr());	
		}
		else {
			visit(curr->getItem());
			BinaryNode<T>* trash;
			temp.pop(trash);
		}
		parent = curr;
	} 
	
}

template<class T>
BinaryNode<T>* BinaryTree<T>::copyTree(const BinaryNode<T>* nodePtr) 
{

    return newNodePtr;
}  

template<class T>
void BinaryTree<T>::destroyTree(BinaryNode<T>* rootPtr)
{
	if (rootPtr != nullptr)
	{
		destroyTree(rootPtr->getRightPtr());
		destroyTree(rootPtr->getLeftPtr());
		delete rootPtr;
	}
}  


/**********************************************************************
//Breadth-First Traversal:
Store the list of the tree by level (height) and store the result in
a queue, which has been passed by reference
**********************************************************************/
template<class T>
void BinaryTree<T>::BFT(BinaryNode<T>* root, Queue<T>& result)
{
	Queue<BinaryNode<T>*> temp_queue;
	BinaryNode<T>* pTravese;


	temp_queue.enqueue(root);
	while (!temp_queue.isEmpty()) {
		temp_queue.dequeue(pTravese);

		if (pTravese->getLeftPtr() != nullptr) {
			temp_queue.enqueue(pTravese->getLeftPtr());
		}
		if (pTravese->getRightPtr() != nullptr) {
			temp_queue.enqueue(pTravese->getRightPtr());
		}
		result.enqueue(pTravese->getItem());
	}
}


template<class T>
void BinaryTree<T>::_preorder(void visit(T &), BinaryNode<T>* nodePtr) const
{
//PRE-ORDER : ROOT - LEFT - RIGHT
	if (nodePtr != 0)
	{
		T item = nodePtr->getItem();
		visit(item);
		_preorder(visit, nodePtr->getLeftPtr());
		_preorder(visit, nodePtr->getRightPtr());
	} 
}  

template<class T>
void BinaryTree<T>::_inorder(void visit(T &), BinaryNode<T>* nodePtr) const
{
//IN-ORDER: LEFT - ROOT - RIGHT
	if (nodePtr!= 0) {
		T item = nodePtr->getItem();
		_inorder(visit, nodePtr->getLeftPtr());
		visit(item);
		_inorder(visit, nodePtr->getRightPtr());		
	}

}

template<class T>
void BinaryTree<T>::_postorder(void visit(T &), BinaryNode<T>* nodePtr) const
{
//POST ORDER: : LEFT- RIGHT - ROOT
	if (nodePtr != 0) {		
		_postorder(visit, nodePtr->getLeftPtr());
		_postorder(visit, nodePtr->getRightPtr());
		visit(nodePtr->getItem());
	}
}  

template<class T>
BinaryTree<T> & BinaryTree<T>::operator=(const BinaryTree<T> & sourceTree)
{

//RE-CURSIVE
	if (this != &sourceTree) {
		rootPtr = sourceTree.rootPtr;
		count = sourceTree.count;
	}
	else return *this;
}  

#endif _BINARY_TREE

