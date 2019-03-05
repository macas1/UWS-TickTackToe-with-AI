#ifndef BOARD_H
#define BOARD_H

#include <string>

#include "MoveData.h"

using namespace std;


class board{
private:
    int size;
    int winCond;
    char** boardCells;

public:
    //Constructor
    board();
    board(int size, int winCond);

    //Copy Constructor
    board(const board &obj);

    //Deconstructor
    ~board();

    //Getters
    int getSize() const;
    int getWinCond() const;

    //Functions
    void clear();
    void display() const;
    void makeMove(int x, int y, char symbol);
    void makeMove(moveData m);
    bool cellIsFree(int x, int y) const;
    bool cellIsFree(moveData m) const;
    bool isFull() const;
    bool hasWon(char playerSymbol) const;
    int  howManyFreeCells() const;
    moveData generateRandomMove(char playerSymbol) const;
};

#endif //BOARD_H
