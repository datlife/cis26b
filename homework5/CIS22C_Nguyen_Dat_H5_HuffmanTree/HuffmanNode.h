#ifndef HUFFNODE_H_
#define HUFFNODE_H_

#include <string>
#include <iostream>
class HuffmanNode 
{
private:
	int frequency; //key for HuffmanTree & Minheap
	char character;//key for HashTable
	std::string bits;
	HuffmanNode* left;
	HuffmanNode* right;
public:
	HuffmanNode();
	HuffmanNode(const char &data);

	//Setters
	void setLeft(HuffmanNode* l) { left = l; }
	void setRight(HuffmanNode* r) { right = r; }
	void setBits(std::string bitmap) { bits = bitmap; }
	void setChar(char c) { character = c; }
	void setFre(int fr) { frequency = fr; }
	//Getters
	HuffmanNode* getLeft() const { return left; }
	HuffmanNode* getRight() const { return right; }
	int			 getFre() const { return frequency; }
	char		 getChar() const { return character; }
	std::string	 getBits() const { return bits; }


	void updateFrequency() { frequency++; }
	//Overloading operators
	bool operator >		(const HuffmanNode & sourceTree) const;
	bool operator <		(const HuffmanNode & sourceTree) const;
	bool operator >=	(const HuffmanNode & sourceTree) const;
	bool operator <=	(const HuffmanNode & sourceTree) const;
	bool operator ==	(const HuffmanNode & sourceTree) const;
	bool isEmpty() { return frequency == 0; }
	bool isLeaf() { return (right == nullptr) && (left == nullptr); }
	HuffmanNode & operator = (const HuffmanNode & sourceTree);
	friend std::ostream & operator << (std::ostream& os, const HuffmanNode & sourceTree) {
		os << sourceTree.getChar() << " " << sourceTree.getFre() << " " << sourceTree.getBits();
		return os;
	}
	~HuffmanNode();
};

#endif