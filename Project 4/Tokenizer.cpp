#include "provided.h"
#include <string>
#include <vector>
using namespace std;

class TokenizerImpl
{
public:
    TokenizerImpl(string separators);
    vector<string> tokenize(const std::string& s) const;
private:
	string m_separators;
};

TokenizerImpl::TokenizerImpl(string separators)
{
	m_separators = separators;
}

vector<string> TokenizerImpl::tokenize(const std::string& s) const
{
	vector<string> m_words;

	string tmp = "";

	for (int i = 0; i < s.size(); i++)
	{
		bool flag = true;
		for (int j = 0; j < m_separators.size(); j++)
		{
			if (s[i] == m_separators[j])
			{
				flag = false;
				if (tmp != "")
					m_words.push_back(tmp);
				tmp = "";
			}
		}
		if (flag)
			tmp = tmp + s[i];
	}

	if (tmp != "")
		m_words.push_back(tmp);

    return m_words;
}

//******************** Tokenizer functions ************************************

// These functions simply delegate to TokenizerImpl's functions.
// You probably don't want to change any of this code.

Tokenizer::Tokenizer(string separators)
{
    m_impl = new TokenizerImpl(separators);
}

Tokenizer::~Tokenizer()
{
    delete m_impl;
}

vector<string> Tokenizer::tokenize(const std::string& s) const
{
    return m_impl->tokenize(s);
}
