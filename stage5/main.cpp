/* 
 * File:   main.cpp
 * Author: Joshua Nguyen
 * Created on June 14, 2025, 8 PM~~
 * Purpose:  High or Low game
 */

//System Libraries
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <cctype>
#include <iomanip>
#include <fstream> //For File I/O

using namespace std;

//Global Constants
const int MAX_PLR = 10;

//Function Prototypes
void play(string[], int[], int&);
void prntBrd(const string[], const int[], int);
void srtBord(string[], int[], int);
void filRead(string[], int[], int&);
void filSave(const string[], const int[], int);
int getRnd(int min = 1, int max = 100);

//Execution Begins Here
int main(int argc, char** argv) {
    srand(time(0));
    string pNames[MAX_PLR];
    int pScores[MAX_PLR];
    int numPlyr = 0;
    char choice;

    filRead(pNames, pScores, numPlyr); //Read data at start

    do {
        cout << "\n-- Higher or Lower --" << endl;
        cout << "1. Play Game" << endl;
        cout << "2. View Leaderboard" << endl;
        cout << "3. Quit" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        switch (choice) {
            case '1': play(pNames, pScores, numPlyr); break;
            case '2': prntBrd(pNames, pScores, numPlyr); break;
            case '3':
                filSave(pNames, pScores, numPlyr); //Save data on quit
                cout << "Goodbye!" << endl;
                break;
            default: cout << "Invalid choice." << endl;
        }
    } while (choice != '3');
    return 0;
}

void filRead(string names[], int scores[], int& num) {
    ifstream inFile("leaderboard.txt");
    if (inFile) {
        while (num < MAX_PLR && inFile >> names[num] >> scores[num]) {
            num++;
        }
        inFile.close();
    }
}

void filSave(const string names[], const int scores[], int num) {
    ofstream outFile("leaderboard.txt");
    for (int i = 0; i < num; i++) {
        outFile << names[i] << " " << scores[i] << endl;
    }
    outFile.close();
}

int getRnd(int min, int max) { return rand() % (max - min + 1) + min; }

void srtBord(string names[], int scores[], int num) { /* ... Same as Stage 4 ... */ 
    for (int i = 0; i < num - 1; i++) {
        int maxIdx = i;
        for (int j = i + 1; j < num; j++) { if (scores[j] > scores[maxIdx]) maxIdx = j; }
        swap(scores[i], scores[maxIdx]);
        swap(names[i], names[maxIdx]);
    }
}

void prntBrd(const string names[], const int scores[], int num) { /* ... Same as Stage 4 ... */
    cout << "\n--- Leaderboard ---" << endl;
    if (num == 0) { cout << "No scores yet." << endl; return; }
    cout << left << setw(10) << "Player" << right << setw(5) << "Score" << endl;
    cout << "-----------------" << endl;
    for (int i = 0; i < num; i++) {
        cout << left << setw(10) << names[i] << right << setw(5) << scores[i] << endl;
    }
}

void play(string names[], int scores[], int& num) { /* ... Same as Stage 4 ... */
    string name; int score = 0; int current, next; char guess; const int ROUNDS = 10;
    cout << "\nEnter your name: "; cin >> name;
    current = getRnd(); cout << "\nStarting game for " << name << "!" << endl;
    for (int round = 0; round < ROUNDS; round++) {
        cout << "\nRound " << round + 1 << ": Current is " << current << endl;
        cout << "Will the next be (H)igher or (L)ower? "; cin >> guess; guess = toupper(guess);
        next = getRnd(); cout << "Next number was: " << next << endl;
        if ((guess == 'H' && next > current) || (guess == 'L' && next < current)) {
            cout << "Correct!\n"; score++;
        } else { cout << "Incorrect.\n"; }
        current = next;
    }
    cout << "\n" << name << "'s final score: " << score << "/" << ROUNDS << endl;
    if (num < MAX_PLR) {
        names[num] = name; scores[num] = score; num++;
        srtBord(names, scores, num);
    } else { cout << "Leaderboard is full!" << endl; }
}
