#include <stack>
#include <string>
#include <iostream>
using namespace std;

class Coord
{
public:
	Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
	int r() const { return m_r; }
	int c() const { return m_c; }
private:
	int m_r;
	int m_c;
};

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
// Return true if there is a path from (sr,sc) to (er,ec)
// through the maze; return false otherwise
{
	stack<Coord> coordStack;					  // declare a stack of Coords
	Coord start(sr, sc);						  // starting coordinate

	coordStack.push(start);
	maze[sr][sc] = '*';							  // indicate algorithm has encountered start

	while (!coordStack.empty())					  // while stack is not empty
	{
		Coord top = coordStack.top();
		coordStack.pop();

		int row = top.r();
		int col = top.c();

		if (row == er && col == ec)
		{
			return true;						  // maze is solved
		}
	
		if (maze[row][col + 1] == '.')			 // if can move EAST (right)
		{
			coordStack.push(Coord(row, col + 1));
			maze[row][col + 1] = '*';
		}

		if (maze[row + 1][col] == '.')			 // if can move SOUTH (down)
		{
			coordStack.push(Coord(row + 1, col));
			maze[row + 1][col] = '*';
		}

		if (maze[row][col - 1] == '.')			 // if can move WEST (left)
		{
			coordStack.push(Coord(row, col - 1));
			maze[row][col - 1] = '*';
		}

		if (maze[row - 1][col] == '.')			 // if can move NORTH (up)
		{
			coordStack.push(Coord(row - 1, col));
			maze[row - 1][col] = '*';
		}

	}
	return false;								// no solution
}

int main()
{
	string maze[10] = {
		"XXXXXXXXXX",
		"X...X..X.X",
		"X..XX....X",
		"X.X.XXXX.X",
		"XXX......X",
		"X...X.XX.X",
		"X.X.X..X.X",
		"X.XXXX.X.X",
		"X..X...X.X",
		"XXXXXXXXXX"
	};

	if (pathExists(maze, 10, 10, 4, 3, 1, 8))
		cout << "Solvable!" << endl;
	else
		cout << "Out of luck!" << endl;
}