# Not-So-Super-Mario-Bros

--------------------------------------------------- TITLE ---------------------------------------------------------------

__**Project Title**__: Not So Super Mario Bros Game Simulation

--------------------------------------------------- GOALS ---------------------------------------------------------------

__**Project goals**__:

**Goal**: Implement a Super Mario Bros inspired simulation.

**Gameplay**:

Our Not So Super Mario Bros. simulation is a far cry from the original game, but the goal remains the same 
– defeat Bowser and save the princess. The game simulation is carried out in a world that consists of a fixed 
number of levels. Mario must navigate the levels, encountering enemies and power-ups, and collecting coins, before engaging a boss to move onto the next level. A general outline of the program follows below.

**The World**:

The world consists of a number of levels, L, which will be provided at runtime. To finish the
game, Mario must navigate from level 1 to level L by defeating intermediate bosses and defeat
the final boss in level L. If Mario runs out of lives before this task is accomplished, the game is
lost.

**Mario - Our Protagonist**:

In our simulation, Mario starts with a number of lives, V, which will be provided at runtime. Mario
also has the ability to collect coins. He starts with 0 coins. For every 20 coins collected, he earns
an extra life (and the number of coins resets to 0). At any moment, Mario is in one of 3 power
levels, PL0, PL1, and PL2. PL0 is the weakest and PL2 is the strongest. Mario can increase
power levels by coming in contact with a mushroom (a “magic” mushroom), and loses a power
level if hurt by an enemy.

**A Level**:

Each level in our game is represented by an NxN grid (think 2D array), with N provided at
runtime. Mario may navigate the grid by moving up, down, left, and right only. The grid wraps
horizontally and vertically (a torus). For example, if Mario is in the rightmost column and moves
right, he will wrap to the same row in the leftmost column.

Every position in the grid can be populated with one of the following:
- A coin
- A mushroom
- A Goomba or a Koopa Troopa
- The boss of the level (there must be exactly 1 per level)
- Nothing

Additionally, every level from 1 to L-1 contains a SINGLE warp pipe somewhere on the grid.
The final level does not contain a warp pipe.

Mario’s Interaction with the Environment:

Mario will begin at a random location in the first level, with power PL0, and starts interacting with
the environment immediately. Once he has interacted with the current location, he moves on to
the next location by moving up, down, left, or right. The direction is chosen randomly with
uniform probability (25% each). Interactions with each position occur as follows:

- If the position contains nothing, Mario moves on.
- If the position contains a coin, Mario adds the coin to his wallet, and then the position
contains nothing. Mario moves on.
- If the position contains a mushroom, Mario’s power level increases by 1, or stays at PL2
if he’s already in PL2. Once the mushroom is consumed, the position contains nothing,
and Mario moves on.
- If the position contains a Goomba or Koopa, Mario engages per the rules of a regular
enemy, below.
- If the position contains the level boss, Mario engages per the rules of a boss, below.
- If Mario encounters the warp pipe, he will immediately jump to a random position in the
next level without having to beat the current level boss.

Mario’s Interaction with a Regular Enemy:

When Mario encounters a regular enemy, gameplay proceeds as follows:

- If the enemy is a Goomba, Mario defeats the enemy with a 80% probability, the position
- becomes empty, and Mario moves on. If Mario loses (20% probability), his power level is
decreased by 1, the Goomba stays in the position, and Mario moves on. The exception
is if Mario loses while at PL0, in which case a life is lost. If Mario has another life, he
continues at the same location, with PL0. Otherwise, the simulation ends, and the game
is lost.
- If the enemy is a Koopa, Mario defeats the enemy with a 65% probability, the position
- becomes empty, and Mario moves on. If Mario loses (35% probability), his power level is
decreased by 1, the Koopa stays in the position, and Mario moves on. The exception is if
Mario loses while at PL0, in which case a life is lost. If Mario has another life, he
continues at the same location, with PL0. Otherwise, the simulation ends, and the game
is lost.
- If Mario defeats 7 enemies on the same life, he earns another life.
Mario’s Interaction with a Boss
When Mario encounters a level boss, gameplay proceeds as follows:
- Mario defeats the enemy with a 50% probability, the position becomes empty, and Mario
moves on to the next level. If Mario is in the last level, the princess is saved, the game is
won, and the simulation is over. If Mario loses (50% probability), his power level is
decreased by 2, and Mario attempts to defeat the boss again. The exception is if Mario
loses while at PL0 or PL1, in which case a life is lost. If Mario has another life, he
continues at the same location, with PL0. Otherwise, the simulation ends, and the game
is lost.

