//
// Created by Nisse on 2022-12-19.
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
#include "day5.h"
using namespace std;

vector<stack<char>> initializeStacks(vector<vector<char>> &rawStacks) {
    vector<stack<char>> stacks;
    for (int i = 0; i < rawStacks[rawStacks.size()-1].size(); i++) {
        char c = rawStacks[rawStacks.size() - 1][i];
        if (c == ' ' || c == '[' || c == ']') {
            continue;
        } else {
            stack<char> stack;
            for (int j = rawStacks.size() - 1; j >= 0; j--) {
                if (i >= rawStacks[j].size()) {
                    break;
                }
                char value = rawStacks[j][i];
                if (value == ' ') {
                    break;
                }
                stack.push(value);
            }
            stacks.push_back(stack);
        }

    }
    return stacks;
}


void handleInstruction(int move, int from, int to, vector<stack<char>> &stacks) {
    for (int i = 0; i < move; i++) {
        char c = stacks[from - 1].top();
        stacks[from - 1].pop();
        stacks[to - 1].push(c);
    }
}

void handleInstruction2(int move, int from, int to, vector<stack<char>> &stacks) {
    stack<char> tempStack;
    for (int i = 0; i < move; i++) {
        char c = stacks[from - 1].top();
        stacks[from - 1].pop();
        tempStack.push(c);
    }
    for (int i = 0; i < move; i++) {
        char c = tempStack.top();
        tempStack.pop();
        stacks[to - 1].push(c);
    }
}

void printTopOfStacks(vector<stack<char>> &stacks) {
    cout << "Top of stacks: ";
    for (stack<char> &s: stacks) {
        cout << s.top();
    }
    cout << "\n";
}

void day5::readData() {
    ifstream myfile;
    myfile.open("../5/input.txt");
    string myline;
    if ( myfile.is_open() ) {

        vector<vector<char>> rawStacks;

        vector<stack<char>> stacks;

        bool stackPhase = true, indexes = false, instructions = false;
        int i = 0;

        while ( myfile && !myfile.eof() ) { // equivalent to myfile.good()
            getline (myfile, myline);

            cout << myline << "\n";

            if (stackPhase) {
                if (myline.find('1') != -1) {
                    stacks = initializeStacks(rawStacks);
                    stackPhase = false;
                    indexes = true;
                } else {
                    cout << "stackphase" << "\n";
                    vector<char> stackRow;
                    for (char c : myline) {
                        stackRow.push_back(c);
                    }
                    rawStacks.push_back(stackRow);
                }
            }
            if (indexes) {
                if (myline.find("move") != -1) {
                    indexes = false;
                    instructions = true;
                } else {
                    cout << "indexes" << "\n";
                    continue;
                }
            }
            if (instructions) {
                int move = stoi(myline.substr(5, myline.find("from") - 1));
                int from = stoi(myline.substr(myline.find("from") + 5, myline.find("to") - 1));
                int to = stoi(myline.substr(myline.find("to") + 3, myline.size()));

                handleInstruction2(move, from, to, stacks);
                cout << "instructions" << "\n";
                continue;
            }

            i++;
        }
        printTopOfStacks(stacks);
    } else {
        cout << "Couldn't open file\n";
    }
}

void day5::run() {
    day5::readData();
}