#include "Map.h"
#include <iostream>
#include <string>
#include <stack>
#include <cctype>
#include <cassert>
using namespace std;

bool validInFix(string infix);
bool validOperands(string infix, const Map& values);
string convertPostFix(string infix);

int evaluate(string infix, const Map& values, string& postfix, int& result)
{
	if (!validInFix(infix))																																						// input must be valid
		return 1;

	postfix = convertPostFix(infix);

	if (!validOperands(infix, values))																																			// all characters must appear in map
		return 2;
																																												// evaluation of expression per pseudocode
	stack<int> answerStack;

	for (int i = 0; i < postfix.size(); i++)
	{
		char c = postfix[i];

		if (isalpha(c))
		{
			int value;
			values.get(c, value);
			answerStack.push(value);
		}

		else
		{
			int value2 = answerStack.top();
			answerStack.pop();

			int value1 = answerStack.top();
			answerStack.pop();

			switch (c)
			{
			case '+':
				answerStack.push(value1 + value2);
				break;
			case '-':
				answerStack.push(value1 - value2);
				break;
			case '*':
				answerStack.push(value1 * value2);
				break;
			case '/':
				if (value2 == 0)
					return 3;
				answerStack.push(value1 / value2);
					break;
			}
		}
	}
	result = answerStack.top();
	return 0;
}

bool validInFix(string infix)
{
	if (infix == "")
		return false;																																							// infix cannot be empty

	else if (infix.size() == 1)																																					// if single element, must be lowercase character
		if (isalpha(infix[0]) && islower(infix[0]))	
			return true;
		else
			return false;
	else
	{
		int leftParantheses = 0;
		int rightParantheses = 0;
		int letterCount = 0;
		int operatorCount = 0;

		for (int i = 0; i < infix.size(); i++)
		{
			char c = infix[i];

			if (isalpha(c) && isupper(c))																																		// no character can be uppercase
				return false;
			if (!isalpha(c) && !(c == ' ' || c == '(' || c == ')' || c == '+' || c == '-' || c == '*' || c == '/'))																// non character and non valid operator
				return false;


			if (c == '(')
				leftParantheses++;
			if (c == ')')
				rightParantheses++;
			if (isalpha(c))
				letterCount++;
			if (c == '+' || c == '-' || c == '*' || c == '/')
				operatorCount++;
		}

		if (leftParantheses != rightParantheses)																																// number of parantheses must match			
			return false;	
		if (operatorCount + 1 != letterCount)																																	// always one more letter than operator
			return false;
	}

	string noSpacesOrParantheses = "";

	for (int i = 0; i < infix.size(); i++)																																		// creates new string only containing operators and characters
	{
		char c = infix[i];
		if (isalpha(c) || c == '+' || c == '-' || c == '*' || c == '/')
			noSpacesOrParantheses += c;

		//if (i != 0)
		//{
		//	if (isalpha(c))
		//	{																																									// traverses backwards until next letter reached
		//		int j = i - 1;
		//		int flag = 0;																																					// number of operators detected
		//		while (j >= 0)
		//		{
		//			if (noSpacesOrParantheses[j] == '+' || noSpacesOrParantheses[j] == '-' || noSpacesOrParantheses[j] == '*' || noSpacesOrParantheses[j] == '/')				// operator detected
		//				flag++;
		//			if (isalpha(infix[j]))																																		// previous character reached
		//				break;
		//			j--;
		//		}
		//		if (flag != 1) 
		//			return false;
		//	}
		//}
	}

	for (int i = 0; i < noSpacesOrParantheses.size(); i++)																													 
	{
		char c = noSpacesOrParantheses[i];
		if (i % 2 == 0)																																							// even positions should be characters
		{
			if (!isalpha(c))
				return false;
		}
		else                                                                                                                                                                    // odd positions should be operators
		{
			if (c != '+' && c != '-' && c != '*' && c != '/')
				return false;
		}
	}


	if (noSpacesOrParantheses.size() == 0)																																		// no operators or characters
		return false;
	if (!isalpha(noSpacesOrParantheses[0]))																																		// first character not a letter
		return false;
	if (!isalpha(noSpacesOrParantheses[noSpacesOrParantheses.size() - 1]))																										// last character not a letter
		return false;

	string noSpaces = "";

	for (int i = 0; i < infix.size(); i++)																																		// creates new string only containing operators, characters, and parantheses
	{
		char c = infix[i];
		if (isalpha(c) || c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')')
			noSpaces += c;
	}
	for (int i = 0; i < noSpaces.size(); i++)																																	// no empty parantheses
		if (noSpaces[i] == '(' && noSpaces[i + 1] == ')')
			return false;
	for (int i = 0; i < noSpaces.size(); i++)
	{
		if (noSpaces[i] == '(')
		{
			int j = i;
			while (noSpaces[j] == '(')
				j++;
			if (!isalpha(noSpaces[j]))
				return false;
		}
		if (noSpaces[i] == ')')
		{
			int j = i;
			while (noSpaces[j] == ')')
				j--;
			if (!isalpha(noSpaces[j]))
				return false;
		}
	}


}

