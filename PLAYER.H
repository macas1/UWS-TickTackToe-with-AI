#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "MoveData.h"
#include "Board.h"

using namespace std;

class player{
protected:
    const bool TESTOUTPUTS = false;;
    char playerSymbol;
public:
    //Constructors
    player();
    player(char playerSymbol);

    //Getters
    char getPlayerSymbol() const;

    //Function
    virtual moveData getMove(board b){ return moveData(); }  //=0
};

#endif //PLAYER_H
