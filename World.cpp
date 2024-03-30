#include "World.h"
#include "Mario.h"

//default constructor
World::World(){
    fout = ""; 
    something = ' ';
    L = 2; //some default levels
    finalLvl = L - 1; //final level
    N = 2; //dimensions
    lvl = 0; //current level
    marioX = 0; //current x-pos
    marioY = 0; //current y-pos
    moves = 0; //no moves yet

    //create 3D array
    myArray = new char**[L];
    for (int i = 0; i < L; i++) {
        myArray[i] = new char*[N];
        for (int j = 0; j < N; j++)
        {
            myArray[i][j] = new char[N];
        }
    }
}

//overloaded constructor
World::World(int lvl, int dim, int c, int x, int g, int kp, int m){

    L = lvl; //levels
    finalLvl = L - 1; //final level
    N = dim; //dimensions of each level

    //create 3D array
    myArray = new char**[L];
    for (int i = 0; i < L; i++) {
        myArray[i] = new char*[N];
        for (int j = 0; j < N; j++)
        {
            myArray[i][j] = new char[N];
        }
    }

    //initialize 3D array with features represented by characters based on 
    //% chance for each feature on the map (passed in parameter as c, x, g, etc.)
    random_device rd;
    uniform_int_distribution<int> dist(1,100);
    int rn;

    //iterate through 3D array
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                rn = dist(rd); //generates random num between 1-100

                //generates a feature in level based on probability given
                if (rn <= c){
                    myArray[i][j][k] = 'c';
                } 
                else if (rn <= (c + x)){
                    myArray[i][j][k] = 'x';
                }
                else if (rn <= (c + x + g)) {
                    myArray[i][j][k] = 'g';
                }
                else if (rn <= (c + x + g + kp)){
                    myArray[i][j][k] = 'k';
                }
                else if (rn <= (c + x + g + kp + m)){
                    myArray[i][j][k] = 'm';
                }
            }
        }
    }

    //generate boss at random for each level
    for (int i = 0; i < L; i++) {
        random_device rd;
        uniform_int_distribution<int> dist(0, (N - 1));

        myArray[i][dist(rd)][dist(rd)] = 'b';
    }

    //generate warp at random for all levels but last (N - 1)
    for (int i = 0; i < (L - 1); i++) {
        random_device rd;
        uniform_int_distribution<int> dist(0, (N - 1));

        myArray[i][dist(rd)][dist(rd)] = 'w';
    }
}

//destructor (garbage collect 3D array)
World::~World(){
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < N; j++)
        {
            delete[] myArray[i][j];
        }
        delete[] myArray[i];
    }
    delete[] myArray;
}

//prints world
void World::print(){
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                fout += myArray[i][j][k];     
            }
            fout += "\n";
        }
        for (int p = 0; p < (N+5); p++){
            fout += "=";
        }
        fout += "\n";
    }
}

//prints level
void World::print(int lvl){
    for (int p = 0; p < (N+5); p++){
            fout += "=";
    }
    fout += "\n";
    for (int j = 0; j < N; j++) {
        for (int k = 0; k < N; k++) {
            fout += myArray[lvl][j][k];     
        }
        fout += "\n";
    }
    for (int p = 0; p < (N+5); p++){
        fout += "=";
    }
    fout += "\n";
}

