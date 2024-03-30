#ifndef MARIO_H
#define MARIO_H

#include <iostream>
#include <random>
#include <string>
#include <fstream>
#include <cctype>

using namespace std;

//Mario class
class Mario{
    public:
        Mario(); //default constructor
        Mario(int V); //constructor (to use)
        ~Mario(); //destructor

        //core methods
        bool GoombaWin(); //simulates Goomba encounter and returns true for win
        bool KoopaWin(); //simulates Koopa encounter and returns true for win
        bool BossWin(); //simulates Koopa encounter and returns true for win

        void GameEnd(); //to be called when game has ended
        bool IsRunning(); //returns true when mario is still running (has not died)

        bool IsDead(); //checks if mario has 0 lives

        void EnemyDefeated(); //adds an enemy to enemies defeated in one life
        void CheckEnemies(); //checks if 7 enemies are defeated and adds a life correspondingly

        int AddCoin(); // adds coin to pouch
        bool CheckTwentyCoins(); //checks if 20 coins, adds life correspondingly, and returns true/false

        void PowerUp(); //powers up
        bool PowerDownBool(); //powers down, returns true if life is lost
        void PowerDown(); //just powers down

        //auxilary
        int GetCoins() const; //returns coins
        int GetPower() const; //returns power level
        int GetLives() const; //returns lives

        static const unsigned int COINS_FOR_LIFE = 20;
        static const unsigned int ENEMIES_FOR_LIFE = 7;

    private:
        int power; //power level
        int lives; //lives
        int coins; //coins
        int enemiesDefeated; //enemies defeated in a row (tracker)
    
        bool notRunning; //true if game has ended

};

#endif