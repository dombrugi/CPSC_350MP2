#include "Level.h"
#include "FileProcessor.h"
#include "Mario.h"

using namespace std;

Level::Level(){
}

Level::~Level(){
    //garbage collection time
    //delete[] levelArray;
}


char** Level::populate(int gridSize, int coin, int nothing, int goomba, int koopa, int mushroom) { //populate the 2D Level array with characters
    levelArray = new char*[gridSize];
    for(int i = 0; i < gridSize; i++) {
        levelArray[i] = new char[gridSize]; // Dynamic allocation
    }

    //create ranges for the probability of placing characters in the array
    int tempNothing = coin + nothing;
    int tempGoomba = tempNothing + goomba;
    int tempKoopa = tempGoomba + koopa;
    int tempShroom = tempKoopa + mushroom;

    for (int i = 0; i < gridSize; i++) { // Creates levels (2D arrays)
        for (int j = 0; j < gridSize; j++) {
            int randChance = rand() % 100 + 1;
            if (coin >= randChance) {
                levelArray[i][j] = 'c';
            } 
            else if (tempNothing >= randChance) {
                levelArray[i][j] = 'x';
            } 
            else if (tempGoomba >= randChance) {
                levelArray[i][j] = 'g';
            } 
            else if (tempKoopa >= randChance) {
                levelArray[i][j] = 'k';
            } 
            else if (tempShroom >= randChance) {
                levelArray[i][j] = 'm';
            } 
            else {
                levelArray[i][j] = 'x';
            }
        }
    }
    return levelArray;
}

char*** Level::world(int levels, int gridSize, int coin, int nothing, int goomba, int koopa, int mushroom) { //generate a 3D array that represents the World for the game
    srand(time(NULL));
    newWorld = new char**[levels];
    for (int i = 0; i < levels; i++) {
        newWorld[i] = new char*[levels];
        for (int j = 0; j < gridSize; j++) {
            newWorld[i][j] = new char[gridSize];
            for(int k = 0; k < gridSize; k++){
                newWorld[i][j][k] = ' ';
            }
        }
    }

    for (int i = 0; i < levels; i++) {
        newWorld[i] = populate(gridSize, coin, nothing, goomba, koopa, mushroom);
        if(i < levels - 1){
            placeItems(gridSize, i, newWorld);
        }
        else{
            placeItemsNoWarp(gridSize, i, newWorld);
        }
    }
    return newWorld;
}

int* Level::placeItems(int gridSize, int level, char*** newWorld){ //place Mario, the warp pipe, and the boss in the Level
    int* marioPosition = new int[1]; //initialize an array to store the indexes of Mario's position in the array
    srand((unsigned)time(0));

    //generate random indexes for Mario, warp, and boss
    int randMario1 = rand() % gridSize;
    int randMario2 = rand() % gridSize;
    int randWarp1 = rand() % gridSize;
    int randWarp2 = rand() % gridSize;
    int randBoss1 = rand() % gridSize;
    int randBoss2 = rand() % gridSize;

    while (true) { //make sure the warp, boss, and Mario don't get placed in the same index
        if (randMario1 != randWarp1 && randMario1 != randBoss1 && randWarp1 != randBoss1 && randMario2 != randWarp2 && randMario2 != randBoss2 && randWarp2 != randBoss2){
            newWorld[level][randMario1][randMario2] = 'H';
            newWorld[level][randWarp1][randWarp2] = 'w';
            newWorld[level][randBoss1][randBoss2] = 'b';

            marioPosition[0] = randMario1;
            marioPosition[1] = randMario2;

            break;
        }
        else {
            randMario1 = (rand()%gridSize);
            randMario2 = (rand()%gridSize);

            randWarp1 = (rand()%gridSize);
            randWarp2 = (rand()%gridSize);

            randBoss1 = (rand()%gridSize);
            randBoss2 = (rand()%gridSize);
        }
    }
    return marioPosition;
}

int* Level::placeItemsNoWarp(int gridSize, int level, char*** newWorld){ //place Mario, the warp pipe, and the boss in the Level
    int* marioPosition = new int[2]; //initialize an array to store the indexes of Mario's position in the array
    srand((unsigned)time(0));

    //generate random indexes for Mario, warp, and boss
    int randMario3 = rand()%gridSize;
    int randMario4 = rand()%gridSize;
    int randBoss3 = (rand()%gridSize);
    int randBoss4 = (rand()%gridSize);

    while (bool notSame = true) { //make sure the warp, boss, and Mario don't get placed in the same index
        if (randMario3 != randBoss3 && randMario4 != randBoss4){
            newWorld[level][randMario3][randMario4] = 'H';
            newWorld[level][randBoss3][randBoss4] = 'b';
            break;
        }
        else {
            randMario3 = (rand()%gridSize);
            randMario4 = (rand()%gridSize);
            randBoss3 = (rand()%gridSize);
            randBoss4 = (rand()%gridSize);
            notSame = true;
        }
    }
    
    //store Marios position in the integer array
    marioPosition[0] = randMario3;
    marioPosition[1] = randMario4;
    return marioPosition;
}

string Level::toString(int levels, int gridSize){ //create a string representation of the world to be used in main
    string s = "";
    for (int i = 0; i < levels; i++) {
        for (int j = 0; j < gridSize; j++) {
            for(int k = 0; k < gridSize; k++){
                s += newWorld[i][j][k];
            }
            s+= "\n";
        }
        s += "\n";
        s += "\n";
    }
    return s;
}

string Level::currToString(int level, int gridSize){ //create a string representation of the current level to be used in string
    string s = "";
    for (int j = 0; j < gridSize; j++) {
        for(int k = 0; k < gridSize; k++){
            s += newWorld[level][j][k];
        }
        s += "\n";
    }
    return s;
}