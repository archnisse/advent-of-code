//
// Created by Nisse on 2022-12-18.
//
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;
#include "day2.h"

// A for Rock, B for Paper, and C for Scissors
// X for Rock, Y for Paper, and Z for Scissors

// X means you need to lose, Y means you need to end the round in a draw, and Z means you need to win. Good luck!

struct Round {
    char opponent;
    char you;
};

bool didIWin(Round round) {
    return round.you == 'Z';
    /*if (round.opponent == 'A' && round.you == 'Y') {
        return true;
    } else if (round.opponent == 'B' && round.you == 'Z') {
        return true;
    } else if (round.opponent == 'C' && round.you == 'X') {
        return true;
    } else {
        return false;
    }*/
}

bool didIDraw(Round round) {
    return round.you == 'Y';
    /*if (round.opponent == 'A' && round.you == 'X') {
        return true;
    } else if (round.opponent == 'B' && round.you == 'Y') {
        return true;
    } else if (round.opponent == 'C' && round.you == 'Z') {
        return true;
    } else {
        return false;
    }*/
}

// 1 for Rock, 2 for Paper, and 3 for Scissors
int scoreForMyMove(Round round) {
    if (round.you == 'X') { // Need to lose
        if (round.opponent == 'A') { // Opponent had rocks, we need to do scissor
            return 3;
        } else if (round.opponent == 'B') { // Opponent had paper, we need to do rock
            return 1;
        } else if (round.opponent == 'C') { // Opponent had scissor, we need to do paper
            return 2;
        }
    } else if (round.you == 'Y') { // We need to draw
        if (round.opponent == 'A') { // Opponent had rocks, we need to do rock
            return 1;
        } else if (round.opponent == 'B') { // Opponent had paper, we need to do paper
            return 2;
        } else if (round.opponent == 'C') { // Opponent had scissor, we need to do scissor
            return 3;
        }
    } else { // We need to win
        if (round.opponent == 'A') { // Opponent had rocks, we need to do paper
            return 2;
        } else if (round.opponent == 'B') { // Opponent had paper, we need to do scissor
            return 3;
        } else if (round.opponent == 'C') { // Opponent had scissor, we need to do rock
            return 1;
        }
    }
    /*if (round.you == 'X') {
        return 1;
    } else if (round.you == 'Y') {
        return 2;
    } else {
        return 3;
    }*/
}

int getMyScore(Round round) {
    int score = 0;
    if (didIWin(round)) {
        score += 6;
    } else if (didIDraw(round)) {
        score += 3;
    }
    score += scoreForMyMove(round);
    return score;
}

vector<Round> readData() {
    ifstream myfile;
    myfile.open("../2/input2.txt");
    string myline;
    vector<Round> rounds = vector<Round>{};
    if ( myfile.is_open() ) {
        while ( myfile && !myfile.eof() ) { // equivalent to myfile.good()
            getline (myfile, myline);
            //cout << myline << "\n";
            Round round{};
            round.opponent = myline.at(0);
            round.you = myline.at(2);
            rounds.push_back(round);
        }
    } else {
        cout << "Couldn't open file\n";
    }
    return rounds;
}

// Day2 first stage answer: 12679, stage 2 answer: 14470
int day2() {
    vector<Round> rounds = readData();
    int score = 0;
    for (Round round : rounds) {
        score += getMyScore(round);
        //cout << "score so far: " << score << "\n";
    }
    cout << "My total score: " << score;
}