//History.cpp

#include <iostream>
#include "History.h"
#include "globals.h"
using namespace std;

History::History(int nRows, int nCols)
{
	m_rows = nRows;
	m_cols = nCols;

	for (int i = 0; i < m_rows; i++) //populates array with dots
	{
		for (int j = 0; j < m_cols; j++)
		{
			marker[i][j] = '.';
		}
	}
}

bool History::record(int r, int c)
{
	if (r <= 0 || r > m_rows || c <= 0 || c > m_cols) //boundcheck
	{
		return false;
	}

	else
	{

		if (marker[r - 1][c - 1]>= 'A' && marker[r - 1][c - 1] < 'Z') //check for in bounds
		{
			marker[r - 1][c - 1]++;
		}
		else if (marker[r - 1][c - 1] == 'Z')// lower bound
		{
			marker[r - 1][c - 1] = 'Z';
		}
		else //new marker
		{
			marker[r - 1][c - 1] = 'A';
		}

		return true;
	}
}

void History::display() const
{
	clearScreen();
	for (int i = 0; i < m_rows; i++)
	{
		for (int j = 0; j < m_cols; j++)
		{
			cout << marker[i][j];
		}
		cout << endl;
	}
	cout << endl;
}