**The Program**:

The program will take as command line input the name of a plain text file that has the following
format:

- Line # 1 is the number of levels, L (a positive integer)
- Line # 2 is the dimension of the grid, N (a positive integer)
- Line # 3 is the number of initial lives, V (a positive integer)
- Line # 4 is the approximate percentage of the positions in each level with coins (a positive
integer)
- Line # 5 is the approximate percentage of the positions in each level with nothing (a positive
integer)
- Line # 6 is the approximate percentage of the positions in each level with Goombas (a positive
integer)
- Line # 7 is the approximate percentage of the positions in each level with Koopas (a positive
integer)
- Line # 8 is the approximate percentage of the positions in each level with mushrooms (a positive
integer)

Note that the values on lines 4-8 MUST sum to 100.

Once the file is read, a world with the appropriate number of levels is constructed. Each level
should be populated using the specifications provided. In addition, a level boss should be
placed randomly, as well as a warp pipe (for all but the last level). Mario is placed at a random
position in the first level with PL0 and the simulation begins until the game is won or lost.

The output of the game is a plain text file that represents a log of every move Mario has made.

The log should start by printing a character representation (see below) of each level, prior to
Mario being placed and interacting with the environment. There should be a newline after each
level representation.

Each subsequent line of the file should specify:

- The level number
- The position location of Mario (a row and column number)
- The current power level of Mario before interacting with the position
- The action that was taken in that position:
- The number of lives Mario has after interacting with the position
- The number of coins Mario has after interacting with the position
- The direction that Mario will move next (UP, DOWN, LEFT, RIGHT)

The last line of the file should specify whether Mario won or lost the game, and the total number
of moves it took to reach that point.

**Data Structure**:
The world is represented (textually) as a 3D LxNxN array of characters. For each of the L
levels, each of the NxN grid positions are represented by the following characters:
- x - nothing
- m - a mushroom
- c - a coin
- g - a Goomba
- k - a Koopa Troopa
- b - the level boss
- w - a warp pipe
- H - stands for hero. Mario’s current position.


--------------------------------------------------- IMPLEMENTATION ----------------------------------------------------------

__**Project Implementation**__:

The program starts in **main** with a proper introduction to the game and the **rules of engagement**. In order to simulate the mock Super Mario Bros game, the user must provide, as input, the name of a .txt file with the following information:

- Line # 1 specifies the number of levels.
- Line # 2 specifies the dimension of the grid of each level.
- Line # 3 specifies the number of initial lives.
- Line # 4 specifies the percentage of the positions in each level with coins.
- Line # 5 specifies the percentage of the positions in each level with nothing.
- Line # 6 specifies the percentage of the positions in each level with Goombas.
- Line # 7 specifies the percentage of the positions in each level with Koopa Troopas.
- Line # 8 specifies the percentage of the positions in each level with mushrooms.

The following rules must be adhered to by the .txt file provided (otherwise handled by error checking):
1. All lines provided must consist of positive integers.
2. Your .txt file must contain only 8 lines (nothing more or less).
3. The sum of the percentages in lines 4-8 must equal 100.

After the rules has been laid out, the user is given the option to **start the game** or **exit the program.**

If they decide to start, we get the name of their **.txt file as input**.

Once the name of the file is provided, the program **reads the file** contents and correspondingly **checks for any error** (rules broken or file exceptions). If all tests are passed, the program proceeds to the next phase.

The simulation relies on two classes (besides main). One class represents our protagonist -- **Mario class** -- while another class represents our world -- **World class**.


**Mario Class**:

This class initializes and regulates Mario's power level, lives, coins, enemies defeated, and the game's end.

The constructor takes in an integer argument of lives, provided by the user in the file given.

Mario Class methods:

``` cpp
    bool GoombaWin(); // simulates Goomba encounter (returns true for win, false for loss)
    bool KoopaWin(); // simulates Koopa Troopa ecounter (returns true for win, false for loss)
    bool BossWin(); // simulates Boss encounter (returns true for win, false for loss)

    void GameEnd(); // to be called in World class when game has ended
    bool IsRunning(); // returns true if Mario is alive, false if Mario is not alive

    bool IsDead(); // checks if mario is dead

    void EnemyDefeated(); // adds an enemy to enemies defeated in one life
    void CheckEnemies(); // checks if 7 enemies are defeated in one life and adds a life correspondingly

    int AddCoin(); // adds coin to Mario's collection
    bool CheckTwentyCoins(); // checks if mario has 20 coins, adds life correspondingly (true if 20 coins, else false)

    void PowerUp(); // Mario powers up
    bool PowerDownBool(); // Mario powers down (returns true if life is lost, else false)
    void PowerDown(); // Mario powers down

    int GetCoins() const; // returns Mario's coins
    int GetPower() const; // returns Mario's power level
    int GetLives() const; // returns Mario's lives
```

