#include "World.h"

using namespace std;

//function to validate each line of input (must be a positive integer)
bool isPositiveInt(string input)
{
    if (input.empty())
    {
        return false;
    }

    if (input[0] == '-')
    {
        return false;
    }

    if (input[0] == '0' && input.size() > 1)
    {
        return false;
    }

    for (int i = 0; i < input.size(); ++i)
    {
        if (!isdigit(input[i]))
        {
            return false;
        }
    }
    return true;
}

//main
int main(int argc, char **argv) {

    const int MAX_SIZE = 20; //constant int representing the fixed size of te array
    const int MAX_LINES = 8; //constant int representing the maximum lines in an input file
    int lines = 0; //int that tracks how many lines have been read from file
    string infilename; //input file name
    ifstream file; //file object
    string play; //variable that allows user to choose whether to start program or quit
    string array[MAX_SIZE]; //initialize an array of const int MAX_SIZE


    cout << endl << endl << "Welcome to Not So Super Mario Bros, your very own Mario simulation!" << endl;
    cout << "To sim, provide the name of a .txt input file with the following information:" << endl;
    cout << endl;

    cout << "Line # 1: the number of levels." << endl;
    cout << "Line # 2: the dimension of the grid of each level." << endl;
    cout << "Line # 3: the number of initial lives." << endl;
    cout << "Line # 4: the percentage of the positions in each level with coins." << endl;
    cout << "Line # 5: the percentage of the positions in each level with nothing." << endl;
    cout << "Line # 6: the percentage of the positions in each level with Goombas." << endl;
    cout << "Line # 7: the percentage of the positions in each level with Koopa Troopas." << endl;
    cout << "Line # 8: the percentage of the positions in each level with mushrooms." << endl;
    cout << endl;

    cout << "RULES: " << endl;
    cout << "1. All lines provided must consist of positive integers." << endl;
    cout << "2. Your .txt file must contain only 8 lines (nothing more or less)." << endl;
    cout << "3. The sum of the percentages in lines 4-8 must equal 100." << endl;
    cout << endl;

    //simulation start
    //takes string as user input where 'p' indicates start
    cout << "Press 'p' to start (otherwise program will exit): ";
    cin >> play;

    //if letter entered isn't 'p' exit
    if (tolower(play[0]) != 'p' || play.size() > 1) 
    {
        cout << endl << "Program has exited." << endl;
        cout << endl;
        return 0;
    }
    
    //ignore newline
    cin.ignore(1, '\n');
    cout << endl;

    //take file name as input
    cout << "Input Filename (include .txt): ";
    cin >> infilename;
    cout << endl;

    //open file
    file.open(infilename);

    //check if file has been opened
    if (file.fail()) {
        cout << "File failed to open." << endl;
        return 1; //1 indicates program failure
    }

    //read file
    while(!file.eof()) //while we have not reached end of file
    { 
        //reads and stores each line into string array 
        getline(file, array[lines]); 

        //increments line
        lines++;

        //break loop if we have reached the maximum size of the array
        if (lines == MAX_SIZE) 
        {
            cout << "Maximum array storage reached." << endl;
            cout << endl;
            break;
        }
    }

    //close file
    file.close();

    //exit program if lines read is not equal to 8
    if (lines != MAX_LINES) 
        {
            cout << "Invalid input. The .txt file must contain only 8 lines as specified above (2)." << endl;
            cout << endl;
            return 0;
        }

    //exit program if any single line is not a positive integer
    for (int i = 0; i < MAX_LINES; ++i)
    {
        if (!isPositiveInt(array[i]))
        {
            cout << "Invalid input. The .txt file must contain only positive integers as specified above (1)." << endl;
            cout << endl;
            return 0;
        }
    }

    //store array values as variables 
    int L = stoi(array[0]); //num levels
    int N = stoi(array[1]); //dimension of grid
    int V = stoi(array[2]); //num initial lives
    int c = stoi(array[3]); //percent chance of coin
    int x = stoi(array[4]); //percent chance of nothing
    int g = stoi(array[5]); //percent chance of goomba
    int k = stoi(array[6]); //percent chance of koopa
    int m = stoi(array[7]); //percent chance of mushroom
    
    int totalP = c + x + g + k + m; //sums total percentage of lines 4-8

    //if total percentage is not equal to 100, exit program
    if (totalP != 100)
    {  
        cout << "Invalid input. Percentage values in lines 4-8 must sum to 100 (3)." << endl;
        cout << endl;
        return 0;
    }

    //initialize mario's world
    World *myWorld = new World(L, N, c, x, g, k, m);

    //initialize mario
    Mario* mario = new Mario(V);

    //sim game
    myWorld->MarioSim(mario);

    string ofilename = "myMarioSim.txt"; //file name
    fstream ofile; //output file object

    //open output file
    ofile.open(ofilename, ios::out);

    //check that file is open and write to it
    if(ofile.is_open())
    {
        //write output of simulation to output file
        ofile << myWorld->output();

        //close file
        ofile.close();
    }

    //clear heap (garbage collect)
    delete myWorld;
    delete mario;

    return 0;
}