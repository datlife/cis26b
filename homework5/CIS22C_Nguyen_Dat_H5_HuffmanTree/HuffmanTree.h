#ifndef HUFFMANTREE_H_
#define HUFFMANTREE_H_

#include "BinaryTree.h"
#include "MinHeap.h"
#include "HashTable.h"
#include <vector>
class HuffmanTree : BinaryTree<HuffmanNode*>
{
private:
	HuffmanNode* root;
	void _indentedList(HuffmanNode *nodePtr, int level);
	void _encode(HuffmanNode* pTraverse, std::string bit);
	void _decode(HuffmanNode* pTraverse, std::string code, std::string& result,size_t iterator);
	void _destroyTree(HuffmanNode*);
public:
	HuffmanTree();
	HuffmanTree(MinHeap& array);
	bool isEmpty();
	void merge(HuffmanNode*& newNode, HuffmanNode* min, HuffmanNode * secmin);
	bool insert(HuffmanNode* & frequency);
	bool remove(HuffmanNode* & input);
	bool getEntry(HuffmanNode* & returnedItem) const;
	void encode() {_encode(root, "");}
	void decode(std::string bitcode, std::string& result) {
		_decode(root, bitcode, result, 0);
	}
	void printList() {_indentedList(root, 0);}
	void destroyTree() { _destroyTree(root); }
	~HuffmanTree();
};

#endif  HUFFMANTREE_H_
