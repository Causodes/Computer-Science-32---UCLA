#ifndef MAP_H
#define MAP_H
#include <string>

using KeyType = std::string;
using ValueType = double;

class Map
{
public:
	Map();         // Create an empty map (i.e., one with no key/value pairs)

	~Map();  
	
	Map(const Map &src);

	Map& operator=(const Map &src);
	
	bool empty() const;   // Return true if the map is empty, otherwise false.

	int size() const;    // Return the ValueType of key/value pairs in the map.

	bool insert(const KeyType& key, const ValueType& value);
	// If key is not equal to any key currently in the map, and if the
	// key/value pair can be added to the map, then do so and return true.
	// Otherwise, make no change to the map and return false (indicating
	// that either the key is already in the map, or the map has a fixed
	// capacity and is full).

	bool update(const KeyType& key, const ValueType& value);
	// If key is equal to a key currently in the map, then make that key no
	// longer map to the value it currently maps to, but instead map to
	// the value of the second parameter; return true in this case.
	// Otherwise, make no change to the map and return false.

	bool insertOrUpdate(const KeyType& key, const ValueType& value);
	// If key is equal to a key currently in the map, then make that key no
	// longer map to the value it currently maps to, but instead map to
	// the value of the second parameter; return true in this case.
	// If key is not equal to any key currently in the map and if the
	// key/value pair can be added to the map, then do so and return true.
	// Otherwise, make no change to the map and return false (indicating
	// that the key is not already in the map and the map has a fixed
	// capacity and is full).

	bool erase(const KeyType& key);
	// If key is equal to a key currently in the map, remove the key/value
	// pair with that key from the map and return true.  Otherwise, make
	// no change to the map and return false.

	bool contains(const KeyType& key) const;
	// Return true if key is equal to a key currently in the map, otherwise
	// false.

	bool get(const KeyType& key, ValueType& value) const;
	// If key is equal to a key currently in the map, set value to the
	// value in the map that that key maps to, and return true.  Otherwise,
	// make no change to the value parameter of this function and return
	// false.

	bool get(int i, KeyType& key, ValueType& value) const;
	// If 0 <= i < size(), copy into the key and value parameters the
	// key and value of one of the key/value pairs in the map and return
	// true.  Otherwise, leave the key and value parameters unchanged and
	// return false.  (See below for details about this function.)

	void swap(Map& other);
	// Exchange the contents of this map with the other one.

private:
	int m_size; //Size of map contents

	struct mapPair
	{
		KeyType m_key;
		ValueType m_value;
	};

	struct Node
	{
		mapPair m_pair;
		Node *next;
		Node *previous;
	};

	Node *head;
	Node *tail;
};

bool combine(const Map& m1, const Map& m2, Map& result);
// If a key appears in exactly one of m1 and m2, then result must contain a pair consisting of that key and its corresponding value.
// If a key appears in both m1 and m2, with the same corresponding value in both, then result must contain exactly one pair with that key and value. 

void subtract(const Map& m1, const Map& m2, Map& result);
// When this function returns, result must contain one copy of all the pairs in m1 whose keys don't appear in m2; it must not contain any other pairs. 
// (You must not assume result is empty when it is passed in to this function; it may not be.) 

#endif