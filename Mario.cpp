#include "Mario.h"
#include "FileProcessor.h"

using namespace std;

Mario::Mario(){
    mPL = 0;
    mCoins = 0;
    mLives = 0;
    mKills = 0;
}

Mario::Mario(int V){
    mPL = 0;
    mCoins = 0;
    mKills = 0;
    mLives = V;
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

void Mario::fightKoopa(Mario &m1){ //simulate a fight with a koopa according to the rules from the assignment
    mPL = m1.getPL();
    mLives = m1.getLives();
    mKills = m1.getKills();
    int random = rand() % 20;
    bool enemyStatus = false;
    while(enemyStatus == false){
        int random = rand() % 20;
        if(random <= 12){
            cout << "You defeated the Koopa!" << endl;
            ++mKills;
            m1.setKills(mKills);
            if(mKills == 7){
                cout << "Your mKills is " << mKills <<  "! You gain a life!" << endl;
                ++mLives;
                m1.setLives(mLives);
            }
            enemyStatus = true;
            break;
        }else{
            if(mPL == 0){
                if(1 < mLives){
                    --mLives;
                    m1.setLives(mLives);
                    cout << "You lost to the Koopa and your power level was at 0! You lose a life!" << endl;
                    mKills = 0;
                    m1.setKills(mKills);
                }else{
                    cout << "You lost, your power level was 1 or lower and your lives where at 1! You lose the game!" << endl;
                }
            }else{
                --mPL;
                m1.setPL(mPL);
                cout << "You lost to the Koopa! Your power level is " << mPL << endl;
            }
        }
    }
}

void Mario::fightGoomba(Mario &m1){ //simulate a fight with a goomba according to the rules from the assignment
    mPL = m1.getPL();
    mLives = m1.getLives();
    mKills = m1.getKills();
    bool enemyStatus = false;
    while(enemyStatus == false){
        int random = rand() % 5;
        if(random <= 3){
            cout << "You defeated the Goomba!" << endl;
            ++mKills;
            m1.setKills(mKills);
            if(mKills == 7){
                cout << "Your mKills is " << mKills <<  "! You gain a life!" << endl;
                ++mLives;
                m1.setLives(mLives);
            }
            enemyStatus = true;
            break;
        }else{
            if(mPL == 0){
                if(1 < mLives){
                    --mLives;
                    m1.setLives(mLives);
                    cout << "You lost to the Goomba and your power level was at 0! You lose a life!" << endl;
                    mKills = 0;
                    m1.setKills(mKills);
                }else{
                    cout << "You lost, your power level was 0 and your lives where at 1! You lose the game!" << endl;
                }
            }else{
                --mPL;
                m1.setPL(mPL);
                cout << "You lost to the Goomba! Your power level is " << mPL << endl;
            }
        }
    }
}

bool Mario::fightBoss(Mario &m1, bool levelStatus){ //simulate a fight with the level boss according to the rules from the assignment, end the level if Mario wins
    mPL = m1.getPL();
    mLives = m1.getLives();
    mKills = m1.getKills();
    while(levelStatus == false){
        int random = rand() % 2;
        switch (random) {
            case 0:
                levelStatus = true;
                cout << "You defeated the Boss!" << endl;
                ++mKills;
                m1.setKills(mKills);
                if(mKills == 7){
                    cout << "Your mKills is " << mKills <<  "! You gain a life!" << endl;
                    ++mLives;
                    mKills = 0;
                    m1.setKills(mKills);
                }
                break;
            case 1: 
                if(mPL <= 1){
                    if(1 < mLives){
                        --mLives;
                        m1.setLives(mLives);
                        cout << "You lost to the Boss and your power level was at 1 or 0! You lose a life! You have " << mLives << " live(s)." << endl;
                        mKills = 0;
                        m1.setKills(mKills);
                    }else{
                        cout << "You lost, your power level was 1 or lower and your lives where at 1! You lose the game!" << endl;
                        levelStatus = true;
                        m1.setLives(mLives);
                    }
                }else{
                    mPL = mPL - 2;
                    m1.setPL(mPL);
                    cout << "You lost to the Boss! You're power level is " << mPL << endl;
                }
                break;
        }
    }
levelStatus = false;
return levelStatus;
}


void Mario::move(Mario &m1, int* marioPosition, int gridSize, int currentLevel, int mPL, int mLives, int mKills, bool levelStatus, bool livesLeft, char*** newWorld, bool enemyStatus){
    srand((unsigned)time(0));
    int randMove = rand()%4;
    int* nextMove = new int[2];

    switch (randMove){ //randomly determine Mario's next move
        case 0:
            nextMove[0] = marioPosition[0]-1;
            nextMove[1] = marioPosition[1];
            if (nextMove[0] < 0){ //account for torus
                nextMove[0] = gridSize - 1; 
            }
            break;
        case 1:
            nextMove[0] = marioPosition[0]+1;
            nextMove[1] = marioPosition[1];
            if (nextMove[0] > gridSize - 1){ //account for torus
                nextMove[0] = 0;
            }
            break;
        case 2:
            nextMove[0] = marioPosition[0];
            nextMove[1] = marioPosition[1]+1;
            if (nextMove[1] > gridSize - 1){ //account for torus
                nextMove[1] = 0;
            }
            break;
        case 3:
            nextMove[0] = marioPosition[0];
            nextMove[1] = marioPosition[1]-1;
            if (nextMove[1] < 0){ //account for torus
                nextMove[1] = gridSize - 1;
            }
            break;
        default:
            break;
    }
    switch (newWorld[currentLevel][nextMove[0]][nextMove[1]]){ //run appropriate interactions based on the character Mario moves to
        case 'c':
            m1.gainCoin();
            enemyStatus = true;
            break;
        case 'g':
            m1.fightGoomba(m1);
            break;
        case 'k':
            m1.fightKoopa(m1);
            break;
        case 'm':
            m1.gainLevel();
            enemyStatus = true;
            break;
        case 'x':
            cout << "Mario found nothing at this index." << endl;
            break;
        case 'b':
            m1.fightBoss(m1, levelStatus);
            break;
        case 'w':
            levelStatus = true;
        default:
            break;
    }
    if (enemyStatus == true){
        newWorld[currentLevel][marioPosition[0]][marioPosition[1]] = 'x'; //put nothing in the square mario was in
        marioPosition[0] = nextMove[0];
        marioPosition[1] = nextMove[1];
        newWorld[currentLevel][nextMove[0]][nextMove[1]] = 'H'; //put mario in the square the thing he interacted with was in
    }
} 

string Mario::marioResult(int* marioPosition, int coins, int PL, int lives, int level, string marioMove, string move){ //creates a string version of Mario's attributes to be added to the output file
    string result;
    int marioRow = marioPosition[0];
    int marioColumn = marioPosition[1];
    result += "Level: " + to_string(level) + ".\n";
    result += "Mario is at [" + to_string(marioRow) + "][" + to_string(marioColumn) + "]" + ".\n";
    result += "Mario's power level is " + to_string(PL) + ".\n";
    result += marioMove + "\n";
    result += "Mario's lives are " + to_string(lives) + ".\n";
    result += "Mario's coins are " + to_string(coins) + ".\n";
    result += "Mario will move " + move + ".\n";
    cout << result; 
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