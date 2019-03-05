#include <stdlib.h>
#include <time.h>
#include <ctime>
#include <iostream>
#include <math.h>

#include "PlayerComputerMinimax.h"
#include "MKGame.h"
#include "BOARD.H"

using namespace std;

//Contructors
playerComputerMinimax::playerComputerMinimax(){ //Default constructor
    this->playerSymbol = 'O';
}

moveData playerComputerMinimax::getMove(board b){
    //Check for data error
    if(b.isFull()) throw std::runtime_error("Error: minimax can't generate move when board is full.");

    //Declarations
    int stepsTaken=0, maxRDepth=-1, currentRecursions=1, bestCellsUsed=0;
    int bSize = b.getSize(), currentValue = b.howManyFreeCells();
    bool highScoreSet = false;
    moveData cells[currentValue], bestCells[currentValue];
    int winData[3];
    double winRatio, highestScore;

    //Find wanted maximum recursion depth
    while(currentRecursions <= MAXRECURSION && currentRecursions > 0 && currentValue > 0){ //under cap, no rollover, over possimple moves
        currentRecursions *= currentValue;
        currentValue--;
        maxRDepth++;
    }

    //Apply a minimum recursion depth so it's still intelegent at the cost of speed
    if(SMARTOVERFAST){
            int winCond = b.getWinCond();
            if(maxRDepth <= winCond){
                maxRDepth = winCond+1;
                currentRecursions = -1;
            }
    }

    //Testoutput containing recursion data
    if(TESTOUTPUTS){
            cout << "<ThinkingDepth:" << maxRDepth << " MaxRecusions:";
            if(currentRecursions > 0) cout << currentRecursions/(currentValue+1);
            else cout << "Exceeded";
            cout << ">";
    }

    //Begin recording time elapsed
    clock_t begin = clock();

    //Start finding scores for each move and store the highest scoring one
    for(int x=0; x<bSize; x++)
        for(int y=0; y<bSize; y++){
            //Only look at free cells
            if(!b.cellIsFree(x, y)) continue;

            //Progress message
            cout <<"\nAI thinking: " << round(stepsTaken/float(b.howManyFreeCells())*100) << "%";

            //Change the board to the temp testing state
            b.makeMove(x, y, playerSymbol);

            //Get win/loss/draw counts
            winData[0]=0; winData[1]=0; winData[2]=0;
            getScores(winData, b, 'O', maxRDepth);

            // get winRatio as points where a win=1, loss=0, draw=0.5
            winRatio = winData[0];
            winRatio += winData[2]*0.5;

            //Get winRaio as point/games played
            winRatio = winRatio/(winData[0] + winData[1] + winData[2]);

            //Save as a move with the winRatio as a score
            cells[stepsTaken] = moveData(x, y, winRatio, 'O');

            //Change the high score if not set or there is a new high score
            if(!highScoreSet || cells[stepsTaken].score > highestScore){
                highestScore = cells[stepsTaken].score;
                highScoreSet = true;
            }

            //Testoutput with specific move data
            if(TESTOUTPUTS) cout << "  <x:" << x+1 << " Y:" << y+1 << " CScore:" << cells[stepsTaken].score << " HScore:" << highestScore << ">";

            //Increment steps
            stepsTaken++;

            //Change the board back to it's correct state
            b.makeMove(x, y, ' ');
        }

    //Get hightest scoreing moves
    for(int i=0; i<b.howManyFreeCells(); i++){
        //if(TESTOUTPUTS) cout << "\n~" << i << "_" << cells[i].x << "_" << cells[i].y << "_" << cells[i].score << "_" << highestScore;
        if(cells[i].score==highestScore){
            bestCells[bestCellsUsed] = cells[i];
            bestCellsUsed++;
        }
    }

    //Output final progress message and the time that tis AI's turn took.
    clock_t end = clock();
    cout<<"\nAI thinking: 100% (Seconds elapsed: " << double(end - begin) / CLOCKS_PER_SEC << ")";

    //Return a ranom best scoring cell
    srand(time(NULL));
    return bestCells[rand() % bestCellsUsed];
}

void playerComputerMinimax::getScores(int (&winData)[3], board b, char playerSymbol, int depth){

    //Check if someone has won and pass up that score
    if(b.hasWon('O')){
        winData[0] += 1;
        return;
    }
    else if(b.hasWon('X')){
        winData[1] += 1;
        return;
    }
    //Pass score 0 for tie or too deep in recursion loops to continue
    else if(b.isFull() || depth==0){
        winData[2] += 1;
        return;
    }

    //Declarations
    int bSize = b.getSize();

    //For each cell
    for(int x=0; x<bSize; x++)
        for(int y=0; y<bSize; y++){
            if(!b.cellIsFree(x, y)) continue; //Only look at free cells
            b.makeMove(x, y, playerSymbol);   //Change the board to a temporary testing state

            if(playerSymbol=='X') getScores(winData, b, 'O', depth-1); //Make a similar temp move for the next player
            else getScores(winData, b, 'X', depth-1);

            b.makeMove(x, y, ' '); //Change the board back to it's correct state
        }
}
