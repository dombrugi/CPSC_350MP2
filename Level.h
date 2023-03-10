#ifndef LEVEL_H
#define LEVEL_H

#include <iostream>
#include "Mario.h"
using namespace std;

class Level{
    public:
        Level(); //default constructor
        Level(int N); //overloaded constructor
        ~Level(); //destructor
        char** populate(int gridSize, int coin, int nothing, int goomba, int koopa, int mushroom);
        char*** world(int levels, int gridSize, int coin, int nothing, int goomba, int koopa, int mushroom);
        int* placeItems(int gridSize, int level, char*** newWorld);
        int* placeItemsNoWarp(int gridSize, int level, char*** newWorld);
        string toString(int levels, int gridSize);
        string currToString(int level, int gridSize);
    private:
        char** levelArray;
        char*** newWorld;
};

#endif