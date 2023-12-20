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
#include "day6.h"
using namespace std;

void printMessageSoFar(vector<char> &message) {
    for (char c : message) {
        cout << c;
    }
}

bool areLastFourDifferent(vector<char> &message) {

    if (message.size() < 4) {
        cout << "message too small: ";
        printMessageSoFar(message);
        cout << "\n";
        return false;
    }
    char one = message[message.size()-1];
    char two = message[message.size()-2];
    char three = message[message.size()-3];
    char four = message[message.size()-4];
    cout << "Looking at last four chars: " << "one: " << one << ", two: " << two << ", three: " << three << ", four: " << four << "\n";
    return (one != two && one != three && one != four && two != three && two != four && three != four);
}

bool areLastNDifferent(vector<char> &message, int goalDifferent) {
    set<char> lastFourteen;
    if (message.size() < goalDifferent) {
        return false;
    }
    int floor = message.size() - goalDifferent;
    for (int i = message.size() - 1; i >= floor; i--) {
        lastFourteen.insert(message[i]);
    }
    if (lastFourteen.size() == goalDifferent) {
        return true;
    }
    return false;
}

void day6::readData() {
    ifstream myfile;
    myfile.open("../6/input.txt");
    string myline;
    if ( myfile.is_open() ) {
        int startIndex = 0;
        while ( myfile && !myfile.eof() ) { // equivalent to myfile.good()
            getline (myfile, myline);
            //cout << myline << "\n";
            vector<char> messageSoFar;
            for (char c : myline) {
                messageSoFar.push_back(c);
                if (areLastNDifferent(messageSoFar, 14)) {
                    cout << "Last four chars are different: ";
                    printMessageSoFar(messageSoFar);
                    cout << "\n";
                    cout << "startIndex of four different chars: " << startIndex + 1;
                    return;
                }
                startIndex++;
            }
        }
    } else {
        cout << "Couldn't open file\n";
    }
}

void day6::run() {
    readData();
}