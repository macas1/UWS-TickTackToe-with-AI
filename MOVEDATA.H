#ifndef MOVEDATA_H
#define MOVEDATA_H

#include <string>

using namespace std;

struct moveData{
    int x, y;
    double score;
    char symbol;

    //Constructors
    moveData(){
        x = 0;
        y = 0;
        score = 0;
    }
    moveData(int x, int y, char playerSymbol){
        this->x = x;
        this->y = y;
        symbol  = playerSymbol;
    }
    moveData(int x, int y, double score){
        this->x = x;
        this->y = y;
        this->score = score;
    }
    moveData(int x, int y, double score, char playerSymbol){
        this->x = x;
        this->y = y;
        this->score = score;
        symbol = playerSymbol;
    }
};

#endif
