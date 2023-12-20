//
// Created by Nisse on 2022-12-22.
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
#include "day10.h"

void handleDisplay(int cycle, int x) {
    if (cycle % 40 == 0) {
        cout << "\n";
    }
    if (abs((cycle % 40) - x) <= 1) {
        cout << "#";
    } else {
        cout << ".";
    }
}

int checkPrintValue(int cycle, int x) {
    handleDisplay(cycle, x);
    if ((cycle+20)%40 == 0) {
        //cout << "cycle: " << cycle << ", x: " << x << "\n";
        return cycle * x;
    }
    return 0;
}

void day10::readData() {
    ifstream myfile;
    myfile.open("../10/input.txt");
    string myline;
    if ( myfile.is_open() ) {
        // Keep a vector for each direction that for each index stores the highest tree yet. Will that do it?
        int x = 1;
        int cycle = 0;
        int sumSignalStrengths = 0;
        while ( myfile && !myfile.eof() ) { // equivalent to myfile.good()
            getline (myfile, myline);
            if (myline == "noop") {
                sumSignalStrengths += checkPrintValue(cycle, x);
                cycle++;
            } else {
                sumSignalStrengths += checkPrintValue(cycle, x);
                cycle++;
                sumSignalStrengths += checkPrintValue(cycle, x);
                cycle++;
                x += stoi(myline.substr(5, myline.size()));
            }
        }
        cout << "Sum strengths: " << sumSignalStrengths << "\n";
    } else {
        cout << "Couldn't open file\n";
    }
}

void day10::run() {
    readData();
}
