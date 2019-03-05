#include "Player.h"

using namespace std;

//Constructors
player::player(){
    playerSymbol = 'X';
}

player::player(char playerSymbol){ //Cunstructor with custom symbol
    this->playerSymbol = playerSymbol;
}

//Getters
char player::getPlayerSymbol() const{ //Get the player symbol
    return playerSymbol;
}
