#include <iostream>
using namespace std;
class Board
{
public:
	char squares[9][9];
	void set()
	{
		for (int i = 1; i <= 8; i++)
		{
			squares[2][i] = 'P';
			squares[7][i] = 'p';
			for (int y = 3; y <= 6; y++)
				squares[y][i] = '|';

		}
		squares[1][1] = squares[1][8] = 'R';
		squares[1][2] = squares[1][7] = 'N';
		squares[1][3] = squares[1][6] = 'B';
		squares[1][4] = 'Q';
		squares[1][5] = 'K';
		squares[8][1] = squares[8][8] = 'r';
		squares[8][2] = squares[8][7] = 'n';
		squares[8][3] = squares[8][6] = 'b';
		squares[8][4] = 'q';
		squares[8][5] = 'k';
	}

};