#include "provided.h"
#include "MyHash.h"
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

class DecrypterImpl
{
public:
	bool load(string filename);
	vector<string> crack(const string& ciphertext);
private:
	void helper(string& input, string& previous, vector<string>& result);
	WordList dictionary;
	Translator mapping; // Begin with empty mapping
	string key = "";
};

bool DecrypterImpl::load(string filename)
{
	if (dictionary.loadWordList(filename))
		return true;
    return false;
}

vector<string> DecrypterImpl::crack(const string& ciphertext)
{
	string temp = ciphertext;
	vector<string> cracked;
	//cout << ciphertext << endl;
	string base = mapping.getTranslation(ciphertext);

	helper(temp, base, cracked);
	return cracked;
}

void DecrypterImpl::helper(string& input, string& previous, vector<string>& result)
{
	Tokenizer seperators(", ; :.!()[] {}-\"#$%^&"); // Tokenize message

	string placeholder = input;

	vector<string> wordList = seperators.tokenize(input); // Populate vector with tokenized message
	vector<string> partDecrypt = seperators.tokenize(previous);

	vector<string>::iterator it = partDecrypt.begin();

	int unknownCount = 0;
	int location = -1;
	int count = 0;

	for (; it != partDecrypt.end(); it++) // Loop to search through tokenized words
	{
		count++;
		string temp = *(it);
		int questionCount = 0;

		for (int i = 0; i < temp.length(); i++) // Searching for word with most '?'
		{
			if (temp[i] == '?')
			{
				questionCount++;
			}
		}


		if (questionCount > unknownCount)
		{
			unknownCount = questionCount;
			location = count;
		}

	}

	string wordChoice = "";
	string transChoice = " ";

	if (location != -1)
	{
		vector<string>::iterator it2 = wordList.begin();

		for (int i = 0; i < location - 1; i++) // Traverse in wordList until reaching correct word
			it2++;

		wordChoice = *(it2);

		transChoice = mapping.getTranslation(wordChoice); // Translate chosen word using current mapping
	}

	vector<string> patternVector = dictionary.findCandidates(wordChoice, transChoice); // Returns vector with candidate words

	if (patternVector.empty()) // If pattern is empty (incorrect mapping) pop and return to previous mapping
	{
		mapping.popMapping();
		return;
	}

	vector<string>::iterator it3 = patternVector.begin();

	for (; it3 != patternVector.end(); it3++)
	{
		string candidate = *(it3);

		if (mapping.pushMapping(wordChoice, candidate)) // If no collision
		{
			string test = mapping.getTranslation(input);
			//cout << test << endl;
			vector<string> testList = seperators.tokenize(test);

			bool flag = true;
			bool flag2 = true;
			bool flag3 = true;

			vector<string>::iterator it4 = testList.begin(); // Check translation
			for (; it4 != testList.end(); it4++) // Iterating through message words
			{
				string temp = *(it4);
				int questionCount = 0;
				for (int i = 0; i < temp.length(); i++)
				{
					if (isupper(temp[i]))
						temp[i] = tolower(temp[i]);
					if (temp[i] == '?')
					{
						questionCount++;
						flag = false;
					}
				}

				if (questionCount == 0)
				{
					if (!dictionary.contains(temp) && flag3) // If fully translated word not found in dictionary
					{
						mapping.popMapping();
						flag2 = false;
						flag3 = false;
					}
				}
			}

			if (!flag && flag2) // All fully translated words found; message not fully translated
			{
				helper(input, test, result);
			}

			else if (flag && flag2) // Message completely decrypted
			{
				bool flag4 = true;
				for (int j = 0; j < testList.size(); j++)
				{
					string tmp = testList[j];
					for (int i = 0; i < tmp.length(); i++)
					{
						if (isupper(tmp[i]))
							tmp[i] = tolower(tmp[i]);
					}
					if (!dictionary.contains(tmp))
						flag4 = false;
				}
				if (flag4)
				{
					result.push_back(test);
					std::sort(result.begin(), result.end());
				}
				mapping.popMapping();
			}	
		}
	}
	mapping.popMapping();
}

//******************** Decrypter functions ************************************

// These functions simply delegate to DecrypterImpl's functions.
// You probably don't want to change any of this code.

Decrypter::Decrypter()
{
    m_impl = new DecrypterImpl;
}

Decrypter::~Decrypter()
{
    delete m_impl;
}

bool Decrypter::load(string filename)
{
    return m_impl->load(filename);
}

vector<string> Decrypter::crack(const string& ciphertext)
{
   return m_impl->crack(ciphertext);
}
