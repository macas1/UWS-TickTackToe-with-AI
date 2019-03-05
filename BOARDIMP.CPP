#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>

#include "Board.h"
#include "MoveData.h"

using namespace std;

//Constuctors
board::board(){}

board::board(int size, int winCond){
    //Set passed in vars
    this->winCond = winCond;
    this->size    = size;

    //Create the board with the set size
    boardCells = new char*[size];
    for(int i=0; i<size; i++)
        boardCells[i] = new char[size];

    clear();
}

//Copy constructor
board::board(const board &obj) {
    size = obj.size;
    winCond = obj.winCond;

    //Create new board
    boardCells = new char*[size];
        for(int i=0; i<size; i++)
            boardCells[i] = new char[size];

    //Copy values from previous board
    for(int x=0; x<size; x++)
        for(int y=0; y<size; y++)
            boardCells[x][y] = obj.boardCells[x][y];

}

//Deconsctructor
board::~board(){
    for (int i = 0; i < size; i++)
		delete[] boardCells[i];

	delete[] boardCells;
}

//Getters
int board::getSize() const{ //Gets board size as constant
    return size;
}

int board::getWinCond() const{ //Gets win condition as constant
    return winCond;
}

//Functions
void board::clear(){ //Make every character in the board a space
     for(int x=0; x<size; x++)
        for(int y=0; y<size; y++)
            boardCells[x][y] = ' ';
}

void board::display() const { //Displays the board in the console
    //Header
    cout << "\n-------------------------------------------\n   " << 1; //Separator
    for(int x=1; x<size; x++){ //Header values
        cout << "  ";
        if(x<10) cout << " ";
        cout << x+1;
    }
    cout << endl;

    //Rows
    for (int x=0; x<size; x++){
        //Row line 1/2
        cout << x+1 << " ";
        if(x<9) cout << " ";
        for(int y=0; y<size; y++){
            cout << boardCells[x][y];
            if(y<size-1)
                cout << "---";
        }

        //Row line 2/2, skip last
        if(x<size-1){
            cout << "\n";
            for(int y=0; y<size; y++)
                cout << "   |";
        }
        cout << "\n";
    }
    cout << endl;
}

bool board::isFull() const { //Check if the board has any non-space characters
    for(int x=0; x<size; x++)
        for(int y=0; y<size; y++)
            if(boardCells[x][y] == ' ')
                return false;
    return true;
}

bool board::cellIsFree(int x, int y) const { //Checks if the given cell is a space
    if(boardCells[x][y] == ' ')
        return true;
    return false;
}

bool board::cellIsFree(moveData m) const { //Checks if the cell contained in a moveData is a space
    int x = m.x, y=m.y;
    return cellIsFree(x, y);
}

int board::howManyFreeCells() const { //Counts the amount of free cells
    int free = 0;
    for(int x=0; x<size; x++)
        for(int y=0; y<size; y++)
            if(cellIsFree(x, y))
                free++;
    return free;
}

void board::makeMove(int x, int y, char symbol){ //Changes a cell in the board
    boardCells[x][y] = symbol;
}

void board::makeMove(moveData m){ //Changes a cell in the board from the args contained in a moveData
    boardCells[m.x][m.y] = m.symbol;
}

bool board::hasWon(char playerSymbol) const { //Checks is the given symbol has won
    bool won[4];
    for(int x=0; x<size; x++)
        for(int y=0; y<size; y++){ //for every cell
            if(boardCells[x][y] != playerSymbol) continue; //If the first cell does not contain the symbol, ignore this cell

            for(int i=0; i<4; i++)
                won[i] = true;

            for(int i=1; i<winCond; i++){
                if(won[0] && (y<winCond-1                   || boardCells[x][y-i]   != playerSymbol)) won[0] = false; //Check UP
                if(won[1] && (x<winCond-1 || y<winCond-1    || boardCells[x-i][y-i] != playerSymbol)) won[1] = false; //Check UP/LEFT
                if(won[2] && (x<winCond-1                   || boardCells[x-i][y]   != playerSymbol)) won[2] = false; //Check LEFT
                if(won[3] && (x<winCond-1 || y>size-winCond || boardCells[x-i][y+i] != playerSymbol)) won[3] = false; //Check LEFT/DOWN
                if(!won[0] && !won[1] && !won[2] && !won[3]) break;
            }
            if(won[0] || won[1] || won[2] || won[3]) return true; //If a complete wonning side was found return true
        }
    return false; //If no wonning sides were found then return false
}

moveData board::generateRandomMove(char playerSymbol) const {
    //Count empty cells
    int freeSpots, step, currentStep = -1;
    freeSpots = howManyFreeCells();

    //Get a random empty cell value
    srand(time(NULL)); //Initiate rand with the time as a seed
    step = (rand() % freeSpots); //get x and y as random numbers between size-1 and 0

    //Get random empty cell position (the position in the board ignoreing non-empty cells)
    for(int x=0; x<size; x++)
        for(int y=0; y<size; y++){
            if(cellIsFree(x,y)) currentStep++;
            if(currentStep>=step)
                return moveData(x, y, playerSymbol);
        }

    throw std::runtime_error("Error: board::generateRandomMove did not find a free position.");
}
