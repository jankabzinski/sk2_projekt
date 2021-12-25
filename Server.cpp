#include <iostream>
#include <vector>
#include "Board.cpp"
#include "Piece.cpp"

using namespace std;

bool checkMove(Board board)
{
	return false;
}

class Game
{
public:
	Board board;
	vector <Piece> pieces;
	
	vector <string> possibleMovesWhite;
	vector <string> possibleMovesBlack;
	char turn;
	void setGame()
	{
		for (int i = 1; i <= 8; i++)
		{
			Piece* p = new Pawn();
			p->square[0] = 2;
			p->square[1] = i;
			p->sign = 'P';
			p->addMoves();
			this->pieces.push_back(*p);
		}
	}

	void addMove(int square[2], char piece)
	{
		char color = piece >= 97 ? 'b' : 'w';
		int newSquare[2];
		switch (piece)
		{
		case 'K' || 'k':
			
			checkMove(this->board);
			break;

		default:
			break;
		}

	}
};
int main()
{
	Game a;
	a.board.set();
	a.setGame();
	
	for (auto iter = a.possibleMovesWhite.begin(); iter != a.possibleMovesWhite.end(); iter++)
	{
		cout << *iter << endl;
	}

	for (int i = 1; i <= 8; i++)
	{
		for (int j = 1; j <= 8; j++)
			cout << a.board.squares[i][j] <<" ";
		
		cout << endl;

	}
//97 a, 100 d, 104 h 
}
