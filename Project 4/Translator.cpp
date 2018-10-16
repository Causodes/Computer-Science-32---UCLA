#include "provided.h"
#include <string>
#include <vector>
using namespace std;

class TranslatorImpl
{
public:
	TranslatorImpl();
	~TranslatorImpl();
    bool pushMapping(string ciphertext, string plaintext);
    bool popMapping();
    string getTranslation(const string& ciphertext) const;
private:
	vector<string> *currentmapping;
	vector<string> *alreadymapped;
};

TranslatorImpl::TranslatorImpl()
{
	alreadymapped = new vector<string>;
	currentmapping = new vector<string>;
}

TranslatorImpl::~TranslatorImpl()
{
	vector<string>::iterator it = alreadymapped->begin();
	while (it != alreadymapped->end())
	{
		delete &it;
		it = alreadymapped->erase(it);
	}

	alreadymapped->clear();

	delete alreadymapped;

	vector<string>::iterator it2 = currentmapping->begin();
	while (it2 != currentmapping->end())
	{
		delete &it2;
		it2 = currentmapping->erase(it2);
	}

	currentmapping->clear();

	delete currentmapping;
}

bool TranslatorImpl::pushMapping(string ciphertext, string plaintext)
{
	if (ciphertext.length() != plaintext.length())
		return false;

	string temp1;
	string temp2;

	if (alreadymapped->empty() || currentmapping->empty())
	{
		temp1 = "??????????????????????????";
		temp2 = "??????????????????????????";
	}

	else
	{
		 temp1 = alreadymapped->back();
		 temp2 = currentmapping->back();
	}

	for (int i = 0; i < ciphertext.length(); i++)
	{
		int index1 = tolower(plaintext[i]) - 'a'; // Determines index to insert plaintext to alreadymapped
		int index2 = tolower(ciphertext[i]) - 'a'; // Determines index to insert ciphertext to currentmapping

		if (!isalpha(ciphertext[i]) || !isalpha(plaintext[i])) // Check for nonalphabetic character
			return false;

		if (toupper(temp1[index2]) != toupper(plaintext[i]) && temp1[index2] != '?') // Check for collision
			return false;

		if (toupper(temp2[index1]) != toupper(ciphertext[i]) && temp2[index1] != '?') // Check for collision
			return false;

		temp1[index2] = toupper(plaintext[i]);
		temp2[index1] = toupper(ciphertext[i]);
	}
	alreadymapped->push_back(temp1);
	currentmapping->push_back(temp2);

	return true;
}

bool TranslatorImpl::popMapping()
{
	if (alreadymapped->size() == 0 || currentmapping->size() == 0)
		return false;
	else
	{
		alreadymapped->pop_back();
		currentmapping->pop_back();

		return true;
	}
    return false; 
}

string TranslatorImpl::getTranslation(const string& ciphertext) const
{
	string translationKey;
	
	if (alreadymapped->size() == 0 || currentmapping->size() == 0)
		translationKey = "??????????????????????????";
	else
		translationKey = alreadymapped->back(); // Retrieves current mapping
		
	string translation = "";



	for (int i = 0; i < ciphertext.length(); i++)
	{
 		if (!isalpha(ciphertext[i])) // Nonalphabetical Character
			translation = translation + ciphertext[i];

		else if (!isupper(ciphertext[i])) // Nonuppercase Character
		{
			int index = toupper(ciphertext[i]) - 'A';
			char key = translationKey[index]; // Retrieve character
			key = tolower(key);
			translation = translation + key;
		}
		else // Uppercase Character
		{
			int index = toupper(ciphertext[i]) - 'A';
			char key = translationKey[index]; // Retrieve character
			translation = translation + key;
		}
	}
    return translation;
}

//******************** Translator functions ************************************

// These functions simply delegate to TranslatorImpl's functions.
// You probably don't want to change any of this code.

Translator::Translator()
{
    m_impl = new TranslatorImpl;
}

Translator::~Translator()
{
    delete m_impl;
}

bool Translator::pushMapping(string ciphertext, string plaintext)
{
    return m_impl->pushMapping(ciphertext, plaintext);
}

bool Translator::popMapping()
{
    return m_impl->popMapping();
}

string Translator::getTranslation(const string& ciphertext) const
{
    return m_impl->getTranslation(ciphertext);
}