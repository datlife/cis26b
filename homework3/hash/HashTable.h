#ifndef TEAM4_HASHMAP_H_
#define TEAM4_HASHMAP_H_
#include "HuffmanNode.h"
#include <string>

#include <vector>
class HashTable 
{
private:
	//hash table
	HuffmanNode**		table;
	int					table_size_;
	int					occupied_node;
public:
	//Constructor a hash table - Defaul sub-Bucket = 3
	HashTable();
	HashTable(int);
	void	 createTable(int);
	//Main Hash Functions
	std::string		 hashFunc(std::string key);
	void			 insert(HuffmanNode* c);
	void			 insertbyBit(HuffmanNode* c);
	void			 remove(std::string key);
	std::string		 searchBits(char key);
	char			 searchChar(char);
	void			 displayTable();
	void		     initialize(std::vector<HuffmanNode*>&);
	//Getters
	int				 getSize() const { return table_size_; }
	int				 getOccupiedSize() const{ return occupied_node; }
	HuffmanNode*	 getElement(int i) const{ return table[i]; }

	//Statistics functions
	bool	isEmpty();
	//Destructor for a hash table
	~HashTable();
};
#endif