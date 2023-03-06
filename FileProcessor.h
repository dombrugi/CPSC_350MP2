#ifndef FILEPROCESSOR_H
#define FILEPROCESSOR_H

#include <iostream>
using namespace std;

class FileProcessor{
    public:
        FileProcessor(); //default constructor 
        FileProcessor(string fileName); //overloaded constructor
        ~FileProcessor(); //default destructor
        char** populate();
        char** levelArray;
        
        //accessors
        int getL();
        int getN();
        int getV();
        int getCoinProb();
        int getNothingProb();
        int getGoombaProb();
        int getKoopaProb();
        int getShroomProb();

    private:
        int L;
        int N;
        int V;
        int coinProb;
        int nothingProb;
        int goombaProb;
        int koopaProb;
        int shroomProb;

        
};


#endif