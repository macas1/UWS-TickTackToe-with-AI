#include "Player.h"
#include "Board.h"
#include "MKGame.h"
#include "MoveData.h"

using namespace std;

class playerComputerRand: public player{
public:
    //Contructors
    playerComputerRand();

    //Functions
    moveData getMove(board b);
};
