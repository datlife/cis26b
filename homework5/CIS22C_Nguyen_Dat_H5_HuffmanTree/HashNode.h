#ifndef TEAM4_HASH_H_
#define TEAM4_HASH_H_
#include<string>
#include "Product.h"

class HashNode {
private:
	std::string key;
	Product* value;
	int collision_;
public:
	//If the Node is empty, t he default value is -1 (to check isEmpty() node)
	HashNode(){
		collision_ = -1;
	}
	HashNode(Product data){
		key = data.getID();
		value = &data;
	}
	std::string getKey() const { return key; }
	Product getValue() const { return *value; }

	void setKey(std::string new_key) { key = new_key; }
	void setValue(Product new_value) { value = &new_value; }
	void updateCollision() { collision_++; }

	int getCollision() { return collision_; }
	bool isCollided(){ return collision_ > 0; }
	bool isEmpty(){ return 	collision_ == -1; }
};
#endif TEAM4_HASH_H_