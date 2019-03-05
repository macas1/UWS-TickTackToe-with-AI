#include <time.h>
#include <iostream>
#include <string>
#include <algorithm>
#include "MKDriver.h"
#include "board.h"

using namespace std;

void MKDriver::testWinningConditions(){
    const int MAXBOARDSIZE = 20;

    char symbols[2] = {'X', 'O'};
    int boardState, m, k, i;
    string ynCheck;
    srand(time(NULL));
    board *testBoard;

    while(true){     //Untill the user stops the processing
        boardState = 0;
        m = rand() % (MAXBOARDSIZE  - 2 + 1) + 2; //m = Rand between MAXBOARDSIZE and 2
        k = rand() % (m  - 2 + 1) + 2;            //m = Rand between m  and 2
        testBoard = new board(m,k);
        testBoard->clear();

        //Untill the board retruns a game over condition, make random moves
        for(i = 0; boardState==0; i++){
            testBoard->makeMove(testBoard->generateRandomMove(symbols[i%2]));
            if(testBoard->hasWon(symbols[i%2]))
                boardState = 1;
            else if(testBoard->isFull())
                boardState = 2;
        }

        //When a game over condition occours, display the board and the condition.
        testBoard->display();
        cout << "M: " << m << "\nK: " << k << endl;
        if(boardState==1) cout << "In the above game " << symbols[(i+1)%2] << " won." << endl;
        if(boardState==2) cout << "The above game is a draw." << endl;
        delete testBoard;

        //Ask to test another
        cout << "Test another (y/n)? ";
        cin >> ynCheck;
        transform(ynCheck.begin(), ynCheck.end(),ynCheck.begin(), ::toupper); //capitilize
        if(ynCheck!="Y" && ynCheck != "YES")
            break;
    }
}
