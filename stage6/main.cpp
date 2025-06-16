/* 
 * File:   main.cpp
 * Author: Joshua Nguyen
 * Created on June 14, 2025, 9 PM~~
 * Purpose:  High or Low game
 */

//System Libraries
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <cctype>
#include <iomanip>
#include <fstream>

using namespace std;

//Global Constants
const int MAX_PLR = 10;

//Function Prototypes
void play(string[], int[], int&);
void prntBrd(const string[], const int[], int);
void srtBord(string[], int[], int);
void filRead(string[], int[], int&);
void filSave(const string[], const int[], int);
void addPlyr(string[], int[], int&, string, int);
int findPlr(const string[], int, string);
int getRnd(int min = 1, int max = 100);

//Execution Begins Here
int main(int argc, char** argv) { /* ... Same as Stage 5 ... */
    srand(time(0)); string pNames[MAX_PLR]; int pScores[MAX_PLR]; int numPlyr = 0; char choice;
    filRead(pNames, pScores, numPlyr);
    do {
        cout << "\n-- Higher or Lower --" << endl;
        cout << "1. Play Game" << endl; cout << "2. View Leaderboard" << endl; cout << "3. Quit" << endl;
        cout << "Enter choice: "; cin >> choice;
        switch (choice) {
            case '1': play(pNames, pScores, numPlyr); break;
            case '2': prntBrd(pNames, pScores, numPlyr); break;
            case '3': filSave(pNames, pScores, numPlyr); cout << "Goodbye!" << endl; break;
            default: cout << "Invalid choice." << endl;
        }
    } while (choice != '3');
    return 0;
}

int findPlr(const string names[], int num, string name) {
    for (int i = 0; i < num; i++) {
        if (names[i] == name) {
            return i; //Return index of the found player
        }
    }
    return -1; //Return -1 if not found
}

void addPlyr(string names[], int scores[], int& num, string name, int score) {
    int pIndex = findPlr(names, num, name); //Search for player
    if (pIndex != -1) { //Player found
        if (score > scores[pIndex]) { //Update score if higher
            scores[pIndex] = score;
            cout << name << "'s high score updated!" << endl;
        }
    } else if (num < MAX_PLR) { //Player not found, add if space
        names[num] = name;
        scores[num] = score;
        num++;
    } else {
        cout << "Leaderboard is full. Cannot add new player." << endl;
    }
    srtBord(names, scores, num); //Sort after any change
}

void play(string names[], int scores[], int& num) {
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
    addPlyr(names, scores, num, name, score); //Use helper function to add/update
}

// ... Other functions (filRead, filSave, srtBord, prntBrd, getRnd) are unchanged from Stage 5 ...
void filRead(string n[], int s[], int& num){ifstream iF("leaderboard.txt");if(iF){while(num<MAX_PLR && iF>>n[num]>>s[num])num++;iF.close();}}
void filSave(const string n[],const int s[],int num){ofstream oF("leaderboard.txt");for(int i=0;i<num;i++)oF<<n[i]<<" "<<s[i]<<endl;oF.close();}
void srtBord(string n[], int s[], int num){for(int i=0;i<num-1;i++){int m=i;for(int j=i+1;j<num;j++)if(s[j]>s[m])m=j;swap(s[i],s[m]);swap(n[i],n[m]);}}
void prntBrd(const string n[],const int s[],int num){cout<<"\n--- Leaderboard ---"<<endl;if(num==0){cout<<"No scores yet."<<endl;return;}cout<<left<<setw(10)<<"Player"<<right<<setw(5)<<"Score"<<endl;cout<<"-----------------"<<endl;for(int i=0;i<num;i++)cout<<left<<setw(10)<<n[i]<<right<<setw(5)<<s[i]<<endl;}
int getRnd(int min, int max) { return rand() % (max - min + 1) + min; }