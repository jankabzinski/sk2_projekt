#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Board
{
public:
	string coordinates = " abcdefgh";
	char squares[9][9] = {' '};
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
		out.open("out.txt", ios::out);
		for (int i = 8; i >= 0; i--)
		{
			for (int j = 0; j <= 8; j++)
				cout << this->squares[i][j];

			cout << endl;
		}
		out.close();
	}
};

class Piece {
public:
	int square[2];
	char sign;
};


class Game
{
public:
	Board board;
	vector <Piece> whitePieces;
	vector <Piece> blackPieces;
	vector <string> possibleMovesWhite;
	vector <string> possibleMovesBlack;
	char turn = 'w';
	bool checkInspect = false;
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

		p->square[0] = 8;// 8 linia

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
		this->checkInspect = true;
		for (auto iter = opponentPieces.begin(); iter != opponentPieces.end(); iter++)
			this->possibleMoves(iter->square, iter->sign);

		if (getCheck() == false)
		{
			this->checkInspect = false;
			return false;
		}
		else
		{
			vector <string> truePossibleMoves;
			Board bCopy = this->board;
			vector<Piece> opCopy = opponentPieces;
			vector <Piece> myCopy = myPieces;

			if (this->turn == 'w')
				this->possibleMovesBlack.clear();
			else
				this->possibleMovesWhite.clear();

			for (auto iter = myMoves.begin(); iter != myMoves.end(); iter++)
			{
				myPieces = myCopy;
				board = bCopy;
				opponentPieces = opCopy;
				setCheck(false);

				makeMove(*iter, board, myPieces, opponentPieces);

				this->board = board;
				for (auto i = opponentPieces.begin(); i != opponentPieces.end(); i++)
					this->possibleMoves(i->square, i->sign);

				this->board = bCopy;
				if (getCheck() == false)
					truePossibleMoves.push_back(*iter);
			}

			this->checkInspect = false;

			if (truePossibleMoves.empty())
				return true;
			else
			{
				myMoves = truePossibleMoves;
				return false;
			}
		}
	}
	void areLegal(Board board, vector <string>& myMoves, vector<Piece> myPieces, vector<Piece> opponentPieces)
	{
		Board bCopy = this->board;
		vector<Piece> opCopy = opponentPieces;
		vector <Piece> myCopy = myPieces;

		this->checkInspect = true;
		
		for (auto move = myMoves.begin(); move != myMoves.end(); move++)
		{
			setCheck(false);
			board = bCopy;
			opponentPieces = opCopy;
			myPieces = myCopy;
			this->makeMove(*move, board, myPieces, opponentPieces);

			this->board = board;
			for (auto i = opponentPieces.begin(); i != opponentPieces.end(); i++)
				this->possibleMoves(i->square, i->sign);

			this->board = bCopy;

			if (getCheck() == true)
			{
				myMoves.erase(move--);//przesuniecie wskaznika do tylu, 
				//bo po usunieciu przesuwa nam sie do przodu i ominelibysmy jeden element
			}
		}
		this->checkInspect = false;
	}

	void makeMove(string move, Board & board, vector<Piece>& myPieces, vector<Piece>& opponentPieces)
	{
		char sign;
		if (move != "O-O" && move != "O-O-O")
		{
			sign = board.squares[move[1] - 48][move[0] - 96];
			board.squares[move[1] - 48][move[0] - 96] = ' ';
			if (board.squares[move[4] - 48][move[3] - 96] == ' ')
			{
				for (auto i = 0; i < myPieces.size(); i++)
				{
					if (myPieces[i].sign == sign && myPieces[i].square[0] == move[1] - 48 && myPieces[i].square[1] == move[0] - 96)
					{
						myPieces[i].square[0] = move[4] - 48;
						myPieces[i].square[1] = move[3] - 96;
						break;
					}
				}
				board.squares[move[4] - 48][move[3] - 96] = sign;
			}
			else
			{
				for (auto i = opponentPieces.begin(); i != opponentPieces.end(); i++)
				{
					if (i->sign == board.squares[move[4] - 48][move[3] - 96] && i->square[0] == move[4] - 48 && i->square[1] == move[3] - 96)
					{
						opponentPieces.erase(i);
						break;
					}
				}
				board.squares[move[4] - 48][move[3] - 96] = sign;

				//zmiana 
				for (auto i = 0; i < myPieces.size(); i++)
				{
					if (myPieces[i].sign == sign && myPieces[i].square[0] == move[1] - 48 && myPieces[i].square[1] == move[0] - 96)
					{
						myPieces[i].square[0] = move[4] - 48;
						myPieces[i].square[1] = move[3] - 96;
						break;
					}
				}
				board.squares[move[4] - 48][move[3] - 96] = sign;
			}
		}
		else
		{
			if (this->turn == 'w')
			{
				if (move == "O-O")
				{
					board.squares[1][5] = ' ';
					board.squares[1][6] = 'R';
					board.squares[1][7] = 'K';
					board.squares[1][8] = ' ';
					sign = 'K';
					for (auto i = 0; i < myPieces.size(); i++)
					{
						if (myPieces[i].sign == sign)
						{
							myPieces[i].square[1] = 7 + 48;
							break;
						}
					}
					sign = 'R';
					for (auto i = 0; i < myPieces.size(); i++)
					{
						if (myPieces[i].sign == sign && myPieces[i].square[1] == 8 + 48)
						{
							myPieces[i].square[1] = 6 + 48;
							break;
						}
					}
				}
				else
				{
					board.squares[1][5] = ' ';
					board.squares[1][4] = 'R';
					board.squares[1][3] = 'K';
					board.squares[1][1] = ' ';
					sign = 'K';
					for (auto i = 0; i < myPieces.size(); i++)
					{
						if (myPieces[i].sign == sign)
						{
							myPieces[i].square[1] = 3 + 48;
							break;
						}
					}
					sign = 'R';
					for (auto i = 0; i < myPieces.size(); i++)
					{
						if (myPieces[i].sign == sign && myPieces[i].square[1] == 1 + 48)
						{
							myPieces[i].square[1] = 4 + 48;
							break;
						}
					}
				}
			}
			else
			{
				if (move == "O-O")
				{
					board.squares[8][5] = ' ';
					board.squares[8][6] = 'r';
					board.squares[8][7] = 'k';
					board.squares[8][8] = ' ';
					sign = 'k';
					for (auto i = 0; i < myPieces.size(); i++)
					{
						if (myPieces[i].sign == sign)
						{
							myPieces[i].square[1] = 7 + 48;
							break;
						}
					}
					sign = 'r';
					for (auto i = 0; i < myPieces.size(); i++)
					{
						if (myPieces[i].sign == sign && myPieces[i].square[1] == 8 + 48)
						{
							myPieces[i].square[1] = 6 + 48;
							break;
						}
					}
				}
				else
				{
					board.squares[8][5] = ' ';
					board.squares[8][4] = 'r';
					board.squares[8][3] = 'k';
					board.squares[8][1] = ' ';
					sign = 'k';
					for (auto i = 0; i < myPieces.size(); i++)
					{
						if (myPieces[i].sign == sign)
						{
							myPieces[i].square[1] = 3 + 48;
							break;
						}
					}
					sign = 'r';
					for (auto i = 0; i < myPieces.size(); i++)
					{
						if (myPieces[i].sign == sign && myPieces[i].square[1] == 1 + 48)
						{
							myPieces[i].square[1] = 4 + 48;
							break;
						}
					}
				}
			}
		}
	}
	void isCastlingPossible(vector<Piece> wPieces, vector<Piece>  bPieces)
	{
		if (this->turn == 'w')
		{
			if (this->board.squares[1][5] != 'K')
				return;
			else
			{
				if (this->board.squares[1][8] == 'R' && this->board.squares[1][7] == ' ' && this->board.squares[1][6] == ' ')
				{
					if (find(this->possibleMovesWhite.begin(), this->possibleMovesWhite.end(), "e1-f1") != this->possibleMovesWhite.end())
					{
						this->checkInspect = true;
						setCheck(false);

						for (auto i = bPieces.begin(); i != bPieces.end(); i++)
							this->possibleMoves(i->square, i->sign);

						if (getCheck() == false)
						{
							Board board = this->board;
							this->makeMove("e1 - g1", this->board, wPieces, bPieces);
							for (auto i = bPieces.begin(); i != bPieces.end(); i++)
								this->possibleMoves(i->square, i->sign);

							this->board = board;
							this->checkInspect = false;
							if (getCheck() == false)
								this->possibleMovesWhite.push_back("O-O");
						}
						else
						{
							this->checkInspect = false;
							setCheck(false);
						}
					}
				}
				if (this->board.squares[1][1] == 'R' && this->board.squares[1][2] == ' ' &&
					this->board.squares[1][3] == ' ' && this->board.squares[1][4] == ' ')
				{
					if (find(this->possibleMovesWhite.begin(), this->possibleMovesWhite.end(), "e1-d1") != this->possibleMovesWhite.end())
					{
						setCheck(false);
						this->checkInspect = true;

						for (auto i = bPieces.begin(); i != bPieces.end(); i++)
							this->possibleMoves(i->square, i->sign);

						if (getCheck() == false)
						{
							Board board = this->board;
							this->makeMove("e1 - c1", this->board, wPieces, bPieces);
							for (auto i = bPieces.begin(); i != bPieces.end(); i++)
								this->possibleMoves(i->square, i->sign);

							this->board = board;
							this->checkInspect = false;
							if (getCheck() == false)
								this->possibleMovesWhite.push_back("O-O-O");
						}
						else
						{
							this->checkInspect = false;
							setCheck(false);
						}
					}
				}
			}
		}
		else
		{
			if (this->board.squares[8][5] != 'k')
				return;
			else
			{
				if (this->board.squares[8][8] == 'r' && this->board.squares[8][7] == ' ' && this->board.squares[8][6] == ' ')
				{
					if (find(this->possibleMovesBlack.begin(), this->possibleMovesBlack.end(), "e8-f8") != this->possibleMovesBlack.end())
					{
						this->checkInspect = true;
						Board board = this->board;
						this->makeMove("e8 - g8", this->board, bPieces,wPieces);
						for (auto i = wPieces.begin(); i != wPieces.end(); i++)
							this->possibleMoves(i->square, i->sign);

						this->board = board;
						this->checkInspect = false;
						if (getCheck() == false)
							this->possibleMovesBlack.push_back("O-O");
					}
				}
				if (this->board.squares[8][1] == 'r' && this->board.squares[8][2] == ' ' &&
					this->board.squares[8][3] == ' ' && this->board.squares[8][4] == ' ')
				{
					if (find(this->possibleMovesBlack.begin(), this->possibleMovesBlack.end(), "e8-d8") != this->possibleMovesBlack.end())
					{
						this->checkInspect = true;
						Board board = this->board;
						this->makeMove("e8 - c8", this->board, bPieces, wPieces);
						for (auto i = wPieces.begin(); i != wPieces.end(); i++)
							this->possibleMoves(i->square, i->sign);

						this->board = board;
						this->checkInspect = false;
						if (getCheck() == false)
							this->possibleMovesBlack.push_back("O-O-O");
					}
				}
			}
		}
	}

