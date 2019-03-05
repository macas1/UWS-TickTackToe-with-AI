#include "Player.h"
#include "Board.h"
#include "MKGame.h"
#include "MoveData.h"

using namespace std;

class playerComputerMinimax: public player{
private:
    //Private data
    const int  MAXRECURSION  = 1000000;  //1 million //The search tree will stop going deeper when it calculates that it may have done this many branches
    const bool SMARTOVERFAST = false;    //Will go deep enough to be somewhat smart when givin a board size it can't reall handle

    //Private functions;
    void getScores(int (&winData)[3], board b, char playerSymbol, int depth);
public:
    //Contructors
    playerComputerMinimax();

    //Functions
    moveData getMove(board b);
};
