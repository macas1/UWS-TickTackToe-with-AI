#include <stdlib.h>
#include <time.h>
#include <ctime>
#include <iostream>
#include <math.h>

#include "playerComputerMonteCarlo.h"
#include "MKGame.h"
#include "BOARD.H"

using namespace std;

//Contructors
playerComputerMonteCarlo::playerComputerMonteCarlo(){ //Default constructor
    this->playerSymbol = 'O';
}

moveData playerComputerMonteCarlo::getMove(board b){
    //Check for data error
    if(b.isFull()) throw std::runtime_error("Error: minimax can't generate move when board is full.");

    //Declarations
    int stepsTaken=0, bestCellsUsed=0;
    int bSize = b.getSize(), freeCells = b.howManyFreeCells();
    bool firstTimeRun = true, printPrecentage;
    moveData cells[freeCells], bestCells[freeCells];
    int winData[3];
    double winRatio, highestScore;
    int randomEach = floor(double(MILLISECONDS_TO_RUN/freeCells)); //init as the milliseconds to run per cell, will turn into games to run per cell after first test

    //Output
    cout << "AI Thinking... (Will try to take less than " << float(MILLISECONDS_TO_RUN/1000.0) << " Seconds)";

    //Testoutput containing loop data
    if(TESTOUTPUTS) cout << "<TotalMilliseconds:" << MILLISECONDS_TO_RUN << " PerCell: " << randomEach << endl;

    //Begin recording time elapsed
    clock_t begin = clock();

    //Start finding scores for each move and store the highest scoring one
    for(int x=0; x<bSize; x++)
        for(int y=0; y<bSize; y++){
            //Only look at free cells
            if(!b.cellIsFree(x, y)) continue;

            //Change the board to the temp testing state
            b.makeMove(x, y, playerSymbol);

            //Get win/loss/draw counts
            winData[0]=0; winData[1]=0; winData[2]=0;

            getScores(winData, b, 'O', randomEach, firstTimeRun);

            // get winRatio as points where a win=1, loss=0, draw=0.5
            winRatio = winData[0];
            winRatio += winData[2]*0.5;

            //Get winRaio as point/games played
            winRatio = winRatio/(winData[0] + winData[1] + winData[2]);

            //Save as a move with the winRatio as a score
            cells[stepsTaken] = moveData(x, y, winRatio, 'O');

            //Change the high score if not set or there is a new high score
            if(firstTimeRun || cells[stepsTaken].score > highestScore){
                highestScore = cells[stepsTaken].score;
            }

            //Testoutput with specific move data
            if(TESTOUTPUTS) cout << "\n<x:" << x+1 << " Y:" << y+1 << " CScore:" << cells[stepsTaken].score << " HScore:" << highestScore << ">";

            if(firstTimeRun){
                firstTimeRun = false;
                if(TESTOUTPUTS) cout << "<TotalGames:" << randomEach*freeCells << " PerCell: " << randomEach << ">";
            }
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

void playerComputerMonteCarlo::getScores(int (&winData)[3], const board &b, char playerSymbol, int &randomCount, bool timeSet){
    //Declarations
    bool aiTurn = true;
    moveData xy;
    int counter = 0;
    clock_t begin;
    if (timeSet) begin = clock();

    //For the amount of random values we need
    while(true){
        //Copy the current board
        board bTemp = b;

        //Play a full game
        while(!(bTemp.isFull() || bTemp.hasWon('X') || bTemp.hasWon('O'))){
            if(aiTurn) xy = bTemp.generateRandomMove('O'); //Generate move
            else       xy = bTemp.generateRandomMove('X');
            bTemp.makeMove(xy); //Save move
            aiTurn = !aiTurn;   //Rotate turn
        }

        //Return value
        if(bTemp.hasWon('O')){
            winData[0] += 1;
        }
        else if(bTemp.hasWon('X')){
            winData[1] += 1;
        }
        //Pass score 0 for tie or too deep in recursion loops to continue
        else if(bTemp.isFull()){
            winData[2] += 1;
        }

        //Increment counter and check for break condition
        counter++;

        if(timeSet){
            clock_t current = clock();
            if(current - begin >= randomCount){
                randomCount = counter;
                break;
            }
        }else{
            if(counter >= randomCount)
                break;
        }
    }
}
