//
// Created by Nisse on 2023-12-20.
//
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;
#include "readData.h"

vector<string> readData::getFileContent(const string &filePath) {
    ifstream myfile;
    myfile.open(filePath);
    string myline;
    vector<string> lines;

    if ( myfile.is_open() ) {
        while (myfile && !myfile.eof()) { // equivalent to myfile.good()
            getline(myfile, myline);
            lines.push_back(myline);
        }
    }

    return lines;
}