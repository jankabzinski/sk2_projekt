#include <iostream>
using namespace std;
class Board
{
public:
	char squares[8][8];
	void set()
	{
		for (int i = 0; i < 8; i++)
		{
			squares[1][i] = 'P';
			squares[6][i] = 'p';
			for (int y = 2; y < 6; y++)
				squares[y][i] = ' ';

		}
		squares[0][0] = squares[0][7] = 'R';
		squares[0][1] = squares[0][6] = 'N';
		squares[0][2] = squares[0][5] = 'B';
		squares[0][3] = 'Q';
		squares[0][4] = 'K';
		squares[7][0] = squares[7][7] = 'r';
		squares[7][1] = squares[7][6] = 'n';
		squares[7][2] = squares[7][5] = 'b';
		squares[7][3] = 'q';
		squares[7][4] = 'k';
	}

};