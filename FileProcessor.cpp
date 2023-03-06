#include <fstream>
#include <ctime>
#include "FileProcessor.h"

using namespace std;

FileProcessor::FileProcessor(){
}

FileProcessor::FileProcessor(string inputFile){ //takes input from a file and assigns their values to variables
    int line;
    ifstream file(inputFile);
    file >> L;
    file >> N;
    file >> V;
    file >> coinProb;
    file >> nothingProb;
    file >> goombaProb;
    file >> koopaProb;
    file >> shroomProb;
}

FileProcessor::~FileProcessor(){
    //garbage collection time
    //delete [] levelArray;
}

//accessors
int FileProcessor::getL(){
    return L;
}

int FileProcessor::getN(){
    return N;
}

int FileProcessor::getV(){
    return V;
}

int FileProcessor::getCoinProb(){
    return coinProb;
}

int FileProcessor::getNothingProb(){
    return nothingProb;
}

int FileProcessor::getGoombaProb(){
    return goombaProb;
}

int FileProcessor::getKoopaProb(){
    return koopaProb;
}

int FileProcessor::getShroomProb(){
    return shroomProb;
}
