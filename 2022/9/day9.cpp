//
// Created by Nisse on 2022-12-21.
//
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <map>
#include <set>
#include <stack>
using namespace std;
#include "day9.h"


bool updateTailPos(pair<int, int> &headPos, pair<int, int> &tailPos) {
    // If the tail needs to move it always moves to the heads latest position... Use that, instead of all this logic xD Comment this out though, might need it.
    // Is the tail too far away?
    if (abs(headPos.first - tailPos.first) > 1 || abs(headPos.second - tailPos.second) > 1) {
        // Tail needs to move
        if (headPos.first != tailPos.first && headPos.second == tailPos.second) {
            // Tail is on the same row, update first to move closer to head
            // Can i use changevector here... maybe, maybe not. Might just look at the number, go towards it. if bigger than or else
            if (headPos.first > tailPos.first) {
                tailPos.first++;
            } else {
                tailPos.first--;
            }
        } else if (headPos.first == tailPos.first && headPos.second != tailPos.second) {
            if (headPos.second > tailPos.second) {
                tailPos.second++;
            } else {
                tailPos.second--;
            }
        } else {
            // Movie diagonally, move both coords closer to the "head" coords
            if (headPos.first > tailPos.first) {
                tailPos.first++;
            } else {
                tailPos.first--;
            }
            if (headPos.second > tailPos.second) {
                tailPos.second++;
            } else {
                tailPos.second--;
            }
        }
        return true;
    }
    return false;
}

int ropeSize = 10;

struct Positions {
    pair<int, int> currentPosition;
    pair<int, int> lastPos;
};

void printBoard(vector<Positions> &rope) {
    int bound = 35;
    char chars[bound][bound];
    for (int i = 0; i < bound; i++) {
        for (int j = 0; j < bound; j++) {
            chars[i][j] = '.';
        }
    }

    for (int i = 0; i < rope.size(); i++) {
        Positions p = rope[i];
        char knot;
        if (i == 0) {
            knot = 'H';
        } else {
            knot = to_string(i)[0];
        }
        if (chars[p.currentPosition.first + 15][p.currentPosition.second + 15] == '.') {
            chars[p.currentPosition.first + 15][p.currentPosition.second + 15] = knot;
        }
    }

    for (int i = 0; i < bound; i++) {
        for (int j = 0; j < bound; j++) {
            cout << chars[i][j];
        }
        cout << "\n";
    }
    cout << "\n";
    cout << "====";
    cout << "\n";
}

void updateTail(vector<Positions> &rope) {
    bool diagonally = false;
    pair<int, int> diagonallyVector;
    for (int i = 1; i < rope.size(); i++) {
        //printBoard(rope);
        bool updatedTail = updateTailPos(rope[i-1].currentPosition, rope[i].currentPosition);
        if (!updatedTail) {
            break;
        }
        /*if (abs(rope[i-1].currentPosition.first - rope[i].currentPosition.first) > 1 || abs(rope[i-1].currentPosition.second - rope[i].currentPosition.second) > 1) {
            // Time to move, go to previous parts last pos.
            // TODO: Not handling diagonal moves. The tail can move diagonally, while the head couldn't. Last-pos thing no longer working... Might need a "moved diagonal" flag?
            rope[i].lastPos.first = rope[i].currentPosition.first;
            rope[i].lastPos.second = rope[i].currentPosition.second;
            if (diagonally) {
                rope[i].currentPosition.first += diagonallyVector.first;
                rope[i].currentPosition.second += diagonallyVector.second;
                //cout << "moved next part of tail diagonally\n";
            } else {
                if (rope[i].currentPosition.first != rope[i-1].lastPos.first && rope[i].currentPosition.second != rope[i-1].lastPos.second) {
                    // Moves diagonally.
                    diagonally = true;
                    diagonallyVector = pair(rope[i-1].lastPos.first - rope[i].currentPosition.first, rope[i-1].lastPos.second - rope[i].currentPosition.second);
                    //cout << "Moves part of tail diagonally.\n";
                }
                rope[i].currentPosition.first = rope[i-1].lastPos.first;
                rope[i].currentPosition.second = rope[i-1].lastPos.second;
            }
            cout << "moving tail part " << i << " to: " << rope[i].currentPosition.first << ", " << rope[i].currentPosition.second << "\n";
            if (i == ropeSize-1) {
                tailVisited.insert(pair(rope[i].currentPosition.first, rope[i].currentPosition.second));
            }
        } else {
            cout << "no need to move tail any more" << "\n";
            break;
        }*/
    }
}

void updateTailVisited(vector<Positions> &rope, set<pair<int, int>> &tailVisisted) {
    tailVisisted.insert(pair(rope[ropeSize-1].currentPosition.first, rope[ropeSize-1].currentPosition.second));
}

void updateHeadPos(pair<int, int> changeVector, int distance, vector<Positions> &positions, set<pair<int, int>> &tailVisited) {
    for (int i = 0; i < distance; i++) {
        positions[0].lastPos.first = positions[0].currentPosition.first;
        positions[0].lastPos.second = positions[0].currentPosition.second;
        positions[0].currentPosition.first += changeVector.first;
        positions[0].currentPosition.second += changeVector.second;
        //cout << "moving head to: " << positions[0].currentPosition.first << ", " << positions[0].currentPosition.second << "\n";
        updateTail(positions);
        updateTailVisited(positions, tailVisited);
        //cout << "    ----------    " << "\n";
    }
    //printBoard(positions);
}

void manageMove(char direction, int distance, set<pair<int, int>> &tailVisisted, vector<Positions> &positions) {
    pair<int, int> changeVector;
    if (direction == 'R') {
        changeVector = pair(1, 0);
    } if (direction == 'L') {
        changeVector = pair(-1, 0);
    } if (direction == 'U') {
        changeVector = pair(0, 1);
    } if (direction == 'D') {
        changeVector = pair(0, -1);
    }
    updateHeadPos(changeVector, distance, positions, tailVisisted);
}

/*
 * part 2: Make the knots a vector and iterate through it if it needs to update. Should be easy with the previous solution, and one can break when it has reached a knot that doesn't need to move.
 */

void day9::readData() {
    ifstream myfile;
    myfile.open("../9/input.txt");
    string myline;
    if ( myfile.is_open() ) {
        // Keep a vector for each direction that for each index stores the highest tree yet. Will that do it?
        pair<int, int> headPos = pair(0, 0);
        pair<int, int> tailPos = pair(0, 0);
        set<pair<int, int>> visitedByTail{};
        visitedByTail.insert(pair(0, 0));

        vector<Positions> positions{};
        for (int i = 0; i < ropeSize; i++) {
            positions.push_back(Positions{pair(0,0), pair(0,0)});
        }

        while ( myfile && !myfile.eof() ) { // equivalent to myfile.good()
            getline (myfile, myline);
            char direction = myline[0];
            string distanceString = myline.substr(2, myline.size());
            int distance = stoi(distanceString);
            cout << direction << " " << distance << "\n";
            manageMove(direction, distance, visitedByTail, positions);
        }
        cout << "Positions visited by rope: " << visitedByTail.size() << "\n";
    } else {
        cout << "Couldn't open file\n";
    }
}

// part 1 solution: 6494

void day9::run() {
    readData();
}
