// Binary Search Tree ADT
// Created by Frank M. Carrano and Tim Henry.
// Modified by: Dat Thanh Nguyen
 //New Features : Breadth-first Traversal
#ifndef _BINARY_SEARCH_TREE
#define _BINARY_SEARCH_TREE

#include "BinaryTree.h"

template<class T>
class BinarySearchTree : public BinaryTree<T>
{   
private:
	// internal INSERT node: insert newNode in nodePtr subtree
	BinaryNode<T>* _insert(BinaryNode<T>* nodePtr, BinaryNode<T>* newNode);
	// internal REMOVE node: locate and delete target node under nodePtr subtree
	BinaryNode<T>* _remove(BinaryNode<T>* nodePtr, const T target, bool & success);
	// DELETE TARGET node from tree, called by internal remove node
	BinaryNode<T>* deleteNode(BinaryNode<T>* targetNodePtr);
	// REMOVE LEFTMODE node in the left subtree of nodePtr
	BinaryNode<T>* removeLeftmostNode(BinaryNode<T>* nodePtr, T & successor);
	// search for target node
	BinaryNode<T>* findNode(BinaryNode<T>* treePtr, const T & target) const;
   
public:  

	// insert a node at the correct location
    bool insert(const T & newEntry);
	// remove a node if found
	bool remove(const T & anEntry);
	// find a target node
	bool getEntry(T & returnedItem) const;

};

///////////////////////// public function definitions ///////////////////////////

template<class T>
bool BinarySearchTree<T>::insert(const T & newEntry)
{

	BinaryNode<T>* newNodePtr = new BinaryNode<T>(newEntry);
	rootPtr = _insert(rootPtr, newNodePtr);
	return true;
}  

template<class T>
bool BinarySearchTree<T>::remove(const T & target)
{
	bool isSuccessful = false;
	rootPtr = _remove(rootPtr, target, isSuccessful);
	return isSuccessful; 
}  

template<class T>
bool BinarySearchTree<T>::getEntry(T & returnedItem) const
{

	BinaryNode<T>* result = findNode(rootPtr, returnedItem);
	if (result != nullptr)
	returnedItem = result->getItem();	

	return result != nullptr;
}  


//////////////////////////// private functions ////////////////////////////////////////////

template<class T>
BinaryNode<T>* BinarySearchTree<T>::_insert(BinaryNode<T>* nodePtr,
                                                          BinaryNode<T>* newNodePtr)
{
	//If tree has nothing
	if (nodePtr == nullptr){
		nodePtr = newNodePtr;
	}
	else
	{
		//Move to left
		if (nodePtr->getItem() >= newNodePtr->getItem())
			//Recursive
			nodePtr->setLeftPtr(_insert(nodePtr->getLeftPtr(), newNodePtr));
		//Move to the right
		else 
			//Recursive
			nodePtr->setRightPtr(_insert(nodePtr->getRightPtr(), newNodePtr));		
	}
	//Update new height of current Node
	nodePtr->updateHeight();
	return nodePtr;
}  

template<class T>
BinaryNode<T>* BinarySearchTree<T>::_remove(BinaryNode<T>* nodePtr,
                                                          const T target,
                                                          bool & success)
{
	if (nodePtr == 0)                   {
		success = false;
		return 0;
	}
	if (nodePtr->getItem() > target)		 
		nodePtr->setLeftPtr(_remove(nodePtr->getLeftPtr(), target, success));
	else if (nodePtr->getItem() < target)	 
		nodePtr->setRightPtr(_remove(nodePtr->getRightPtr(), target, success));
	else{ // if node is found
		nodePtr = deleteNode(nodePtr);
		success = true;
	}      
	return nodePtr;   
}  

template<class T>
BinaryNode<T>* BinarySearchTree<T>::deleteNode(BinaryNode<T>* nodePtr)
{
	if (nodePtr->isLeaf())				
	{
		delete nodePtr;
		nodePtr = 0;
		return nodePtr;
	}
	else if (nodePtr->getLeftPtr() == 0)  
	{
		BinaryNode<T>* nodeToConnectPtr = nodePtr->getRightPtr();
		delete nodePtr;
		nodePtr = 0;
		return nodeToConnectPtr;
	}
	else if (nodePtr->getRightPtr() == 0) 
	{
		BinaryNode<T>* nodeToConnectPtr = nodePtr->getLeftPtr();
		delete nodePtr;
		nodePtr = 0;
		return nodeToConnectPtr;      
	}
	else                                  
	{
		T newNodeValue;
		nodePtr->setRightPtr(removeLeftmostNode(nodePtr->getRightPtr(), newNodeValue));
		nodePtr->setItem(newNodeValue);
		return nodePtr;
	}  
}  

template<class T> 
BinaryNode<T>* BinarySearchTree<T>::removeLeftmostNode(BinaryNode<T>* nodePtr,
                                                                     T & successor)
{
	if (nodePtr->getLeftPtr() == 0)
	{
		successor = nodePtr->getItem();
		return deleteNode(nodePtr);
	}
	else 
	{
		nodePtr->setLeftPtr(removeLeftmostNode(nodePtr->getLeftPtr(), successor));
		return nodePtr;
	}       
}


template<class T>
BinaryNode<T>* BinarySearchTree<T>::findNode(BinaryNode<T>* nodePtr,
                                                           const T & target) const 
{
	if (nodePtr != nullptr){
		if (nodePtr->getItem() == target) 	return nodePtr;
		if (nodePtr->getItem() < target){
			nodePtr = findNode(nodePtr->getRightPtr(), target);
		}
		else
			nodePtr = findNode(nodePtr->getLeftPtr(), target);
	}
	return nodePtr;
}  


#endif _BINARY_SEARCH_TREE
