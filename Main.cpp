#include "Mario.h"
#include "Level.h"
#include "FileProcessor.h"
#include <fstream>

using namespace std;

int main(int argc, char** argv){
    //prepare files
    FileProcessor fp("inputFile.txt");
    ofstream outputFile("outputFile.txt");

    //read in variables from file
    int L = fp.getL();
    int N = fp.getN();
    int V = fp.getV();
    int coin = fp.getCoinProb();
    int nothing = fp.getNothingProb();
    int goomba = fp.getGoombaProb();
    int koopa = fp.getKoopaProb();
    int mushroom = fp.getShroomProb();
    
    //initialized Mario and the World
    Mario m1(V);
    int moveCount = 0;
    char*** newWorld = new char**[4];
    int* marioPosition = new int[1];
    bool levelStatus = false;
    bool livesLeft = true;
    bool enemyStatus = false;
    int currentLevel = 0;
    Level level;

    newWorld = level.world(L,N,coin,nothing,goomba,koopa,mushroom);
    level.toString(currentLevel, N);

    int moveStat = 1;
    
    outputFile << level.toString(L, N);

    while (moveStat != 0 && m1.getLives() > 0){

        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                if(newWorld[currentLevel][i][j] == 'H'){
                    marioPosition[0] = i;
                    marioPosition[1] = j;
                }
            }
        }
        outputFile << "Current Level is " << currentLevel << "." << endl;
        outputFile << "Mario is currently at index " << marioPosition[0] << ", " << marioPosition[1] << "." << endl;
        outputFile << "Mario's current power level is " << m1.getPL() << "." << endl;
        moveStat = m1.move(m1, marioPosition, N, currentLevel, m1.getPL(), m1.getLives(), m1.getKills(), levelStatus, livesLeft, newWorld, enemyStatus);
        outputFile << m1.getAction();
        outputFile << "\n";
        outputFile << "Mario has " << m1.getLives() << " lives." << endl;
        outputFile << "Mario has " << m1.getCoins() << " coins." << endl;
        outputFile << "Mario will move " << m1.getMove() << endl;
        outputFile << "\n";
        outputFile << level.currToString(currentLevel,N);
        outputFile << "\n";
        outputFile << "\n";




        if(moveStat == 3){
            currentLevel++;
            moveStat = 1;
            if(currentLevel == L){
                break;
            }
            level.currToString(currentLevel, N);
        }

        level.currToString(currentLevel, N);
    }

    if(m1.getLives() == 0){
        outputFile << endl << "You lose!" << endl;
    }
    else{
        outputFile << endl << "Mario saved the princess!" << endl;
    }
};
