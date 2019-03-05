#include <string>
#include <iostream>
#include <algorithm>
#include "MKGame.h"
#include "PLAYER.H"
#include "playerHuman.h"
#include "playerComputerRand.h"
#include "playerComputerMinimax.h"
#include "playerComputerMonteCarlo.h"
#include "moveData.h"
#include "MKDriver.h"

using namespace std;

int MKGame::inInt(){ //Get a string input (cin) and return an integer if it's available. Return an error otherwise
    string input;
    cin >> input;
    return stoi(input);
}

void MKGame::play(){
    //INITIATE
    cout << "Thank you for playing this m,k game built by Bradley McInerney 2018." << endl; //Inroduction

    //Declarations
    string player2TName, ynCheck;
    int boardM, boardK, turn, player2Type;
    moveData currentMove;

    //Get settings
    while(true){ //While the game is being played

        //Get boardM or go into testing mode
        while(true){
            try{
                cout << "\nWhat is the size of the board (2-20)? (Or type -1 to open the win condition tester) ";
                boardM = inInt();
                if(boardM==-1){
                    MKDriver tester;
                    tester.testWinningConditions();
                    return;
                }
                if(boardM<2 || boardM>20){
                    cout << "ERROR: The value must be between 2 and 20, please enter again." << endl;
                    continue;
                }
            }catch(std::invalid_argument){ //Catch when not an integer input
                cout << "ERROR: The value must me an integer (whole number), please enter again." << endl;
                continue;
            }
            break;
        }

        //Get boardK
        if(boardM==2){
            boardK = 2;
        }else{
            while(true){
                try{
                    cout << "\nWhat is the amount of symbols in a row required to win (2-" << boardM << ")? ";
                    boardK = inInt();
                    if(boardK<2 || boardK>boardM){
                        cout << "ERROR: The value must be between 2 and " << boardM << ", please enter again." << endl;
                        continue;
                    }
                }catch(std::invalid_argument){ //Catch when not an integer input
                    cout << "ERROR: The value must me an integer (whole number), please enter again." << endl;
                    continue;
                }
                break;
            }
        }

        //Get player2
        while(true){
            cout << "\nWho will be player two?" //Ask for player 2 type
                 << "\n1) Human (Play with a friend)"
                 << "\n2) Computer Random (Dumb, Fast)"
                 << "\n3) Computer Minimax (Smart with small boards)"
                 << "\n4) Computer MonteCarlo (Better for larger boards)" << endl;
            cin >> player2Type;

            if(player2Type==1){ //Set it as a variable we can also output to the user(s) in the confirm settings section
                player2TName = "Human";
                break;
            }else if(player2Type==2){
                player2TName = "Computer Random";
                break;
            }else if(player2Type==3){
                player2TName = "Computer Minimax";
                break;
            }else if(player2Type==4){
                player2TName = "Computer MonteCarlo";
                break;
            }else
                cout << "ERROR: The only valid inputs are 1, 2 or 3, please enter again." << endl;

            //Clear the cin buffer
            cin.clear();
            fflush(stdin);
        }

        //Confirm settings.
        cout << "\nYou're settings are:"
             << "\nBoard size:  " << boardM
             << "\nSize to win: " << boardK
             << "\nOpponent:    " << player2TName
             << "\nAre these settings correct (y/n)? ";
        cin >> ynCheck;
        transform(ynCheck.begin(), ynCheck.end(),ynCheck.begin(), ::toupper); //capitilize
        if(ynCheck!="Y" && ynCheck != "YES")
            continue;

        //Build objects
        board gameBoard = board(boardM, boardK);
        players[0] = new playerHuman();
        if(player2Type==1) players[1] = new playerHuman('O');
        if(player2Type==2) players[1] = new playerComputerRand();
        if(player2Type==3) players[1] = new playerComputerMinimax();
        if(player2Type==4) players[1] = new playerComputerMonteCarlo();

        //Run game
        turn = 0; //redeclare turn each new game is played
        while(true){
            gameBoard.display(); //Display board

            //get player's move
            while(true){
                currentMove = players[turn%2]->getMove(gameBoard);
                if(gameBoard.cellIsFree(currentMove))
                    break;
                else
                    cout << "That cell is already taken, please enter again." << endl;
            }

            //Make move on board
            gameBoard.makeMove(currentMove);
            turn++;

            //Check for game over
            if(gameBoard.hasWon(currentMove.symbol)){ //Game over via win
                gameBoard.display();
                cout << "\nPlayer " << currentMove.symbol << " won!" << endl;
                break;
            }
            if(gameBoard.isFull()){ //Game over via draw
                gameBoard.display();
                cout << "\nThe game is a draw." << endl;
                break;
            }
        }

        //Remove players
        delete[] players;

        //Ask if they want to play again
        cout << "Do you want to play again (y/n)? ";
        cin >> ynCheck;
        transform(ynCheck.begin(), ynCheck.end(),ynCheck.begin(), ::toupper); //to upper case
        if(ynCheck=="Y" || ynCheck == "YES")
            continue;
        break;
    }
}


