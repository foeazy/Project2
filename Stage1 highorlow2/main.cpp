/* 
 * File:   main.cpp
 * Author: Joshua Nguyen
 * Created on June 14, 2025, 9:00 AM~~
 * Purpose:  High or Low game
 */

//System Libraries
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

//User Libraries

//Global Constants - Math/Science/Conversions only

//Function Prototypes
int getRand(int min, int max);
bool checkGuess(int current, int next, char guess);

//Execution Begins Here
int main(int argc, char** argv) {
    //Set random seed
    srand(time(0));

    //Declare Variables
    int current, next, score = 0;
    char guess;

    //Initialize Variables
    current = getRand(1, 100);

    //The Process -> Map Inputs to Outputs
    cout << "Welcome to Higher or Lower!" << endl;

    for (int round = 0; round < 10; round++) {
        cout << "\nRound " << round + 1 << ": Current number is " << current << endl;
        cout << "Will the next number be (H)igher or (L)ower? ";
        cin >> guess;
        guess = toupper(guess);

        next = getRand(1, 100);
        cout << "Next number was: " << next << endl;

        if (checkGuess(current, next, guess)) {
            cout << "Correct!\n";
            score++;
        } else {
            cout << "Incorrect.\n";
        }

        current = next;
    }

    //Display Inputs/Outputs
    cout << "\nGame over! Final score: " << score << "/10" << endl;

    //Exit the Program
    return 0;
}

int getRand(int min, int max) {
    return rand() % (max - min + 1) + min;
}

bool checkGuess(int current, int next, char guess) {
    if (guess == 'H' && next > current) return true;
    if (guess == 'L' && next < current) return true;
    return false;
}