**World Class**:

This class initializes a 3D LxNxN array of characters -- Where L represents the number of levels and N represents the dimensions of each level.

For each of the L levels, each of the NxN grid positions are represented by the following characters:
- x - nothing
- m - a mushroom
- c - a coin
- g - a Goomba
- k - a Koopa Troopa
- b - the level boss
- w - a warp pipe
- H - stands for hero. Mario’s current position.

Features are generated using the percentages given by the user. Along with those features generated are level bosses placed randomly on each level, and warp pipes placed randomly on every level except the last.

World Class methods:

```cpp
    void MarioSim(Mario* mario); // simulates a Super Mario Bros game

    void nothing(Mario* mario); // called in MarioSim() when Mario finds nothing
    void coin(Mario* mario); // called in MarioSim when Mario finds a coin
    void goomba(Mario* mario); // called in MarioSim when Mario finds a Goomba
    void koopa(Mario* mario); // called in MarioSim when Mario finds a Koopa
    void mushroom(Mario* mario); // called in MarioSim when Mario finds a magic mushroom
    void boss(Mario* mario); // called in MarioSim when Mario finds a boss
    void warp(); // called in MarioSim when Mario find a warp

    void NewLevel(); // generate random coordinates (used once Mario warps)
    void MovesOn(int x, int y); // implements Mario's movement (up 1, down 1, left 1, or right 1)
    char direction(); // generates a random direction for MovesOn() (25% probability each direction)

    void print(); // concatenates pretty representation of the world (3D array) to a string
    void print(int lvl); // concatenates the level (NxN array) Mario is on to a string
    void loss(); // concatenates loss message to a string
    void win(); // concatenates win message to a string
    string output() const; // returns the game log as a string
```

**Main**:

In main, we **instantiate** a **Mario object** (with lives, V), and a **World object** (with levels, dimensions, and percentages).

We **simulate a game** using the World class method:

```cpp
    void MarioSim(Mario* mario);
```

We **create an output file** and **write to it** using the World class method: 

```cpp
    string output() const;
```

Before our program exits, we **clear the heap** of our Mario and World objects.

Finally, **the program exits**.


--------------------------------------------------- SAMPLE INPUT ----------------------------------------------------------

__**Sample Input Files**__:

Provided in this repository are 12 sample input files. 

Although more test cases exist, all 12 input files consist of **unique test cases** relevant to the function of this program. 

**Here is a breakdown** of each sample input file's test case:

Sample 1 - Regular Input:
- File consists of regular input that adheres to the rules of engagement.
- Program will provide a personalized game log accordingly.

Sample 2 - lines < 8:
- File has less than 8 lines, breaking a rule of an engagement.
- The program outputs a corresponding error message to the user.

Sample 3 - lines > 8:
- File has more than 8 lines, breaking a rule of an engagement.
- The program outputs a corresponding error message to the user.

Sample 4 - Negative Integer:
- File contains 8 lines, but has a negative integer, breaking a rule of an engagement.
- The program outputs a corresponding error message to the user.

Sample 5 - Floating Point Value:
- File contains 8 lines, but has a float, breaking a rule of an engagement.
- The program outputs a corresponding error message to the user.

Sample 6 - String:
- File contains 8 lines, but has a string, breaking a rule of an engagement.
- The program outputs a corresponding error message to the user.

Sample 7 - 100% coins:
- File has value 100 listed under the percent chance of coins.
- Program will provide a personalized game log accordingly.

Sample 8 - 100% nothing:
- File has value 100 listed under the percent chance of nothing.
- Program will provide a personalized game log accordingly.

Sample 9 - 100% Goombas:
- File has value 100 listed under the percent chance of Goombas.
- Program will provide a personalized game log accordingly.

Sample 10 - 100% Koopa Troopas:
- File has value 100 listed under the percent chance of Koopa Troopas.
- Program will provide a personalized game log accordingly.

Sample 11 - 100% magic mushrooms:
- File has value 100 listed under the percent chance of mushrooms.
- Program will provide a personalized game log accordingly.

Sample 12 - Invalid Integer:
- File contains 8 lines, but has an invalid integer, breaking a rule of an engagement.
- The program outputs a corresponding error message to the user.

--------------------------------------------------- END --------------------------------------------------------------