//MarioSim (gameplay siimulation)
void World::MarioSim(Mario* mario){

    NewLevel();

    //defines a character as some feature on the map
    something = myArray[lvl][marioX][marioY];

    //pretty output
    print();
    myArray[lvl][marioX][marioY] = 'H';
    fout += "Mario is starting in position: (" + to_string(marioX) + ", " + to_string(marioY) + ")\n";
    print(lvl);

    //we know mario will move after loop starts
    //and we've saved the unknown feature to variable 'something'
    //so we set the coordinates to empty
    myArray[lvl][marioX][marioY] = 'x'; //area is empty

    //until game ends
    while (mario->IsRunning()) {

        //the if statement checks for what feature 'something' is
        //and calls methods according to gameplay rules

        if (something == 'x') //if nothing
        {
            nothing(mario);
            MovesOn(marioX, marioY);
            moves += 1;
        }
        else if (something == 'c') //if coin
        {
            coin(mario);
            MovesOn(marioX, marioY);
            moves += 1;
        }
        else if (something == 'g') //if goomba
        {
            goomba(mario);
            if (mario->IsDead()) 
            {
                fout += "and did not survive.\n";
                mario->GameEnd();
                fout += "Lives: " + to_string(mario->GetLives()) + ".\n";
                fout += "Coins: " + to_string(mario->GetCoins()) + ".\n";
                fout += "Total moves: " + to_string(moves) + "\n";
                loss();
                break;
            }
            else 
            {
                fout += "and survived.\n";
                fout += "Lives: " + to_string(mario->GetLives()) + ".\n";
                fout += "Coins: " + to_string(mario->GetCoins()) + ".\n";
                MovesOn(marioX, marioY);
                moves += 1;
            }
        }
        else if (something == 'k') //if koopa troopa
        {
            koopa(mario);
            if (mario->IsDead())
            {
                fout += "and did not survive.\n";
                mario->GameEnd();
                fout += "Lives: " + to_string(mario->GetLives()) + ".\n";
                fout += "Coins: " + to_string(mario->GetCoins()) + ".\n";
                fout += "Total moves: " + to_string(moves) + "\n";
                loss();
                break;
            }
            else 
            {
                fout += "and survived.\n";
                fout += "Lives: " + to_string(mario->GetLives()) + ".\n";
                fout += "Coins: " + to_string(mario->GetCoins()) + ".\n";
                MovesOn(marioX, marioY);
                moves += 1;
            }
        }
        else if (something == 'm') //if mushroom
        {
            mushroom(mario);
            MovesOn(marioX, marioY);
            moves += 1;
        }
        else if (something == 'b') //if boss
        {
            boss(mario);
            if (mario->IsDead())
            {
                fout += "did not win.\n";
                mario->GameEnd();
                fout += "Lives: " + to_string(mario->GetLives()) + "\n";
                fout += "Coins: " + to_string(mario->GetCoins()) + "\n";
                fout += "Total moves: " + to_string(moves) + "\n";
                loss();
                break;
            }
            else if (lvl == finalLvl)
            {
                fout += "won.\n";
                mario->GameEnd();
                fout += "Lives: " + to_string(mario->GetLives()) + "\n";
                fout += "Coins: " + to_string(mario->GetCoins()) + "\n";
                fout += "Total moves: " + to_string(moves) + "\n";
                win();
                break;
            }
            else if (lvl != finalLvl)
            {
                fout += "won.\n";
                fout += "Lives: " + to_string(mario->GetLives()) + "\n";
                fout += "Coins: " + to_string(mario->GetCoins()) + "\n";
                MovesOn(marioX, marioY);
                moves += 1;
            }
        }
        else if (something == 'w') //if warp
        {
            warp();
            continue;
        }

        //since mario moves position after he finds something (if he doesn't warp)
        //we set 'something' to where mario has moved
        //and the loop continues...
        something = myArray[lvl][marioX][marioY];
    } 
}

//MovesOn (mario's movement)
void World::MovesOn(int x, int y){
    char dir = direction();

    if(dir == 'l'){
        fout += "LEFT\n";
        marioX = x;
        if (y == 0){
            marioY = N - 1;
        }
        else{
            marioY = y - 1;
        }
    }
    else if(dir == 'r'){
        fout += "RIGHT\n";
        marioX = x;
        if (y == (N - 1)){
            marioY = 0;
        }
        else{
            marioY = y + 1;
        }
    }
    else if(dir == 'u'){
        fout += "UP\n";
        marioY = y;
        if (x == 0){
            marioX = N - 1;
        }
        else{
            marioX = x - 1;
        }
    }
    else if(dir == 'd'){
        fout += "DOWN\n";
        marioY = y;
        if (x == (N - 1)){
            marioX = 0;
        }
        else{
            marioX = x + 1;
        }
    }
}

//direction (supplementary to MovesOn())
char World::direction(){

    random_device rd;
    uniform_int_distribution<int> dist(1, 100);

    int rand = dist(rd);
                
    if (rand <= 25)
        return 'l';
    else if (rand <= 50)
        return 'r';
    else if (rand <= 75)
        return 'u';
    else {
        return 'd';
    }
}

