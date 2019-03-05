#include <stdlib.h>
#include <time.h>
#include <ctime>
#include <iostream>
#include <math.h>

#include "PlayerComputerRand.h"
#include "MKGame.h"
#include "BOARD.H"

using namespace std;

//Contructors
playerComputerRand::playerComputerRand(){ //Default constructor
    this->playerSymbol = 'O';
}


moveData playerComputerRand::getMove(board b){ //Generate random empty board location
    return b.generateRandomMove(playerSymbol);
}
