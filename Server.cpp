#include <iostream>
#include <vector>
#include <string>
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
	char turn;
	bool getCheck()
	{
		return this->check;
	}

	void setCheck(bool istnienia)
	{
		this->check = istnienia;
	}
	void flipTurn()
	{
		this->turn = this->turn == 'b' ? 'w' : 'b';
	}

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
		this->blackPieces.push_back(*p);
		p->square[1] = 8;
		this->blackPieces.push_back(*p);

		p->sign = 'n';
		p->square[1] = 2;
		this->blackPieces.push_back(*p);
		p->square[1] = 7;
		this->blackPieces.push_back(*p);

		p->sign = 'b';
		p->square[1] = 3;
		this->blackPieces.push_back(*p);
		p->square[1] = 6;
		this->blackPieces.push_back(*p);

		p->sign = 'q';
		p->square[1] = 4;
		this->blackPieces.push_back(*p);

		p->sign = 'k';
		p->square[1] = 5;
		this->blackPieces.push_back(*p);

		delete p;
		setCheck(false);
		this->turn = 'w';
		this->possibleMovesWhite.clear();
		for (auto iter = this->whitePieces.begin(); iter != this->whitePieces.end(); iter++)
			possibleMoves(iter->square,iter->sign);

	}

	void possibleMoves(int oldSquare[2], char piece)
	{
		switch (piece)
		{
		case 'p':
			if (isFree(oldSquare,-1, 0)) addMove(oldSquare, -1, 0);
			if (oldSquare[0] == 7 && isFree(oldSquare, -1, 0) && isFree(oldSquare, -2, 0)) addMove(oldSquare, -2, 0);
			if (isOpponent(oldSquare,-1, -1)) addMove(oldSquare,-1, -1);
			if (isOpponent(oldSquare,-1, 1)) addMove(oldSquare, -1, 1);
			break;

		case 'P':
			if (isFree(oldSquare, 1, 0)) addMove(oldSquare, 1, 0);
			if (oldSquare[0] == 2 && isFree(oldSquare, 1, 0) && isFree(oldSquare, 2, 0)) addMove(oldSquare, 2, 0);
			if (isOpponent(oldSquare, 1, -1)) addMove(oldSquare, 1, -1);
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

	bool isMate(vector<Piece> myPieces, Board board, vector <string> &myMoves, vector<Piece> opponentPieces)
	{
		if (getCheck() == false)
			return false;
		else
		{
			setCheck(false);
			vector <string> truePossibleMoves;
			for (auto iter = myMoves.begin(); iter != myMoves.end(); iter++)
			{
				//makeMove(*iter, board, myPieces, opponentPieces);

				for (auto iter = opponentPieces.begin(); iter != opponentPieces.end(); iter++)
					possibleMoves(iter->square, iter->sign);

				if (getCheck() == false)
					truePossibleMoves.push_back(*iter);

				setCheck(false);
			}

			if (truePossibleMoves.empty())
				return true;
			else
			{
				myMoves = truePossibleMoves;
				return false;
			}
		}
	}
	/*
	void makeMove(string move, Board & board, vector<Piece>& myPieces, vector<Piece>& opponentPieces)
	{
		char sign = board.squares[move[0] - 96][move[1] - 48];
		board.squares[move[0] - 96][move[1]-48] = ' ';
		Piece* p = new Piece();
		if (board.squares[move[3] - 96][move[4] - 48] == ' ')
		{
			p->sign = sign;
			p->square[0] = move[0] - 96;
			p->square[1] = move[1] - 48;

			auto i = find(myPieces.begin(), myPieces.end(), *p);
			i->square[0] = move[3] - 96;
			i->square[1] = move[4] - 48;

			board.squares[move[3] - 96][move[4] - 48] = sign;
			return;
		}
		else
		{
			//usuniecie zbitej bierki
			p->sign = board.squares[move[3] - 96][move[4] - 48]; 
			p->square[0] = move[3] - 96;
			p->square[1] = move[4] - 48;

			auto iter = find(opponentPieces.begin(), opponentPieces.end(), *p);
			if(iter != opponentPieces.end())
				opponentPieces.erase(iter);

			//zmiana 
			p->sign = sign;
			p->square[0] = move[0] - 96;
			p->square[1] = move[1] - 48;

			auto i = find(myPieces.begin(), myPieces.end(), *p);
			i->square[0]= move[3] - 96;
			i->square[1] = move[4] - 48;

			board.squares[move[3] - 96][move[4] - 48] = sign;

			delete p;
		}
	}

	*/
private:
	bool check;
	bool addMove(int from[2], int x, int y)
	{
		if (isFree(from,x, y) || isOpponent(from, x, y)) {
			char color = this->board.squares[from[0]][from[1]] >= 97 ? 'b' : 'w';
			if (color == 'b')
			{
				string move = this->board.coordinates[from[1]] + to_string(from[0]) + "-" + this->board.coordinates[from[1] + y] + to_string(from[0] + x);
				this->possibleMovesBlack.push_back(move);
				if (this->board.squares[x][y] == 'K' && turn == 'w' && this->board.squares[from[0]][from[1]] != 'p')
					setCheck(true);
			}
			else
			{
				string move = this->board.coordinates[from[1]] + to_string(from[0]) + "-" + this->board.coordinates[from[1] + y] + to_string(from[0]+x);
				this->possibleMovesWhite.push_back(move);
				if (this->board.squares[from[0]+x][from[1]+y] == 'k' && turn == 'b' && this->board.squares[from[0]][from[1]] != 'P')
					setCheck(true);
			}
			return true;
		}
		return false;
	}
	bool isInside(int from[2], int x, int y)
	{
		if (from[0] + x > 8 || from[0] + x < 1 || from[1] + y < 1 || from[1] + y>8)
			return false;
		else
			return true;
	}

	bool isFree(int from[2],int x, int y)
	{
		if (!isInside(from,x,y))
			return false;

		return this->board.squares[from[0] + x][from[1] + y] == ' ';
	}

	bool isOpponent(int from[2], int x, int y)
	{
		if (!isInside(from, x, y))
			return false;

		if (this->board.squares[from[0]+x][from[1]+y] == ' ')
			return false;

		char color = this->board.squares[from[0]][from[1]] >= 97 ? 'b' : 'w';
		char color2 = this->board.squares[from[0] + x][from[1] + y] >= 97 ? 'b' : 'w';

		return color != color2;
	}

};
int main()
{
	Game a;
	a.board.set();
	a.setGame();
	while (true)
	{
		string b;
		a.board.show();
		if (a.turn == 'w')
		{
			a.possibleMovesWhite.clear();
			for (auto iter = a.whitePieces.begin(); iter != a.whitePieces.end(); iter++)
				a.possibleMoves(iter->square, iter->sign);

			if (a.isMate(a.whitePieces, a.board, a.possibleMovesWhite, a.blackPieces))
			{
				cout << "CHECKMATE!!!" << endl;
				break;
			}
			else
			{
				cin >> b;
				while (find(a.possibleMovesWhite.begin(), a.possibleMovesWhite.end(), b) == a.possibleMovesWhite.end())
				{
					cout << "nieprawidlowy ruch. Sprobuj ponownie" << endl;
					cin >> b;
				}
				//a.makeMove(b,a.board,a.whitePieces,a.blackPieces);
			}
		}
		else
		{
			a.possibleMovesBlack.clear();
			for (auto iter = a.blackPieces.begin(); iter != a.blackPieces.end(); iter++)
				a.possibleMoves(iter->square, iter->sign);

			if (a.isMate(a.blackPieces, a.board, a.possibleMovesBlack, a.whitePieces))
			{
				cout << "CHECKMATE!!!" << endl;
				break;
			}
			else
			{
				cin >> b;
				while (find(a.possibleMovesBlack.begin(), a.possibleMovesBlack.end(), b) == a.possibleMovesBlack.end())
				{
					cout << "nieprawidlowy ruch. Sprobuj ponownie" << endl;
					cin >> b;
				}
				//a.makeMove(b, a.board, a.blackPieces, a.whitePieces);
			}
		}

		a.setCheck(false);
		a.flipTurn();
	}
	
//97 a, 100 d, 104 h 
}
