#ifndef WORLD_H
#define WORLD_H

#include "Mario.h"

using namespace std;

//World class
class World{
    public:
        World(); //default constructor
        World(int lvl, int dim, int c, int x, int g, int kp, int m); //constructor (to use)
        ~World(); //destructor

        //core methods
        void MarioSim(Mario* mario); //run game (simulation)

        void nothing(Mario* mario); //to call when mario finds nothing
        void coin(Mario* mario); //to call when mario finds a coin
        void goomba(Mario* mario); //to call when mario finds a Goomba
        void koopa(Mario* mario); //to call when mario finds a Koopa
        void mushroom(Mario* mario); //to call when mario finds a magic mushroom
        void boss(Mario* mario); //to call when mario finds a boss
        void warp(); //to call when mario find a warp

        void NewLevel(); //generate random x, y coordinates for new level (once mario warps)
        void MovesOn(int x, int y); //implements mario's movement with torus (up 1, down 1, left 1, or right 1)
        char direction(); //generates random direction for MovesOn() (25% chance each way)
        void print(); //concatenates 3Darray to output file string (fout)
        void print(int lvl); //concatenates NxN level mario is currently on in gameplay loop to fout

        void loss(); //concatenates loss message to fout
        void win(); //concatenates win message to fout

        //auxilary
        string output() const; //returns string fout to save to output log
        

    private:
        char ***myArray; //3D character array (the world)
        char something; //feauture that mario is on
        unsigned int L; //levels
        unsigned int finalLvl; //final level
        unsigned int N; //dimensions
        unsigned int moves; //counts moves
        unsigned int marioX; //if a 3D array follows the form [z][x][y], this would keep track of the x-coordinate
                             //for the gameplay loop
        unsigned int marioY;//if a 3D array follows the form [z][x][y], this would keep track of the y-coordinate
                             //for the gameplay loop
        unsigned int lvl; //tracks current level for gameplay loop
        string fout; //the output string to log
};

#endif