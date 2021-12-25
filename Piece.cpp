#include <iostream>
#include <vector>

using namespace std;

class Piece{
public:
	int square[2];
	char sign;
	virtual string addMoves()
	{
		return "e2-e5";
	}

};
class Pawn: public Piece {
public:
	string addMoves()
	{
		return "e2-e6";
	}
};


