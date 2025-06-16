/* 
 * File:   main.cpp
 * Author: Joshua Nguyen
 * Created on June 14, 2025, 6 PM~~
 * Purpose:  High or Low game
 */

//System Libraries
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <cctype>
#include <iomanip> //For formatting

using namespace std;

//User Libraries

//Global Constants
const int MAX_PLR = 10;

//Function Prototypes
void play(string[], int[], int&);
void prntBrd(const string[], const int[], int);
int getRnd(int min = 1, int max = 100);

//Execution Begins Here
int main(int argc, char** argv) {
    //Set random seed
    srand(time(0));

    //Declare Variables
    string pNames[MAX_PLR];
    int pScores[MAX_PLR];
    int numPlyr = 0;
    char choice;

    //Main menu loop
    do {
        cout << "\n-- Higher or Lower --" << endl;
        cout << "1. Play Game" << endl;
        cout << "2. View Scores" << endl;
        cout << "3. Quit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case '1':
                play(pNames, pScores, numPlyr);
                break;
            case '2':
                prntBrd(pNames, pScores, numPlyr);
                break;
            case '3':
                cout << "Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice." << endl;
        }
    } while (choice != '3');

    return 0;
}

int getRnd(int min, int max) {
    return rand() % (max - min + 1) + min;
}

void prntBrd(const string names[], const int scores[], int num) {
    cout << "\n--- Leaderboard ---" << endl;
    if (num == 0) {
        cout << "No scores yet." << endl;
        return;
    }
    cout << left << setw(10) << "Player" << right << setw(5) << "Score" << endl;
    cout << "-----------------" << endl;
    for (int i = 0; i < num; i++) {
        cout << left << setw(10) << names[i]
             << right << setw(5) << scores[i] << endl;
    }
}

void play(string names[], int scores[], int& num) {
    string name;
    int score = 0;
    int current, next;
    char guess;
    const int ROUNDS = 10;

    cout << "\nEnter your name: ";
    cin >> name;

    current = getRnd();
    cout << "\nStarting game for " << name << "!" << endl;

    for (int round = 0; round < ROUNDS; round++) {
        cout << "\nRound " << round + 1 << ": Current is " << current << endl;
        cout << "Will the next be (H)igher or (L)ower? ";
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
    if (num < MAX_PLR) {
        names[num] = name;
        scores[num] = score;
        num++;
    } else {
        cout << "Leaderboard is full!" << endl;
    }
}