bool validOperands(string infix, const Map& values)																																// checks all characters are in map
{
	for (int i = 0; i < infix.size(); i++)
	{
		char c = infix[i];
		if (isalpha(c) && !values.contains(c))																																	// if character does not appear in map
			return false;
	}
	return true;
}

bool compare(char c, char other)																																				// compare precedence of ch <= precedence of stack top
{
	if ((c == '+' || c == '-') && (other == '*' || other == '/'))
		return true;
	return false;
}

string convertPostFix(string infix)																																				// infix to postfix conversion per provided pseudocode
{
	string postfix = "";
	stack<char> operatorStack;

	for (int i = 0; i < infix.size(); i++)
	{
		char c = infix[i];

		if (isalpha(c))
		{
			postfix += c;
			continue;
		}

		if (c == ' ')
			continue;

		switch (c)
		{
		case '(': 
			operatorStack.push(c); 
			break;

		case ')':
			while (!operatorStack.empty() && operatorStack.top() != '(')
			{
				postfix += operatorStack.top();
				operatorStack.pop();
			}
			operatorStack.pop();
			break;

		case '+':
		case '-':
		case '*':
		case '/':
			while (!operatorStack.empty() && operatorStack.top() != '(' && compare(c, operatorStack.top()))
			{
				postfix += operatorStack.top();
				operatorStack.pop();
			}
			operatorStack.push(c);
			break;
		}
	}

	while (!operatorStack.empty())
	{
		postfix += operatorStack.top();
		operatorStack.pop();
	}
	return postfix;
}

int main()
{
	char vars[] = { 'a', 'e', 'i', 'o', 'u', 'y', '#' };
	int  vals[] = { 3,  -9,   6,   2,   4,   1 };
	Map m;
	for (int k = 0; vars[k] != '#'; k++)
		m.insert(vars[k], vals[k]);
	string pf;
	int answer;
	evaluate("a+ e", m, pf, answer);
	assert(evaluate("a+ e", m, pf, answer) == 0 &&
		pf == "ae+"  &&  answer == -6);
	answer = 999;
	assert(evaluate("", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("a+", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("a i", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("ai", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("()", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("y(o+u)", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("a+E", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("(a+(i-o)", m, pf, answer) == 1 && answer == 999);
	// unary operators not allowed:
	assert(evaluate("-a", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("a*b", m, pf, answer) == 2 &&
		pf == "ab*"  &&  answer == 999);
	assert(evaluate("y +o *(   a-u)  ", m, pf, answer) == 0 &&
		pf == "yoau-*+"  &&  answer == -1);
	answer = 999;
	assert(evaluate("o/(y-y)", m, pf, answer) == 3 &&
		pf == "oyy-/"  &&  answer == 999);
	assert(evaluate(" a  ", m, pf, answer) == 0 &&
		pf == "a"  &&  answer == 3);
	assert(evaluate("((a))", m, pf, answer) == 0 &&
		pf == "a"  &&  answer == 3);
	assert(evaluate("(e-i)/(u-y)", m, pf, answer) == 0 &&
		pf == "ei-uy-/" && answer == -5);
	assert(evaluate("((e-i)/(u-y*a))", m, pf, answer) == 0 &&
		pf == "ei-uya*-/" && answer == -15);
	cout << "Passed all tests" << endl;
	return 0;
}