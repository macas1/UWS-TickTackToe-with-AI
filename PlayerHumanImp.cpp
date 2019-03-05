#include <iostream>

#include "PlayerHuman.h"
#include "MoveData.H"
#include "MKGame.h"
using namespace std;

//Contructors
playerHuman::playerHuman(){ //Default constructor
    player::playerSymbol = 'X';
}

playerHuman::playerHuman(char playerSymbol){ //Consctructor with custom symbol
    player::playerSymbol = playerSymbol;
}


moveData playerHuman::getMove(board b){
    //Declarations
    int successes=0, boardSize=b.getSize();
    int coords[2];
    char text[2] = {'x', 'y'};

    //Loop twice to get values x AND y
    while(successes < 2){
        try{
            cout << "Player " << playerSymbol << ", what is your " << text[successes] << "-coordinate? "; //Ask for value
            coords[successes] = MKGame::inInt(); //Get value as int or otherwise error that will be caught
            if(coords[successes]<1 || coords[successes]>boardSize){ //If no error was thrown, also check that the value is in the bounds of the board
                cout << "ERROR: The coordinate must be between 1 and " << boardSize << ", please enter again." << endl;
                continue; //If out of bounds ask again
            }
        }catch(std::invalid_argument){ //If error caught ask again
            cout << "ERROR: The coordinate must me an integer (whole number), please enter again." << endl;
            continue;
        }
        successes++; //If valid coordinate, ask for the next one or end the while loop
    }
    return moveData(coords[0]-1, coords[1]-1, playerSymbol); //return a movedata with the coordinate relative the the array indexes
}
