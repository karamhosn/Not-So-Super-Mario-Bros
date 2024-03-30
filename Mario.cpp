#include "Mario.h"

// default constructor
Mario::Mario(){
    notRunning = false;
    enemiesDefeated = 0;
    coins = 0;
    power = 0;
    lives = 3; //some default amount of lives
}

//constructor
Mario::Mario(int V){
    notRunning = false; //game starts
    enemiesDefeated = 0; //default enemies defeated
    coins = 0; //default coins
    power = 0; //default power level
    lives = V; //lives
}

//destructor
Mario::~Mario(){
    //nothing to destruct
}

//GoombaWin (80% win rate)
bool Mario::GoombaWin(){
    random_device rd;
    uniform_int_distribution<int> dist(1, 100);

    int rand = dist(rd);
                
    if (rand <= 80)
        return true;
    else {
        return false;
    }
}

//KoopaWin (65% win rate)
bool Mario::KoopaWin(){
    random_device rd;
    uniform_int_distribution<int> dist(1, 100);

    int rand = dist(rd);
                
    if (rand <= 65)
        return true;
    else {
        return false;
    }
}

//BossWin (50% win rate)
bool Mario::BossWin(){
    random_device rd;
    uniform_int_distribution<int> dist(1, 100);

    int rand = dist(rd);
                
    if (rand <= 50)
        return true;
    else {
        return false;
    }
}

//IsDead
bool Mario::IsDead(){
    if (lives == 0){
        return true;
    }
    else{
        return false;
    }
}

//EnemyDefeated
void Mario::EnemyDefeated(){
    enemiesDefeated += 1;
}

//CheckEnemies (checks if 7 enemies are defeated and adds life correspondingly)
void Mario::CheckEnemies(){
    if (enemiesDefeated == Mario::ENEMIES_FOR_LIFE) {
        lives += 1;
    }
    else{
        lives = lives;
    }
}


//AddCoin
int Mario::AddCoin(){
    coins += 1;
    return coins;
}

//CheckTwentyCoins
bool Mario::CheckTwentyCoins(){
    if (coins == Mario::COINS_FOR_LIFE) {
        lives += 1; //++lives
        coins = 0; //resets coined (because life was gained)
        enemiesDefeated = 0; //resets enemies defeated (because life was gained)
        return true;
    }
    else{
        coins = coins;
        return false;
    }
}

//PowerUp
void Mario::PowerUp(){
    if (power < 2) { //max Power level is 2
        power += 1;
    }
    else{
        power = power;
    }
}

//PowerDowlBool
bool Mario::PowerDownBool(){
    if (power == 0){ 
        lives -= 1; //loses life if power was equal to 0
        enemiesDefeated = 0; //enemies defeated resets
        return true; //returns true if life was lost (to implement in Goomba and Koopa gameplay loop)
    }
    else{
        power -= 1;
        return false;
    }
}

//PowerDown
void Mario::PowerDown(){
    if (power == 0){
        lives -= 1;
        enemiesDefeated = 0;
    }
    else{
        power -= 1;
    }
}

//GameEnd
void Mario::GameEnd(){
    notRunning = true;
}

//IsRunning
bool Mario::IsRunning(){
    return notRunning == false; //when mario is still running (has not died) return true
}

//GetCoins
int Mario::GetCoins() const{
    return coins;
}

//GetPower
int Mario::GetPower() const {
    return power;
}

//GetLives
int Mario::GetLives() const {
    return lives;
}