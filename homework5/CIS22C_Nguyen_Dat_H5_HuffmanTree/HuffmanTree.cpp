//Specification file for HuffmanTree.h

#include "HuffmanTree.h"
HuffmanTree::HuffmanTree() {
	root = nullptr;
}
HuffmanTree::HuffmanTree(MinHeap& heap) {
	root = nullptr;
//Loop to build a Huffman Tree
	while (heap.checkMinHeap()) {
		//Allocate a new parentNode
		HuffmanNode* parent_node = new HuffmanNode;
		HuffmanNode *min, *secmin;
		//Look for min and secon min
		min		= heap.extractMin();
		secmin	= heap.extractMin();
		//Merge into a new node
		merge(parent_node, min, secmin);
		//insert parentnode into heap---it will be automatically sorted
		heap.insert(parent_node);
		root = parent_node;
		/*
		Testing
		for (int i = 0; i < 5; i++) std::cout << "-";
		std::cout << std::endl;
		heap.printList();
		printList();
		for (int i = 0; i < 5; i++) std::cout << "-";
		std::cout << std::endl;*/
	}
	//Testing the building prcess
	
}
void HuffmanTree::merge(HuffmanNode*& newnode, HuffmanNode* min, HuffmanNode * secmin) {
	//Remove two node from vector root
	newnode->setLeft(min);
	newnode->setRight(secmin);
	//Set new frequency of parent node = sum(children nodes)
	newnode->setFre(min->getFre() + secmin->getFre());
	newnode->setChar('*');
}

//Store new code bits into a HashTable
void HuffmanTree::_encode(HuffmanNode* pT, std::string bit)
{
	if (pT->getLeft()) {
			bit += "0";
			_encode(pT->getLeft(),bit);
			bit.pop_back();
		}
	if (pT->getRight()){
			bit += "1";
			_encode(pT->getRight(), bit);
			bit.pop_back();
	}
	if (pT && pT->isLeaf()) {
		pT->setBits(bit);
	}
}

//Decode
void HuffmanTree::_decode(HuffmanNode* pTraverse, std::string code, std::string& result,size_t i) {
	while (i < code.size()) {
		while (!pTraverse->isLeaf()) {
			if (code[i] == 48) {
				pTraverse = pTraverse->getLeft();
				i++;
			}
			else if (code[i] == 49) {
				pTraverse = pTraverse->getRight();
				i++;
			}
		}
			result += pTraverse->getChar();
			pTraverse = root;	
	}
}
bool HuffmanTree::isEmpty() {
	return root == nullptr;
}
bool HuffmanTree::insert(HuffmanNode* & frequency) {
	return true;
}
bool HuffmanTree::remove(HuffmanNode* & frequency) {
	return true;
}
bool HuffmanTree::getEntry(HuffmanNode* &) const {
	return true;
}
void HuffmanTree::_indentedList(HuffmanNode *parentNode, int level)
{

	if (parentNode != 0) {
		//Identation
		for (int i = 0; i < level; i++)cout << "\t";
		//Print the current Node
		cout << level << ". ";;
		HuffmanNode *item = parentNode;
		if (!parentNode->isLeaf()) {
			cout << item->getFre() << endl;
		}
		else
			cout << *item << endl;
		

		//if Node is a leaf. Stop here
		if (!parentNode->isLeaf()) {
			int new_level = level + 1;
			//Recursive Algorithm
			_indentedList(parentNode->getRight(), new_level);
			_indentedList(parentNode->getLeft(), new_level);
		}
	}
}
void HuffmanTree::_destroyTree(HuffmanNode* rootPtr){
	if (rootPtr != nullptr)
	{
		_destroyTree(rootPtr->getRight());
		_destroyTree(rootPtr->getLeft());
		delete rootPtr;
	}
}
HuffmanTree::~HuffmanTree() {
}