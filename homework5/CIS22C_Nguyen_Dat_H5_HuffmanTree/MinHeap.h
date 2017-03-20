#ifndef MINHEAP_H_
#define MINHEAP_H_

#include <vector>
#include "BinaryTree.h"
#include "HuffmanNode.h"

class MinHeap : BinaryTree<HuffmanNode*>
{
private:
	vector<HuffmanNode*> root_;
	void reheapDown(size_t parent_index);
	void reheapUp(size_t child_index);
	//void Heapify();
	int size;
public:
	MinHeap();
	MinHeap(vector<HuffmanNode*>&);
	bool insert(HuffmanNode* & frequencyAsKey);
	bool remove(HuffmanNode* & input);
	bool getEntry(HuffmanNode* & returnedItem) const;
	void swap(HuffmanNode*& a, HuffmanNode*& b);
	HuffmanNode* extractMin();
	bool checkMinHeap() { return size >= 1; }
	void printList();
	~MinHeap();
};

#endif MINHEAP_H_
