// Node for a binary tree
// Created by Frank M. Carrano and Tim Henry.
// Modified by Dat nguyen 
// Last update :9:53 PM 2/23/2016
// - Added member data "height" - to calculate the longest path easier
// - Added member function updateHeight() - calculate the height of a specfic given node.
 
#ifndef _BINARY_NODE
#define _BINARY_NODE

template<class T>
class BinaryNode
{   
private:
	T              item;         // Data portion
	BinaryNode<T>* leftPtr;		// Pointer to left child
	BinaryNode<T>* rightPtr;	// Pointer to right child
	int height;
public:
	// constructors
	BinaryNode(const T & anItem) { item = anItem; leftPtr = 0; rightPtr = 0; height = -1; }
	BinaryNode(const T & anItem, 
		       BinaryNode<T>* left, 
			   BinaryNode<T>* right) {
		item = anItem; leftPtr = left; rightPtr = right;}
	// accessors
	void setItem(const T & anItem) {item = anItem;}
	void setLeftPtr(BinaryNode<T>* left) {leftPtr = left;}
    void setRightPtr(BinaryNode<T>* right) {rightPtr = right;}
	void setHeight(int new_height) {height = new_height;}
	// mutators
	T getItem() const	 {return item;}
	BinaryNode<T>* getLeftPtr() const  {return leftPtr;}
	BinaryNode<T>* getRightPtr() const {return rightPtr;}
	int getHeight() const { return height; }

	bool isLeaf() const {return (leftPtr == 0 && rightPtr == 0);}
	void updateHeight(){
		//Find the max of left and right node--> plus +1 = height of currentNode
		int left_height, right_height;

		if (this->getLeftPtr() == nullptr)left_height = -1;
		else left_height = this->getLeftPtr()->getHeight();
		
		if (this->getRightPtr() == nullptr) right_height = -1;
		else right_height = this->getRightPtr()->getHeight();

		if ( left_height > right_height){
			this->height = left_height + 1;
		}
		else
			this->height = right_height + 1;
	}
}; 
#endif _BINARY_NODE
