#include <iostream>
#include <vector>
#include "Board.cpp"
#include "Piece.cpp"

using namespace std;

class Game
{
public:
	Board board;
	vector <Piece> whitePieces;
	vector <Piece> blackPieces;
	vector <string> possibleMovesWhite;
	vector <string> possibleMovesBlack;
	bool turn = true;
	void setGame()
	{
		Piece* p = new Piece();
		for (int i = 1; i <= 8; i++)
		{
			p->square[0] = 2;

			p->square[1] = i;
			p->sign = 'P';
			this->whitePieces.push_back(*p);

			p->square[0] = 7;
			p->sign = 'p';
			this->blackPieces.push_back(*p);
		}
		p->square[0] = 1;// 1 linia

		p->sign = 'R';
		p->square[1] = 1;
		this->whitePieces.push_back(*p);
		p->square[1] = 8;
		this->whitePieces.push_back(*p);

		p->sign = 'N';
		p->square[1] = 2;
		this->whitePieces.push_back(*p);
		p->square[1] = 7;
		this->whitePieces.push_back(*p);

		p->sign = 'B';
		p->square[1] = 3;
		this->whitePieces.push_back(*p);
		p->square[1] = 6;
		this->whitePieces.push_back(*p);
		
		p->sign = 'Q';
		p->square[1] = 4;
		this->whitePieces.push_back(*p);
		
		p->sign = 'K';
		p->square[1] = 5;
		this->whitePieces.push_back(*p);

		p->square[0] = 7;// 1 linia

		p->sign = 'r';
		p->square[1] = 1;
		this->whitePieces.push_back(*p);
		p->square[1] = 8;
		this->whitePieces.push_back(*p);

		p->sign = 'n';
		p->square[1] = 2;
		this->whitePieces.push_back(*p);
		p->square[1] = 7;
		this->whitePieces.push_back(*p);

		p->sign = 'b';
		p->square[1] = 3;
		this->whitePieces.push_back(*p);
		p->square[1] = 6;
		this->whitePieces.push_back(*p);

		p->sign = 'q';
		p->square[1] = 4;
		this->whitePieces.push_back(*p);

		p->sign = 'k';
		p->square[1] = 5;
		this->whitePieces.push_back(*p);

		delete p;
	}
	void possibleMoves(int oldSquare[2], char piece)
	{
		int newSquare[2];
		switch (piece)
		{
		case 'p':
			if (isFree(0, -1)) addMove(oldSquare, 0, -1);
			if (oldSquare[0] == 7 && isFree(0, -1) && isFree(0, -2)) addMove(oldSquare, 0, -2);
			if (isOpponent(oldSquare,-1, -1)) addMove(oldSquare,-1, -1);
			if (isOpponent(oldSquare,1, -1)) addMove(oldSquare,1, -1);
			break;

		case 'P':
			if (isFree(0, 1)) addMove(oldSquare, 0, 1);
			if (oldSquare[0] == 2 && isFree(0, 1) && isFree(0, 2)) addMove(oldSquare, 0, 2);
			if (isOpponent(oldSquare, -1, 1)) addMove(oldSquare, -1, 1);
			if (isOpponent(oldSquare, 1, 1)) addMove(oldSquare, 1, 1);
			break;

		case 'N':
		case 'n':
			addMove(oldSquare, -2, -1); addMove(oldSquare, -2, 1); addMove(oldSquare, 2, -1); addMove(oldSquare, 2, 1);
			addMove(oldSquare, -1, -2); addMove(oldSquare, -1, 2); addMove(oldSquare, 1, -2); addMove(oldSquare, 1, 2);
			break;

		case 'K':
		case 'k':
			for (int x = -1; x <= 1; x++)
				for (int y = -1; y <= 1; y++)
					addMove(oldSquare,x, y);
			break;

		case 'q':
		case 'Q':
		case 'R':
		case 'r':
			for (int n = 1; n <= 8 && addMove(oldSquare, 0, n) && !isOpponent(oldSquare, 0, n); ++n);
			for (int n = 1; n <= 8 && addMove(oldSquare, 0, -n) && !isOpponent(oldSquare, 0, -n); ++n);
			for (int n = 1; n <= 8 && addMove(oldSquare, n, 0) && !isOpponent(oldSquare, n, 0); ++n);
			for (int n = 1; n <= 8 && addMove(oldSquare, -n, 0) && !isOpponent(oldSquare, -n, 0); ++n);
			if (piece != 'Q' && piece != 'q')
				break;

		case 'b':
		case 'B':
			for (int n = 1; n <= 8 && addMove(oldSquare, n, n) && !isOpponent(oldSquare, n, n); ++n);
			for (int n = 1; n <= 8 && addMove(oldSquare, n, -n) && !isOpponent(oldSquare, n, -n); ++n);
			for (int n = 1; n <= 8 && addMove(oldSquare, -n, n) && !isOpponent(oldSquare, -n, n); ++n);
			for (int n = 1; n <= 8 && addMove(oldSquare, -n, -n) && !isOpponent(oldSquare, -n, -n); ++n);
			break;
			
		default:
			break;
		}

	}

private:
	bool addMove(int from[2], int x, int y)
	{
		if (isFree(x, y) || isOpponent(from, x, y)) {
			char color = this->board.squares[from[0]][from[1]] >= 97 ? 'b' : 'w';
			if (color == 'b')
			{
				string move = to_string(from[0]) + to_string(from[1]) + "-" + to_string(x) + to_string(y);
				this->possibleMovesBlack.push_back(move);
			}
			else
			{
				string move = to_string(from[0]) + to_string(from[1]) + "-" + to_string(x) + to_string(y);
				this->possibleMovesWhite.push_back(move);
			}
			return true;
		}
		return false;
	}

	bool isFree(int x, int y)
	{
		if (x > 8 || x < 1 || y < 1 || y>8)
			return false;

		return this->board.squares[x][y] == ' ';
	}

	bool isOpponent(int from[2], int x, int y)
	{
		if (this->board.squares[x][y] == ' ')
			return false;

		char color = this->board.squares[x][y] >= 97 ? 'b' : 'w';
		char color2 = this->board.squares[x][y] >= 97 ? 'b' : 'w';

		return color != color2;
	}

	
};
int main()
{
	Game a;
	a.board.set();
	a.setGame();
	a.board.show();	
//97 a, 100 d, 104 h 
}
