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
#include "day8.h"

void visibleFromLeftCorrected(vector<vector<int>> &trees, vector<vector<bool>> &visibleTrees) {
    int tallestSoFar = -1;
    for (int i = 0; i < trees.size(); i++) {
        for (int j = 0; j < trees[i].size(); j++) {
            int currentTree = trees[i][j];
            cout << currentTree;
            if (currentTree > tallestSoFar) {
                tallestSoFar = currentTree;
                if (!visibleTrees[i][j]) {
                    visibleTrees[i][j] = true;
                }
                cout << "*";
            }
        }
        tallestSoFar = -1;
        cout << "\n";
    }
}

void visibleFromRightCorrected(vector<vector<int>> &trees, vector<vector<bool>> &visibleTrees) {
    int tallestSoFar = -1;
    for (int i = trees.size() - 1; i >= 0; i--) {
        for (int j = trees[i].size() - 1; j >= 0; j--) {
            int currentTree = trees[i][j];
            cout << currentTree;
            if (currentTree > tallestSoFar) {
                tallestSoFar = currentTree;
                if (!visibleTrees[i][j]) {
                    visibleTrees[i][j] = true;
                }
                cout << "*";
            }
        }
        tallestSoFar = -1;
        cout << "\n";
    }
}

void visibleFromTopCorrected(vector<vector<int>> &trees, vector<vector<bool>> &visibleTrees) {
    int tallestSoFar = -1;
    for (int i = 0; i < trees[0].size(); i++) {
        for (int j = 0; j < trees.size(); j++) {
            int currentTree = trees[j][i];
            cout << currentTree;
            if (currentTree > tallestSoFar) {
                tallestSoFar = currentTree;
                if (!visibleTrees[j][i]) {
                    visibleTrees[j][i] = true;
                }
                cout << "*";
            }
        }
        tallestSoFar = -1;
        cout << "\n";
    }
}

void visibleFromBottomCorrected(vector<vector<int>> &trees, vector<vector<bool>> &visibleTrees) {
    int tallestSoFar = -1;
    for (int i = trees[0].size() - 1; i >= 0; i--) {
        for (int j = trees.size() - 1; j >= 0; j--) {
            int currentTree = trees[j][i];
            cout << currentTree;
            if (currentTree > tallestSoFar) {
                tallestSoFar = currentTree;
                if (!visibleTrees[j][i]) {
                    visibleTrees[j][i] = true;
                }
                cout << "*";
            }
        }
        tallestSoFar = -1;
        cout << "\n";
    }
}

int countVisibleTrees(vector<vector<bool>> &visibleTrees) {
    int numVisibleTrees = 0;
    for (int i = 0; i < visibleTrees.size(); i++){
        for (int j = 0; j < visibleTrees[i].size(); j++) {
            if (visibleTrees[i][j]) {
                numVisibleTrees++;
                cout << "1";
            } else {
                cout << "0";
            }
        }
        cout << "\n";
    }
    return numVisibleTrees;
}

int getScore(vector<vector<int>> &trees, int i, int j) {
    int first = 0, second = 0, third = 0, fourth = 0;
    for (int k = i + 1; k < trees.size(); k++) {
        first++;
        if (trees[k][j] >= trees[i][j]) {
            break;
        }
    }
    
    for (int k = i-1; k >= 0; k--) {
        second++;
        if (trees[k][j] >= trees[i][j]) {
            break;
        }
    }
    
    for (int k = j+1; k < trees[i].size(); k++) {
        third++;
        if (trees[i][k] >= trees[i][j]) {
            break;
        }
    }

    for (int k = j-1; k >= 0; k--) {
        fourth++;
        if (trees[i][k] >= trees[i][j]) {
            break;
        }
    }
    return first * second * third * fourth;
}

int getBestLocation(vector<vector<int>> &trees) {
    int betScore = -1;
    for (int i = 0; i < trees.size(); i++) {
        for (int j = 0; j < trees.size(); j++) {
            int score = getScore(trees, i, j);
            if (score > betScore) {
                betScore = score;
            }
        }
    }
    return betScore;
}

void day8::readData() {
    ifstream myfile;
    myfile.open("../8/input.txt");
    string myline;
    if ( myfile.is_open() ) {
        vector<vector<int>> trees;
        vector<vector<bool>> visibleTrees;
        // Keep a vector for each direction that for each index stores the highest tree yet. Will that do it?
        while ( myfile && !myfile.eof() ) { // equivalent to myfile.good()
            getline (myfile, myline);
            vector<int> line;
            vector<bool> visible;
            for (char c : myline) {
                int currentTree = c - 48;
                line.push_back(currentTree);
                visible.push_back(false);
            }
            trees.push_back(line);
            visibleTrees.push_back(visible);
        }
        cout << "Looking at trees " << "\n";
        cout << "From left corrected: \n";
        visibleFromLeftCorrected(trees, visibleTrees);
        cout << "From right corrected\n";
        visibleFromRightCorrected(trees, visibleTrees);
        cout << "From bottom corrected\n";
        visibleFromBottomCorrected(trees, visibleTrees);
        cout << "From top corrected:\n";
        visibleFromTopCorrected(trees, visibleTrees);

        int numVisibleTrees = countVisibleTrees(visibleTrees);

        cout << "visible treees: " << numVisibleTrees << "\n";

        int bestLocationScore = getBestLocation(trees);

        cout << "Best location score: " << bestLocationScore << "\n";
    } else {
        cout << "Couldn't open file\n";
    }
}

void day8::run() {
    readData();
}
