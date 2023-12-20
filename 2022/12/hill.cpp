//
// Created by Nisse on 2022-12-23.
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
#include <stdint.h>
using namespace std;
#include "hill.h"

struct Node {
    char c;
    int distance = INT32_MAX;
};

pair<int, int> getEnd(vector<vector<char>> &map) {
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[i].size(); j++) {
            if (map[i][j] == 'E') {
                return pair(i, j);
            }
        }
    }
    return pair(-1, -1);
}

pair<int, int> getSource(vector<vector<char>> &map) {
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[i].size(); j++) {
            if (map[i][j] == 'S') {
                return pair(i, j);
            }
        }
    }
    return pair(-1, -1);
}

void hill::readData() {
    ifstream myfile;
    myfile.open("../12/input_example.txt");
    string myline;
    vector<vector<Node>> map;
    pair<int, int> sourcePos;
    pair<int, int> endPos;
    vector<int> distance;
    if ( myfile.is_open() ) {
        // Keep a vector for each direction that for each index stores the highest tree yet. Will that do it?
        while ( myfile && !myfile.eof() ) { // equivalent to myfile.good()
            getline (myfile, myline);
            vector<char> line{};
            for (char c : myline) {
                line.push_back(c);
                distance.push_back(INT32_MAX);
            }
            //map.push_back(line);
        }

    } else {
        cout << "Couldn't open file\n";
    }
}

/*j\i 0  1  2
 * 0  x, x, x
 * 1  y, y, y
 * 2  z, z, z
 *
 * j + i*size = 0, 1, 2
 *              3, 4, 5
 *              6, 7, 8
 */

void hill::run() {
    readData();
}
