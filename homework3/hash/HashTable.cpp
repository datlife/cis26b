//Specification file for HashTable

#include "HashTable.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <cctype>
#include <algorithm>
#include <bitset> //to print binary bits of a char
//Main Constructor
HashTable::HashTable() {
	table = nullptr;
}
HashTable::HashTable(int size) {
	//Assume that total items of a store at any given time are not greater than 10,000 items
	table_size_ = size;
	occupied_node = 0;
	//Dynamically allocate a new hash_table double pointer poniting to hash entries		
	table = new HuffmanNode*[table_size_];
	for (int i = 0; i < size; i++){
		table[i] = nullptr;
	}
}

/****************************************************
Create table with specified size
****************************************************/
void HashTable::createTable(int size) {
	//Assume that total items of a store at any given time are not greater than 10,000 items
	table_size_ = size;
	//Dynamically allocate a new hash_table double pointer poniting to hash entries		
	table = new HuffmanNode*[table_size_];
	for (int i = 0; i < table_size_; i++) table[i] = nullptr;
}


/****************************************************
Insert a HashNode into HashTable
****************************************************/
void HashTable::insert(HuffmanNode* newNode) {
	//Compute the barbcde into hash's code
	int bucket = newNode->getChar();
	//Insert 
	if (table[bucket] == nullptr) {
		HuffmanNode* node = new	HuffmanNode(newNode->getChar());
		table[bucket] = node;
		table[bucket]->setChar(node->getChar());
		table[bucket]->setBits(node->getBits());
		table[bucket]->updateFrequency();
		occupied_node++;
	}
	else{
		table[bucket]->updateFrequency();
	}

}
void			 HashTable::insertbyBit(HuffmanNode* c) {
	//Compute the key into hash's code
	int bucket = c->getChar();
	//Insert 
	if (table[bucket] != nullptr) {
		table[bucket]->setBits(c->getBits());
	}
	else {
		std::cout << "New char detected. Please check your code!" << std::endl;
	} 
}

/****************************************************
Remove a HashNode into HashTable
****************************************************/
void HashTable::remove(std::string key) {


}

/****************************************************
Search a HashNode in HashTable
****************************************************/
std::string HashTable::searchBits(char key) {
	//Compute the hash's code

	int bucket = key;
	//Check if current bucket is occupied.
	if (table[bucket])
	{
		return table[bucket]->getBits();	
	}
	return "";
}
char HashTable::searchChar(char c) {
	//Compute the hash's code
	if (c != '\0') {
		int bucket = c;
		//Check if current bucket is occupied.
		if (!table[bucket])
		{
			return table[bucket]->getChar();
		}
	}

	return '\0';
}

void		HashTable::initialize(std::vector<HuffmanNode*>& v){
	for (int i = 0; i < table_size_; i++){
		if (table[i]){
			v.push_back(table[i]);
		}
	}
}

/****************************************************
MAIN HASH FUNCTION
****************************************************/
std::string HashTable::hashFunc(std::string key) {
	return key;

	//Universal hashing method
}

bool	HashTable::isEmpty() { return  table_size_ == 0; }

void	 HashTable::displayTable() {
	int  original = 0;
	int  compressed = 0;
	for (int i = 0; i < 44; i++) { std::cout << '-'; }
	std::cout << "\nChar";
	std::cout << std::setw(10) << "|Frequency";
	std::cout << std::setw(15) << "| Orginal Bits";
	std::cout << std::setw(15) << "| Huffman Bits|\n";
	for (int i = 0; i < 44; i++) { std::cout<< '-'; }
	std::cout << std::endl;
	for (int i = 0; i < table_size_; i++) {
		if (table[i] != nullptr) {
			size_t size = sizeof(table[i]->getChar());
			
			std::cout << std::left	  << " ";
			std::cout << std::setw(3) << table[i]->getChar() << "|    "
					  << std::setw(5) << table[i]->getFre() << " | "
					  << std::setw(11) << std::bitset<8>(table[i]->getChar()) << " | "
					  << std::setw(12)<< table[i]->getBits()<< "|" <<std::endl;

			original += table[i]->getFre()*8;
			compressed += table[i]->getBits().size()*table[i]->getFre();
		}
	}
	double percent = (1 - (compressed / static_cast<double>(original)))* 100;
	for (int i = 0; i < 44; i++) { std::cout << '-'; }
	std::cout << std::left;
	std::cout << "\n"	
		<< std::setw(15) << "Total size:" << "|"
		<< std::setw(8) << original<<" Bits" << "|"
		<< std::setw(8) << compressed<<" Bits" << "|"
		<< std::endl;
	std::cout << " Saved " << percent << "% Memory!\n";
	for (int i = 0; i < 44; i++) { std::cout << '-'; }
	std::cout << std::endl;
}
	
/****************************************************
Destructor for HashTable
****************************************************/
HashTable::~HashTable() {

	delete[] table;
}


/*SuperHash: Word Cited
http://www.azillionmonkeys.com/qed/hash.html
*/