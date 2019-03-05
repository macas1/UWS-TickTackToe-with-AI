#ifndef MKGAME_H
#define MKGAME_H

#include "player.h"
#include "board.h"
#include <string>

using namespace std;

class MKGame{
private:
    board gameBoard;
    player *players[2];
public:
    void play();
    static int inInt();
};

#endif //MKGAME_H
