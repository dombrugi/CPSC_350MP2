#ifndef MARIO_H
#define MARIO_H

#include <iostream>
using namespace std;

class Mario{
    public:
        Mario(); //default constructor
        Mario(int V); //overloaded constructor
        ~Mario(); //destructor
        bool isAlive();
        void move();
        void kill();
        void gainLevel();
        void loseLevel();
        void gainLife();
        void loseLife();
        void gainCoin();
        bool fightKoopa(Mario &m1);
        bool fightGoomba(Mario &m1);
        bool fightBoss(Mario &m1, bool levelStatus);
        int move(Mario &m1, int* marioPosition, int gridSize, int currentLevel, int mPL, int mLives, int mKills, bool levelStatus, bool livesLeft, char*** newWorld, bool enemyStatus);


        //accessors and mutators
        int getPL();
        void setPL(int PL);
        int getLives();
        void setLives(int lives);
        int getCoins();
        void setCoins(int coins);
        int getKills();
        void setKills(int lives);
        bool getWon();
        void setWon(bool won);
        string getMove();
        string getAction();


    private:
        int mPL;
        int mLives;
        int mCoins; 
        int mKills;
        string mMove;
        string mAction;
        bool mWon;
};


#endif