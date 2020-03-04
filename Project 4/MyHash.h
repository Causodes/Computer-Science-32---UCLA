// MyHash.h

// Skeleton for the MyHash class template.  You must implement the first seven
// member functions; we have implemented the eighth.

#ifndef MYHASH_H_
#define MYHASH_H_

#include <functional>

template<typename KeyType, typename ValueType>
struct Node
{
	Node <KeyType, ValueType> (KeyType key, ValueType value, Node <KeyType, ValueType> *ptr)
	{
		m_key = key;
		m_value = value;
		next = ptr;
	}
	Node *next;
	KeyType m_key;
	ValueType m_value;
};

template<typename KeyType, typename ValueType>
class MyHash
{
public:
	MyHash(double maxLoadFactor = 0.5)
	{
		m_numItems = 0;
		m_capacity = 100;

		m_table = new Node <KeyType, ValueType>* [m_capacity];

		if (maxLoadFactor <= 0)
			m_loadfactor = 0.5;
		else if (maxLoadFactor > 2)
			m_loadfactor = 2;
		else
			m_loadfactor = maxLoadFactor;

		for (int i = 0; i < m_capacity; i++)
			(m_table)[i] = nullptr;
	}

   	~MyHash()
	{
		remove();
	}

	void reset()
	{
		remove();

		m_numItems = 0;
		m_capacity = 100;

		m_table = new Node <KeyType, ValueType>*[m_capacity];

		for (int i = 0; i < 100; i++)
			(m_table)[i] = nullptr;
	}

	void associate(const KeyType& key, const ValueType& value)
	{
		ValueType* val = find(key);

		if (val != nullptr)
			*val = value;
		else
		{
			unsigned int hash(const KeyType& k);  // prototype
			unsigned int bucket = hash(key);
			//unsigned int bucket = std::hash<std::string>()(key);
			bucket = bucket % m_capacity;
			Node <KeyType, ValueType> *entry = new Node <KeyType, ValueType>(key, value, m_table[bucket]);
			(m_table)[bucket] = entry;
			m_numItems++;
		}

		if (getLoadFactor() > m_loadfactor)
		{
			Node <KeyType, ValueType> ** tempTable = new Node<KeyType, ValueType> *[m_capacity * 2];
			for (int i = 0; i < m_capacity * 2; i++)
				(tempTable)[i] = nullptr;

			for (int i = 0; i < m_capacity; i++)
			{
				Node <KeyType, ValueType> *newEntry = m_table[i];
				while (newEntry != nullptr)
				{
					unsigned int hash(const KeyType& k);  // prototype
					unsigned int newBucket = hash(newEntry->m_key);
					//unsigned int newBucket = std::hash<std::string>()(newEntry->m_key);
					newBucket = newBucket % (m_capacity * 2);
					Node <KeyType, ValueType> *tmp = new Node<KeyType, ValueType>(newEntry->m_key, newEntry->m_value, tempTable[newBucket]);
					tempTable[newBucket] = tmp;
					newEntry = newEntry->next;
				}
			}
			remove();
			m_table = tempTable;
			m_capacity *= 2;
		}
	}

	int getNumItems() const
	{
		return m_numItems;
	}

	double getLoadFactor() const
	{
		double loadfactor = (1.0 * m_numItems) / (1.0 * m_capacity);
		return loadfactor;
	}

      // for a map that can't be modified, return a pointer to const ValueType
	const ValueType* find(const KeyType& key) const
	{
		unsigned int hash(const KeyType& k);  // prototype
		unsigned int bucket = hash(key);
		//unsigned int bucket = std::hash<std::string>()(key);
		bucket = bucket % m_capacity;
		const Node <KeyType, ValueType> *current = (m_table)[bucket];

		while (current != nullptr)
		{
			if (current->m_key == key)
				return &(current->m_value);
			else
				current = current->next;
		}
		return nullptr;
	}

      // for a modifiable map, return a pointer to modifiable ValueType
    ValueType* find(const KeyType& key)
    {
        return const_cast<ValueType*>(const_cast<const MyHash*>(this)->find(key));
    }

      // C++11 syntax for preventing copying and assignment
    MyHash(const MyHash&) = delete;
    MyHash& operator=(const MyHash&) = delete;

private:
	int m_capacity;
	int m_numItems;
	double m_loadfactor;
	Node <KeyType, ValueType> ** m_table;

	void remove()
	{
		for (int i = 0; i < m_capacity; i++)
		{
			while (m_table[i] != nullptr)
			{
				Node <KeyType, ValueType> *current = (m_table)[i];
				m_table[i] = m_table[i]->next;
				delete current;
			}
			(m_table)[i] = nullptr;
		}
		delete[] m_table;
	};
};

#endif
