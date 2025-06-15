/* 
 * File:   main.cpp
 * Author: Joshua Nguyen
 * Created on June 14, 2025, 5 PM~~
 * Purpose:  High or Low game
 */

//System Libraries
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <cctype>

using namespace std;

//User Libraries

//Global Constants
const int MAX_PLR = 10; //Maximum number of players

//Function Prototypes
void play(string[], int[], int&);
int getRnd(int min = 1, int max = 100);

//Execution Begins Here
int main(int argc, char** argv) {
    //Set random seed
    srand(time(0));

    //Declare Variables
    string pNames[MAX_PLR]; //Array for player names
    int pScores[MAX_PLR];   //Parallel array for player scores
    int numPlyr = 0;        //Number of current players

    //For now, we just play one game to test the arrays
    play(pNames, pScores, numPlyr);

    //A simple loop to see if the data was stored
    cout << "\n--- Players in Memory ---" << endl;
    for(int i=0; i < numPlyr; i++){
        cout << pNames[i] << ": " << pScores[i] << endl;
    }

    //Exit the Program
    return 0;
}

int getRnd(int min, int max) {
    return rand() % (max - min + 1) + min;
}

void play(string names[], int scores[], int& num) {
    //Declare function-level variables
    string name;
    int score = 0;
    int current, next;
    char guess;
    const int ROUNDS = 10;

    //Get player name
    cout << "Enter your name: ";
    cin >> name;

    //Start game logic
    current = getRnd();
    cout << "\nStarting game for " << name << "!" << endl;

    for (int round = 0; round < ROUNDS; round++) {
        cout << "\nRound " << round + 1 << ": Current number is " << current << endl;
        cout << "Will the next number be (H)igher or (L)ower? ";
        cin >> guess;
        guess = toupper(guess);

        next = getRnd();
        cout << "Next number was: " << next << endl;

        if ((guess == 'H' && next > current) || (guess == 'L' && next < current)) {
            cout << "Correct!\n";
            score++;
        } else {
            cout << "Incorrect.\n";
        }
        current = next;
    }

    cout << "\n" << name << "'s final score: " << score << "/" << ROUNDS << endl;

    //Add new player to the arrays
    if(num < MAX_PLR){
        names[num] = name;
        scores[num] = score;
        num++; //Increment player count passed by reference
    }
}