//NewLevel
void World::NewLevel(){
    random_device rd;
    uniform_int_distribution<int> dist(0, (N - 1));

    marioX = dist(rd);
    marioY = dist(rd);
}

//nothing
void World::nothing(Mario* mario){

    //file output
    fout += "Level: " + to_string(lvl) + ". Mario is at position: (" 
    + to_string(marioX) + ", " + to_string(marioY) + ").\n";
    fout += "Power level: " + to_string(mario->GetPower()) + ".\n";
    fout += "There is nothing.\n";
    fout += "Lives: " + to_string(mario->GetLives()) + ".\n";
    fout += "Coins: " + to_string(mario->GetCoins()) + ".\n";
}

//coin
void World::coin(Mario* mario){

    //file output
    fout += "Level: " + to_string(lvl) + ". Mario is at position: (" 
    + to_string(marioX) + ", " + to_string(marioY) + ").\n";
    fout += "Power level: " + to_string(mario->GetPower()) + ".\n";
    
    //adds coin to pouch
    const int numCoins = mario->AddCoin();

    //file output
    fout += "Mario found a coin. He now has " + to_string(numCoins) + " coin(s). ";

    //checking if mario has twenty coins
    bool twentyCoins = mario->CheckTwentyCoins();
    if (twentyCoins){
        fout += "Mario has gained a life. Mario now has \n" + to_string(mario->GetLives()) + " many lives.\n";
    }
    else {
        fout += "\n";
    }

    //area is now empty
    myArray[lvl][marioX][marioY] = 'x';

    //file output
    fout += "Lives: " + to_string(mario->GetLives()) + ".\n";
    fout += "Coins: " + to_string(mario->GetCoins()) + ".\n";
} 

//goomba
void World::goomba(Mario* mario){

    //file output
    fout += "Level: " + to_string(lvl) + ". Mario is at position: (" 
    + to_string(marioX) + ", " + to_string(marioY) + ").\n";
    fout += "Power level: " + to_string(mario->GetPower()) + ".\n";
    fout += "Mario encountered a Goomba ";

    //mario fights goomba
    bool win = mario->GoombaWin();

    if (win) //if mario wins
    {
        mario->EnemyDefeated(); //add enemy to defeats in one life
        mario->CheckEnemies(); //check if 7 enemies are defeated in one life
        myArray[lvl][marioX][marioY] = 'x'; //area is now empty
    }
    else //else mario loses
    {
        bool lifeLost = mario->PowerDownBool(); //checks if life is lost
        bool isDead = mario->IsDead(); //checks if mario is dead
        if (lifeLost && !isDead){ //if life is lost and mario is not dead keep fighting
            while (!isDead) { //while mario isn't dead
                win = mario->GoombaWin(); //mario fights goomba

                if (win){ //if mario wins
                    myArray[lvl][marioX][marioY] = 'x'; //area is now empty
                    break;
                }
                else { //else mario loses
                    mario->PowerDown(); //powers down
                    isDead = mario->IsDead(); //checks if mario is dead
                }
            }
        } 
    }
} 

//koopa
void World::koopa(Mario* mario){

    //file output
    fout += "Level: " + to_string(lvl) + ". Mario is at position: (" 
    + to_string(marioX) + ", " + to_string(marioY) + ").\n";
    fout += "Power level: " + to_string(mario->GetPower()) + ".\n";
    fout += "Mario encountered a Koopa Troopa ";

    //mario fights koopa troopa
    bool win = mario->KoopaWin();

    if (win) //if mario wins
    {
        mario->EnemyDefeated(); //add enemy to defeats in one life
        mario->CheckEnemies(); //check if 7 enemies are defeated in one life
        myArray[lvl][marioX][marioY] = 'x'; //area is empty
    }
    else //else mario loses
    {
        bool lifeLost = mario->PowerDownBool(); //checks if life is lost
        bool isDead = mario->IsDead(); //checks if mario is dead
        if (lifeLost && !isDead){ //if life is lost and not dead keep fighting
            while (!isDead) { //while mario isn't dead
                win = mario->KoopaWin(); //mario fights koopa troopa

                if (win){ //if mario wins
                    myArray[lvl][marioX][marioY] = 'x'; //area is empty
                    break;
                }
                else { //else mario loses
                    mario->PowerDown(); //powers down
                    isDead = mario->IsDead(); //checks if mario is dead
                }
            }
        }  
    }
}

