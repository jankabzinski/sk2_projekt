#include <iostream>
#include <vector>
#include "Board.cpp"
#include "Piece.cpp"

using namespace std;

class Game
{
public:
	Board board;
	vector <Piece> pieces;
	vector <string> possibleMoves;
};
int main()
{
	Game a;
	a.board.set();
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
			cout << a.board.squares[i][j] <<" ";
		
		cout << endl;

	}
//97 a, 100 d, 104 h 
}
