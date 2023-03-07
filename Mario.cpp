#include "Mario.h"
#include "FileProcessor.h"

using namespace std;

Mario::Mario(){
    mPL = 0;
    mCoins = 0;
    mLives = 0;
    mKills = 0;
    mMove = "";
    mAction = "";
}

Mario::Mario(int V){
    mPL = 0;
    mCoins = 0;
    mKills = 0;
    mLives = V;
    mMove = "";
    mAction = "";
}

Mario::~Mario(){
    //garbage collection time
}

bool Mario::isAlive(){ //check if Mario is alice
    if (getLives() > 0){
        return true;
    }
    else {
        return false;
    }
}

void Mario::kill(){ //increment kills when Mario defeats an enemy, grant a life when he reaches 7 kills without a death
    mKills++;
    if (mKills == 7){
        gainLife();
        mKills = 0;
    }
}

void Mario::gainLevel(){
    while (mPL <= 2){
        mPL++;
    }
}

void Mario::loseLevel(){
    mPL--;
    if (mPL == 0){
        loseLife();
    }
}

void Mario::gainLife(){
    mLives++;
}

void Mario::loseLife(){
    mLives--;
    mKills = 0;
}

void Mario::gainCoin(){
    mCoins++;
    if (mCoins == 20){
        gainLife();
        mCoins = 0;
    }
}

bool Mario::fightKoopa(Mario &m1){ //simulate a fight with a koopa according to the rules from the assignment
    mPL = m1.getPL();
    mLives = m1.getLives();
    mKills = m1.getKills();
    bool enemyStatus = false;
    int random = rand() % 99 + 1;
        if(random <= 65){
            ++mKills;
            m1.setKills(mKills);
            if(mKills == 7){
                ++mLives;
                m1.setLives(mLives);
            }
            return true;
        }else{
            if(mPL == 0){
                if(1 < mLives){
                    --mLives;
                    m1.setLives(mLives);
                    mKills = 0;
                    m1.setKills(mKills);
                }else{
                    m1.setLives(0);
                }
            }else{
                --mPL;
                m1.setPL(mPL);
            }
        }
    return false;
}

bool Mario::fightGoomba(Mario &m1){ //simulate a fight with a goomba according to the rules from the assignment
    mPL = m1.getPL();
    mLives = m1.getLives();
    mKills = m1.getKills();
    bool enemyStatus = false;
        int random = rand() % 99 + 1;
        if(random <= 80){
            ++mKills;
            m1.setKills(mKills);
            if(mKills == 7){
                ++mLives;
                m1.setLives(mLives);
            }
            enemyStatus = true;
            return true;
        }else{
            if(mPL == 0){
                if(1 < mLives){
                    --mLives;
                    m1.setLives(mLives);
                    mKills = 0;
                    m1.setKills(mKills);
                }else{
                    m1.setLives(0);
                }
            }else{
                --mPL;
                m1.setPL(mPL);
            }
        }
    return false;
}

bool Mario::fightBoss(Mario &m1, bool levelStatus){ //simulate a fight with the level boss according to the rules from the assignment, end the level if Mario wins
    mPL = m1.getPL();
    mLives = m1.getLives();
    mKills = m1.getKills();

    bool exit = false;
    bool ret = false;

    while(exit == false){
        int random = rand() % 2;
        switch (random) {
            case 0:
                exit = true;
                ret = true;
                ++mKills;
                m1.setKills(mKills);
                if(mKills == 7){
                    ++mLives;
                    mKills = 0;
                    m1.setKills(mKills);
                }
                break;
            case 1: 
                if(mPL <= 1){
                    if(mLives > 1){
                        --mLives;
                        m1.setLives(mLives);
                        mKills = 0;
                        m1.setKills(mKills);
                    }else{
                        exit = true;
                        ret = false;
                        m1.setLives(0);
                    }
                }else{
                    mPL = mPL - 2;
                    m1.setPL(mPL);
                }
                break;
        }
    }
return ret;
}


int Mario::move(Mario &m1, int* marioPosition, int gridSize, int currentLevel, int mPL, int mLives, int mKills, bool levelStatus, bool livesLeft, char*** newWorld, bool enemyStatus){
    int randMove = rand() % 4;
    int* nextMove = new int[2];
    bool enStatus = false;

    switch (randMove){ //randomly determine Mario's next move
        case 0:
            nextMove[0] = marioPosition[0]-1;
            nextMove[1] = marioPosition[1];
            if (nextMove[0] < 0){ //account for torus
                nextMove[0] = gridSize - 1; 
            }
            mMove = "UP";
            break;
        case 1:
            nextMove[0] = marioPosition[0]+1;
            nextMove[1] = marioPosition[1];
            if (nextMove[0] > gridSize - 1){ //account for torus
                nextMove[0] = 0;
            }
            mMove = "Down";
            break;
        case 2:
            nextMove[0] = marioPosition[0];
            nextMove[1] = marioPosition[1]+1;
            if (nextMove[1] > gridSize - 1){ //account for torus
                nextMove[1] = 0;
            }
            mMove = "Right";
            break;
        case 3:
            nextMove[0] = marioPosition[0];
            nextMove[1] = marioPosition[1]-1;
            if (nextMove[1] < 0){ //account for torus
                nextMove[1] = gridSize - 1;
            }
            mMove = "Left";
            break;
        default:
            break;
    }
    switch (newWorld[currentLevel][nextMove[0]][nextMove[1]]){ //run appropriate interactions based on the character Mario moves to
        case 'c':
            m1.gainCoin();
            enStatus = true;
            mAction = "Mario found a coin!";
            break;
        case 'g':
            enStatus = m1.fightGoomba(m1);
            mAction = "Mario fought a Goomba.";
            break;
        case 'k':
            enStatus = m1.fightKoopa(m1);
            mAction = "Mario fought a Koopa.";
            break;
        case 'm':
            m1.gainLevel();
            enStatus = true;
            mAction = "Mario picked up a mushroom!";
            break;
        case 'x':
            mAction =  "Mario found nothing at this index.";
            enStatus = true;
            break;
        case 'b':
            enStatus = m1.fightBoss(m1, levelStatus);
            if(enStatus == true && m1.getLives() > 0){
                return 3; //next level
            }
            break;
        case 'w':
            levelStatus = true;
            enStatus = true;
            mAction = "Mario took a warp pipe to the next level.";
            return 3; //next level
        default:
            break;
    }

    if (enStatus == true){
        newWorld[currentLevel][marioPosition[0]][marioPosition[1]] = 'x'; //put nothing in the square mario was in
        marioPosition[0] = nextMove[0];
        marioPosition[1] = nextMove[1];
        newWorld[currentLevel][nextMove[0]][nextMove[1]] = 'H'; //put mario in the square the thing he interacted with was in
        return 1; //successful move
    }
    if(m1.getLives() == 0){
        return 0; //death
    }
    return 2; //failed move
}

//accessors and mutators
int Mario::getPL(){
    return mPL;
}

void Mario::setPL(int PL){
    mPL = PL;
}

int Mario::getLives(){
    return mLives;
}

void Mario::setLives(int lives){
    mLives = lives;
}   

int Mario::getCoins(){
    return mCoins;
}

void Mario::setCoins(int coins){
    mCoins = coins;
}

int Mario::getKills(){
    return mKills;
}

void Mario::setKills(int kills){
    mKills = kills;
}

string Mario::getMove(){
    return mMove;
}

string Mario::getAction(){
    return mAction;
}