//mushroom
void World::mushroom(Mario* mario){

    //file output
    fout += "Level: " + to_string(lvl) + ". Mario is at position: (" 
    + to_string(marioX) + ", " + to_string(marioY) + ").\n";
    fout += "Power level: " + to_string(mario->GetPower()) + ".\n";
    
    //power up!
    mario->PowerUp();

    //area is now empty
    myArray[lvl][marioX][marioY] = 'x';

    //file output
    fout += "Mario found a mushroom. Mario powered up to level " + to_string(mario->GetPower()) + ".\n";
    fout += "Lives: " + to_string(mario->GetLives()) + ".\n";
    fout += "Coins: " + to_string(mario->GetCoins()) + ".\n";
} 

//boss
void World::boss(Mario* mario){

    //file output
    fout += "Level: " + to_string(lvl) + ". Mario is at position: (" 
    + to_string(marioX) + ", " + to_string(marioY) + ").\n";
    fout += "Power level: " + to_string(mario->GetPower()) + ".\n";
    fout += "Mario encountered a boss and ";

    //mario fights a boss!
    bool win = mario->BossWin();

    if (lvl == finalLvl){ //if mario is on the final level (win or lose situation)

        if (!win) //if he loses
        {
            mario->PowerDown(); //powers down twice
            mario->PowerDown();
            bool isDead = mario->IsDead(); // checks if mario is dead
            if (!isDead){ // if mario is not dead keep fighting boss
                while (!isDead) { //while mario is not dead
                    win = mario->BossWin(); //mario fights boss

                    if (win){ //if mario wins
                        break;
                    }
                    else { //else mario loses
                        mario->PowerDown(); //powers down twice
                        mario->PowerDown();
                        isDead = mario->IsDead(); //checks if mario is dead
                    }
                }
            }
        }  
    }
    else { //else not final boss

        if (win) //if mario wins against normal boss
        {
            mario->EnemyDefeated(); //add enemy to defeats in one life
            mario->CheckEnemies(); //check if 7 enemies are defeated in one life
            myArray[lvl][marioX][marioY] = 'x'; //area is now empty
        }
        else  //else he loses to normal boss
        {
            mario->PowerDown(); //powers down twice
            mario->PowerDown();
            bool isDead = mario->IsDead(); //checks if mario is dead
            if (!isDead){ //if mario is not dead keep fighting boss
                while (!isDead) { //while mario is not dead
                    win = mario->BossWin(); //mario fights boss

                    if (win){ //if mario wins
                        myArray[lvl][marioX][marioY] = 'x'; //area is now empty
                        break;
                    }
                    else { //else mario loses
                        mario->PowerDown(); //mario powers down twice
                        mario->PowerDown();
                        isDead = mario->IsDead(); //checks if mario is dead
                    }
                }
            }
        }
    }
} 

//warp
void World::warp(){

    //file output
    fout += "Level: " + to_string(lvl) + ". Mario is at position: (" 
    + to_string(marioX) + ", " + to_string(marioY) + ").\n";
    fout += "Mario found a warp pipe. ";
    fout += "Mario will warp to\nthe next level!\n";

    //mario warps to next level!
    lvl = lvl + 1;
    NewLevel();

    //mario has now warped to a random position in the next level
    something = myArray[lvl][marioX][marioY]; //set something equal to mario's current position
    myArray[lvl][marioX][marioY] = 'H'; //update mario's current position to be reflected in array
    
    //file output
    print(lvl);
    fout += "Level: " + to_string(lvl) + ". Mario will start at position: (" + to_string(marioX) + ", " + to_string(marioY) +  ").\n";

    //area is now empty
    myArray[lvl][marioX][marioY] = 'x';
}

//loss
void World::loss(){

    //file output
    fout += "YOU LOST THE GAME.\n";
}

//win
void World::win(){

    //file output
    fout += "PRINCESS PEACH WAS SAVED. YOU BEAT THE GAME! :D\n";
}

//output (for game log)
string World::output() const{

    //return file output
    return fout;
}