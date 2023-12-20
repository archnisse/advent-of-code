//
// Created by Nisse on 2023-12-20.
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
#include "calibration.h"
#include "../readData.h"


vector<int> findAllDigitsInLine(string &s) {
    string digit;
    vector<int> digits;
    for (char c : s) {
        if (isdigit(c)) {
            cout << "adding " << c << " to current digit" << "\n";
            digit.push_back(c);
        } else {
            if (!digit.empty()) {
                int parsedDigit = stoi(digit);
                digits.push_back(parsedDigit);
                cout << "adding digit: " << parsedDigit << "\n";
            }
            digit = "";
        }
    }
    if (!digit.empty()) {
        int parsedDigit = stoi(digit);
        digits.push_back(parsedDigit);
        cout << "adding digit: " << parsedDigit << "\n";
    }
    return digits;
}

vector<char> findAllDigitsInLine2(string &s) {
    vector<char> digits;
    for (char c : s) {
        if (isdigit(c)) {
            cout << "adding " << c << " to digits" << "\n";
            digits.push_back(c);
        }
    }
    return digits;
}

vector<char> findAllDigitsInLine3(string &s) {
    vector<char> digits;
    for (char c : s) {
        if (isdigit(c)) {
            cout << "adding " << c << " to digits" << "\n";
            digits.push_back(c);
        }
    }
    return digits;
}

string isLetterDigit(string &s) {

}

void calibration::run() {
    vector<string> lines = (new readData())->getFileContent("../2023/1/input.txt");

    int total = 0;
    for (string& line : lines ) {
        cout << "finding digits in line: " << line << "\n";
        vector<char> numbersInLine = findAllDigitsInLine2(line);

        for (int i : numbersInLine) {
            cout << "number: " << i << "\n";
        }

        char first = numbersInLine[0];
        char last = numbersInLine[numbersInLine.size()-1];

        cout << "First: " << first << "\n";
        cout << "Last: " << last << "\n";

        string digit;
        digit.push_back(first);
        digit.push_back(last);
        total += stoi(digit);
    }

    cout << "Total: " << total << "\n";
}

