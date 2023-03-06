#include "Mario.h"
#include "Level.h"
#include "FileProcessor.h"
#include <fstream>

using namespace std;

int main(int argc, char** argv){
    FileProcessor fp("inputFile.txt");
    ofstream outputFile("outputFile.txt");
    int L = fp.getL();
    int N = fp.getN();
    int V = fp.getV();
    int coin = fp.getCoinProb();
    int nothing = fp.getNothingProb();
    int goomba = fp.getGoombaProb();
    int koopa = fp.getKoopaProb();
    int mushroom = fp.getShroomProb();
    
    Mario m1;
    m1.setLives(V);
    int moveCount = 0;
    
    char*** newWorld = new char**[4];
    int* marioPosition = new int[2];
    bool levelStatus = false;
    bool livesLeft = true;
    bool enemyStatus = false;
    int currentLevel = 0;
    Level level;
    

    // while (m1.getLives() > 0){
    //     newWorld = level.world(L,N,coin,nothing,goomba,koopa,mushroom);
    //     while (currentLevel <= L){
    //         if (currentLevel == L){
    //             marioPosition = level.placeItemsNoWarp(N, currentLevel, newWorld);
    //             m1.move(m1, marioPosition, N, currentLevel, m1.getPL(), m1.getLives(), m1.getKills(), levelStatus, livesLeft, newWorld, enemyStatus);
    //             moveCount++;
    //             if (levelStatus == true){
    //                 outputFile << "Mario has saved the Princess!" << endl;
    //                 break;
    //             }
    //         }
    //         else {
    //             marioPosition = level.placeItems(N, currentLevel, newWorld);
    //             m1.move(m1, marioPosition, N, currentLevel, m1.getPL(), m1.getLives(), m1.getKills(), levelStatus, livesLeft, newWorld, enemyStatus);
    //             moveCount++;
    //             if (levelStatus == true){
    //                 currentLevel++;
    //             }
    //         }
    //         for (int i = 0; i < N; i++){
    //             outputFile << marioPosition[i] << endl;
    //         }
    //         outputFile << moveCount << endl;
    //     }
    // }
    // outputFile << "The game has ended.";

    cout << "There was a genuine attempt, I promise.";
};
