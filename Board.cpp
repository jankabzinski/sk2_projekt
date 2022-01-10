#include <iostream>
#include <map>
#include <string>
#include <fstream>
using namespace std;
class Board
{
public:
	string coordinates = " abcdefgh";
	map <char, int> transform = { {'a',1}, {'b',2}, {'c',3}, { 'd',4},{'e',5},{'f',6},{'g',7},{'h',8}};

	char squares[9][9];
	void set()
	{
		squares[0][0] = ' ';
		for (int i = 1; i <= 8; i++)
		{
			squares[0][i] = this->coordinates[i];
			squares[i][0] = i + 48;
			squares[2][i] = 'P';
			squares[7][i] = 'p';
			for (int y = 3; y <= 6; y++)
				squares[y][i] = ' ';

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
	void show()
	{
		fstream out;
		out.open("out.txt",ios::out);
		for (int i = 8; i >= 0; i--)
		{
			for (int j = 0; j <= 8; j++)
				cout << this->squares[i][j];

			cout << endl;
		}
		out.close();
	}
};