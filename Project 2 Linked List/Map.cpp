#include <iostream>
#include "Map.h"

Map::Map() // Default constructor
{
	m_size = 0;
	head = nullptr;
	tail = nullptr;
}

Map::~Map() // Destructor
{
	Node *temp1 = head;
	while (temp1 != nullptr)
	{
		Node *temp2 = temp1->next; 
		delete temp1;
		temp1 = temp2;
	}
}
Map::Map(const Map &src) // Copy Constructor
{
	m_size = 0; //Constructs New Linked List
	head = nullptr;
	tail = nullptr;

	for (int i = 0; i < src.size(); i++) // Loop to Traverse Source
	{
		KeyType key;
		ValueType value;
		src.get(i, key, value);

		insert(key, value); // Populates
	}
}

Map& Map::operator = (const Map &src) // Assignment Operator
{
	if (&src == this) // Aliasing Check
		return (*this);

	Node *temp1 = head;

	while (temp1 != nullptr) // Deletes Existing Map Linked List
	{
		Node *temp2 = temp1->next;
		delete temp1;
		temp1 = temp2;
	}

	m_size = 0; // Constructs New Linked List
	head = nullptr;
	tail = nullptr;

	int c = src.size();

	for (int i = 0; i < src.m_size; i++) // Populates Linked List with Data from Source
	{
		c = c;
		KeyType key;
		ValueType value;
		src.get(i, key, value);

		insert(key, value);
	}
	return (*this);
}

bool Map::empty() const // Checks For If Head Points to nullptr; Empty Linked List
{
	if (head == nullptr)
		return true;
	return false;
}

int Map::size() const // Returns m_size
{
	return m_size;
}

bool Map::get(const KeyType& key, ValueType& value) const // Change to Value Associated with Key
{
	Node *temp = head;
	while (temp != nullptr) // Loop to Traverse Linked List
	{
		if (temp->m_pair.m_key == key)
		{
			value = temp->m_pair.m_value; // If Key Matches, Return Associated Value
			return true;
		}
		temp = temp->next;
	}
	return false;
}

bool Map::get(int i, KeyType& key, ValueType& value) const // Change to Key and Value Associated with ith Element of Linked List
{
	if (i >= 0 && i < m_size) // If i Falls within Valid Parameters
	{
		int j = 0;
		Node *temp = head;
		while (j < i) // Loop to Traverse to ith Element
		{
			temp = temp->next;
			j++;
		}
		key = temp->m_pair.m_key; // Change Key
		value = temp->m_pair.m_value; // Change Value
		return true;
	}
	return false;
}

bool Map::contains(const KeyType& key) const // Check for Linked List Containing Key
{
	Node *temp = head;
	while (temp != nullptr) // Loop to Traverse Linked List
	{
		if (temp->m_pair.m_key == key) // Check for Key Match
			return true;
		temp = temp->next;
	}
	return false;
}

bool Map::insert(const KeyType& key, const ValueType& value) // Insert Node to End of Linked List
{
	if (contains(key)) // Duplicate Node
		return false;
	else if (empty()) // Empty Linked List
	{
		Node *newNode = new Node; // Populate Node with Appropriate Data
		newNode->m_pair.m_key = key;
		newNode->m_pair.m_value = value;

		head = newNode; // Set Node to Both Head and Tail
		head->next = nullptr;
		tail = newNode;
		tail->next = nullptr;
		m_size = 1;

		return true;
	}
	else // General Case Scenario
	{
		Node *newNode = new Node; // Populate Node with Appropriate Data
		newNode->m_pair.m_key = key;
		newNode->m_pair.m_value = value;

		tail->next = newNode; // Add New Node After Current Tail
		newNode->previous = tail; // Link New Node to Tail
		newNode->next = nullptr; // Set New Node as End
		tail = newNode; // Assign New Node Title of Tail

		m_size++; // Increment Size of Linked List by One

		return true;
	}
}

bool Map::update(const KeyType& key, const ValueType& value) // Updates Existing Key with New Value
{
	Node *temp = head;
	while (temp != nullptr) // Loop to Traverse Linked List
	{
		if (temp->m_pair.m_key == key) // If Key Match, Change Associated Value
		{
			temp->m_pair.m_value = value;
			return true;
		}
		temp = temp->next;
	}
	return false;
}

bool Map::insertOrUpdate(const KeyType& key, const ValueType& value) // Update Existing Key with New Value; If Not Found, Insert
{
	if (update(key, value))
		return true;
	else if (insert(key, value))
		return true;
	else
		return false;
}

bool Map::erase(const KeyType& key) // Delete Node with Associated Key
{
	if (m_size == 0) // Empty Map
		return false;
	if (m_size == 1) // Map Populated by Single Node
	{
		if (head->m_pair.m_key == key)
		{
			delete head;
			head = nullptr;
			tail = nullptr;
			m_size = 0;
			return true;
		}
		return false;
	}
	Node *temp = head;
	while (temp != nullptr) // Loop to Traverse Linked List
	{
		if (temp->m_pair.m_key == key) // If Matching Key
		{
			if (temp == head) // Deleting First Node
			{
				head = temp->next; // Change Designation of Second Element to Head
				head->previous = nullptr; // Change New Head to First Node
				delete temp; // Delete Previous Head
			}
			else if (temp == tail) // Deleting Last Node
			{
				tail = temp->previous; // Change Designation of Second to Last Element to Tail
				tail->next = nullptr; // Change New Tail to Last Node
				delete temp; // Delete Previous Tail
			}
			else // General Case
			{
				Node *temp1 = temp->previous;
				temp1->next = temp->next; // Previous Node Points to Succeeding Node
				delete temp; // Delete Node
			}
			m_size--; // Decrement Size

			return true;
		}
		temp = temp->next;
	}
	return false;
}

void Map::swap(Map& other) // Swaps Contents of Two Maps
{
	Map temp = other; // Swap Pointers to Maps
	other = *this;
	*this = temp;
}

// NON MAP FUNCTIONS

bool combine(const Map& m1, const Map& m2, Map& result)
{
	result = m1; // Copy m1 Data into result
	Map tempMap = m2; // Copy m2 Data into Temporary Map
	int flag = 0; // Flag for Key Value Argument: 0 = Pass, 1 = Fail

	for (int i = 0; i < tempMap.size(); i++) // Loop to Traverse tempMap (Contents of m2)
	{
		KeyType tempKey;
		ValueType tempValue1;
		ValueType tempValue2;

		tempMap.get(i, tempKey, tempValue1); // Get Data of Each Node

		if (!result.contains(tempKey)) // If result (m1) Does Not Contain Key
			result.insert(tempKey, tempValue1); // Insert Node to result
		else // If result (m1) Does Contain Key
		{
			result.get(tempKey, tempValue2);
			if (tempValue2 != tempValue1) // If Values Associated With Key Do Not Match
			{
				flag = 1; // Fail
				result.erase(tempKey); // Remove Invalid Node From result (m1)
			}
		}
	}

	if (flag == 1)
		return false;
	return true;
}

void subtract(const Map& m1, const Map& m2, Map& result) // Elements in m1, But Not in m2
{
	Map emptyMap;
	result = emptyMap; // Set result to an Empty Map
	for (int i = 0; i < m1.size(); i++) // Loop to Traverse m1 Linked List
	{
		KeyType tempKey;
		ValueType tempValue;

		m1.get(i, tempKey, tempValue);

		if (!m2.contains(tempKey)) // If m2 Does Not Contain Key from m1
		{
			result.insert(tempKey, tempValue); // Insert Node from m1
		}
	}
}