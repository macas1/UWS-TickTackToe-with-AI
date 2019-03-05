#ifndef PLAYER_HU
#define PLAYER_HU

#include "Player.h"
#include "Board.h"
#include "MKGame.h"

using namespace std;

class playerHuman: public player{
public:
    //Constructors
    playerHuman();
    playerHuman(char playerSymbol);
    moveData getMove(board b);
};

#endif
