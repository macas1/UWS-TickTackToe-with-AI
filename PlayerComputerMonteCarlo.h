#include "Player.h"
#include "Board.h"
#include "MKGame.h"
#include "MoveData.h"

using namespace std;

class playerComputerMonteCarlo: public player{
private:
    //Private data
    const int MILLISECONDS_TO_RUN = 5000; // How many second max the AI turns will take
    const int MAX_PROGRESS_PRINTS = 5;

    //Private functions;
    void getScores(int (&winData)[3], const board &b, char playerSymbol, int &randomCount, bool timeSet);
public:
    //Contructors
    playerComputerMonteCarlo();

    //Functions
    moveData getMove(board b);
};