private:
	bool check = false;
	bool addMove(int from[2], int x, int y)
	{
		if (isFree(from,x, y) || isOpponent(from, x, y)) {
			if (this->turn == 'b' && this->checkInspect == false || this->turn == 'w' && this->checkInspect == true)
			{
				string move = this->board.coordinates[from[1]] + to_string(from[0]) + "-" + this->board.coordinates[from[1] + static_cast<__int64>(y)] + to_string(from[0] + x);
				this->possibleMovesBlack.push_back(move);
				if (this->board.squares[from[0]+x][from[1]+y] == 'K' && this->turn == 'w' && this->board.squares[from[0]][from[1]] != 'p')
					setCheck(true);
			}
			else
			{
				string move = this->board.coordinates[from[1]] + to_string(from[0]) + "-" + this->board.coordinates[from[1] + static_cast<__int64>(y)] + to_string(from[0] + x);
				this->possibleMovesWhite.push_back(move);
				if (this->board.squares[from[0]+x][from[1]+y] == 'k' && this->turn == 'b' && this->board.squares[from[0]][from[1]] != 'P')
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
void play()
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
				a.areLegal(a.board,a.possibleMovesWhite,a.whitePieces,a.blackPieces);
				a.isCastlingPossible(a.whitePieces,a.blackPieces);
				if (a.possibleMovesWhite.empty())
				{
					cout << "STALEMATE!!!" << endl;
					break;
				}

				cin >> b;
				while (find(a.possibleMovesWhite.begin(), a.possibleMovesWhite.end(), b) == a.possibleMovesWhite.end())
				{
					cout << "nieprawidlowy ruch. Sprobuj ponownie" << endl;
					cin >> b;
				}
				a.makeMove(b,a.board,a.whitePieces,a.blackPieces);
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
				a.areLegal(a.board, a.possibleMovesBlack, a.blackPieces, a.whitePieces);
				a.isCastlingPossible(a.whitePieces, a.blackPieces);
				if (a.possibleMovesBlack.empty())
				{
					cout << "STALEMATE!!!" << endl;
					break;
				}

				cin >> b;
				while (find(a.possibleMovesBlack.begin(), a.possibleMovesBlack.end(), b) == a.possibleMovesBlack.end())
				{
					cout << "nieprawidlowy ruch. Sprobuj ponownie" << endl;
					cin >> b;
				}
				a.makeMove(b, a.board, a.blackPieces, a.whitePieces);
			}
		}
		a.flipTurn();
	}
}
