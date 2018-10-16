#include "Map.h"
#include <iostream>

Map::Map()
{
	m_size = 0;
}

bool Map::empty() const
{
	if (m_size == 0)
		return true;
	else
		return false;
}

int Map::size() const
{
	return m_size;
}

bool Map::contains(const KeyType& key) const
{
	for (int i = 0; i < m_size; i++)
	{
		if (m_pairs[i].m_key == key)
			return true;
	}
	return false;
}

bool Map::get(const KeyType& key, ValueType& value) const
{
	for (int i = 0; i < m_size; i++)
	{
		if (m_pairs[i].m_key == key)
		{
			value = m_pairs[i].m_value;
			return true;
		}
	}
	return false;
}

bool Map::insert(const KeyType& key, const ValueType& value)
{
	if (m_size == DEFAULT_MAX_ITEMS)
		return false;
	else if (contains(key))
		return false;
	else
	{
		m_pairs[m_size].m_key = key;
		m_pairs[m_size].m_value = value;
		m_size++;

		return true;
	}
}

bool Map::update(const KeyType& key, const ValueType& value)
{
	for (int i = 0; i < m_size; i++)
		if (m_pairs[i].m_key == key)
		{
			m_pairs[i].m_value = value;
			return true;
		}
	return false;
}

bool Map::insertOrUpdate(const KeyType& key, const ValueType& value)
{
	if (update(key, value))
		return true;
	else if (insert(key, value))
		return true;
	else
		return false;
}

bool Map::erase(const KeyType& key)
{
	for (int i = 0; i < m_size; i++)
	{
		if (m_pairs[i].m_key == key)
		{
			for (int j = i; j < m_size - 1; j++)
			{
				m_pairs[j] = m_pairs[j + 1];	
			}
			m_size--;
			return true;
		}
	}
	return false;
}

void Map::swap(Map& other)
{
	Map temp = *this;
	*this = other;
	other = temp;
}

bool Map::get(int i, KeyType& key, ValueType& value) const
{
	if (i >= 0 && i < m_size)
	{
		key = m_pairs[i].m_key;
		value = m_pairs[i].m_value;
		return true;
	}
	return false;
}