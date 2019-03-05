#include <iostream>
#include <string>

#include "MKGame.h"
#include "board.h"

using namespace std;

/*
This version seems to be working except for the recursion part of the MonteCarlo
Maybe it will be fixed once board is turned into a pointer
*/

int main()
{
    MKGame mainGame; //Declare a game
    mainGame.play(); //Play the game

    return 0;
}
