#include "MinHeap.h"
MinHeap::MinHeap()
{
}

//***************************PUBLIC MEMBER FUNCTIONS************************************
bool MinHeap::insert( HuffmanNode* & newNode) {
	size = root_.size();
	root_.push_back(newNode);
	reheapUp(size);
	return true;
}
bool MinHeap::remove(HuffmanNode* & input) {
	return true;
}
bool MinHeap::getEntry(HuffmanNode* & returnedItem) const {
	return true;
}
void MinHeap::printList() {
	for (int i = 0; i < size; i++) {
		std::cout << *root_[i] << std::endl;
	}
}
//------------------------------------PRIVATE FUNCTIONS-----------------------------
MinHeap::MinHeap(vector<HuffmanNode*>& v) {
	//Copy vector v into root_
	for (vector<HuffmanNode*>::iterator i = v.begin(); i < v.end(); i++){
		insert(*i);
	}
}
void MinHeap::reheapDown(size_t parent_index) {
	size_t length = root_.size();
	size_t iLeftChild = 2 * parent_index + 1;
	size_t iRightChild = 2 * parent_index + 2;
	//parent node is a leaf
	if (iLeftChild >= length) { return; }

	size_t min = parent_index;
	//Case 1:  parentnode > leftchild
	if (*root_[parent_index] > *root_[iLeftChild]) {
		min = iLeftChild;
	}
	if ((iRightChild < length) && *root_[min] > *root_[iRightChild]) {
		min = iRightChild;
	}
	if (min != parent_index) {
		//Swap min_Node vs parent_Node
		swap(root_[parent_index], root_[min]);
		reheapDown(min);
	}
}
void MinHeap::reheapUp(size_t child_index) {
	//if child is Root
	if (child_index == 0) return;
	size_t parent_index = (child_index - 1) / 2;
	//Swap
	if ( *root_[parent_index] > *root_[child_index]) {
		swap(root_[parent_index], root_[child_index]);
		reheapUp(parent_index);
	}

}
void MinHeap::swap(HuffmanNode*& a, HuffmanNode*& b){
	HuffmanNode* temp = a;
	a = b;
	b = temp;
}
HuffmanNode* MinHeap::extractMin(){
	if (size == 0)return nullptr;

	HuffmanNode* holdMin = root_[0];
	//Copy the last item of vector to the Min's pos
	root_[0] = root_[root_.size()-1];
	root_.pop_back(); //delete the last item
	size = root_.size();
	reheapDown(0);

	return holdMin;
}
MinHeap::~MinHeap()
{
}
