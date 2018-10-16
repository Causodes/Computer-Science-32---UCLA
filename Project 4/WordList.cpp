#include "provided.h"
#include "MyHash.h"
#include <string>
#include <vector>
#include <fstream>
#include <cctype>
using namespace std;

class WordListImpl
{
public:
    bool loadWordList(string filename);
    bool contains(string word) const;
    vector<string> findCandidates(string cipherWord, string currTranslation) const;
private:
	MyHash<string, bool> wordList;
	MyHash<string, vector<string>> patternList;
};

bool WordListImpl::loadWordList(string filename)
{
	ifstream dict(filename);

	if (!dict) // Check for successful word list loading
		return false;

	wordList.reset();
	patternList.reset();

	string str;
	bool flag = true;

	while (getline(dict, str))
	{
		for (int i = 0; i < str.length(); i++)
		{
			flag = true;

			if (isalpha(str[i]) || str[i] == '\'') // Check for valid characters
			{
				if (str[i] != '\'') // Conversion to all lowercase
					str[i] = tolower(str[i]);
			}
			else
			{
				flag = false; // If invalid character found inside string
				break;
			}
		}

		if (!flag) // If invalid character found inside string
			continue;

		wordList.associate(str, true);

		string pattern = "";
		char code = 'a';

		char encodingArray[26] = {};
		for (int i = 0; i < 26; i++)
			encodingArray[i] = '0';

		for (int i = 0; i < str.length(); i++) // Encodes given string to a specified pattern
		{
			if (isalpha(str[i]))
			{
				int index = tolower(str[i]) - 'a';
				if (encodingArray[index] == '0')
				{
					encodingArray[index] = code;
					code++;
				}
				pattern = pattern + encodingArray[index];
			}
			else
				pattern = pattern + str[i];
		}

		if (patternList.find(pattern) != nullptr)
		{
			vector<string> *patternVector = patternList.find(pattern);
			patternVector->push_back(str);
			patternList.associate(pattern, *patternVector);
		}
		else
		{
			vector<string> patternVector;
			patternVector.push_back(str);
			patternList.associate(pattern, patternVector);


		}
	}
    return true;
}

bool WordListImpl::contains(string word) const
{
	if (wordList.find(word) == nullptr)
		return false;
	else
		return true;
}

vector<string> WordListImpl::findCandidates(string cipherWord, string currTranslation) const
{
	if(cipherWord.length() != currTranslation.length())
		return vector<string>();

	string pattern = "";
	char code = 'a';

	char encodingArray[26] = {};
	for (int i = 0; i < 26; i++)
		encodingArray[i] = '0';

	string temp = cipherWord;

	for (int i = 0; i < cipherWord.length(); i++) // Encodes cipherWord string to previous pattern
	{
		int index = tolower(temp[i]) - 'a';
		if (isalpha(temp[i]))
		{
			if (encodingArray[index] == '0')
			{
				encodingArray[index] = code;
				code++;
			}
			pattern = pattern + encodingArray[index];
		}
		else if(temp[i] == '\'')
			pattern = pattern + '\'';
	}

	const vector<string> *candidateVector = patternList.find(pattern);

	vector<string>::const_iterator it = candidateVector->begin();

	vector<string> finalVector;
	bool flag = true;

	for (; it != candidateVector->end(); it++)
	{
		flag = true;

		for (int i = 0; i < currTranslation.length(); i++)
		{
			if (currTranslation[i] == '?')
				continue;
			else if (currTranslation[i] != '?' && currTranslation[i] != '\'' && !isalpha(currTranslation[i]))
				return vector<string>();
			else if (tolower(currTranslation[i]) != (*it)[i])
			{
				flag = false;
				break;
			}
		}

		if (!flag)
			continue;

		finalVector.push_back((*it));
	}

	return finalVector;
}

//***** hash functions for string, int, and char *****

unsigned int hash(const std::string& s)
{
    return std::hash<std::string>()(s);
}

unsigned int hash(const int& i)
{
    return std::hash<int>()(i);
}

unsigned int hash(const char& c)
{
    return std::hash<char>()(c);
}

//******************** WordList functions ************************************

// These functions simply delegate to WordListImpl's functions.
// You probably don't want to change any of this code.

WordList::WordList()
{
    m_impl = new WordListImpl;
}

WordList::~WordList()
{
    delete m_impl;
}

bool WordList::loadWordList(string filename)
{
    return m_impl->loadWordList(filename);
}

bool WordList::contains(string word) const
{
    return m_impl->contains(word);
}

vector<string> WordList::findCandidates(string cipherWord, string currTranslation) const
{
   return m_impl->findCandidates(cipherWord, currTranslation);
}
