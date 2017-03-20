#include "HuffmanNode.h"
//Constructor
HuffmanNode::HuffmanNode() {
	character = '\0';
	bits = "";
	frequency = 0;
	left = right = nullptr;

}
//Default Constructor
HuffmanNode::HuffmanNode(const char &data) {
	character = data;
	frequency = 0;
	left = right = nullptr;
}

//Comparision overloading operators
bool HuffmanNode::operator > (const HuffmanNode & sourceTree) const 
{
	return frequency > sourceTree.getFre();
}
bool HuffmanNode::operator >= (const HuffmanNode & sourceTree) const
{
	return frequency >= sourceTree.getFre();
}

bool HuffmanNode::operator == (const HuffmanNode & sourceTree) const
{
	return character == sourceTree.getChar();
}
bool HuffmanNode::operator < (const HuffmanNode & sourceTree) const
{
	return frequency < sourceTree.getFre();
}
bool HuffmanNode::operator <= (const HuffmanNode & sourceTree) const
{
	return frequency <= sourceTree.getFre();
}
HuffmanNode & HuffmanNode::operator = (const HuffmanNode & source) 
{
	if (this != &source) {
		character = source.getChar();
		frequency = source.getFre();
		bits = source.getBits();
		left = source.getLeft();
		right = source.getRight();
	}
	return *this;
}

HuffmanNode::~HuffmanNode()
{
}
