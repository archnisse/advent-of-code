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
#include "day4.h"
using namespace std;

struct Range {
    int start;
    int end;
};

bool isOneRangeContained(Range r1, Range r2) {
    return (r1.start >= r2.start && r1.end <= r2.end) || (r2.start >= r1.start && r2.end <= r1.end);
}

bool doesRangesOverlap(Range r1, Range r2) {
    return !((r1.start < r2.start && r1.end < r2.start) || (r1.start > r2.end && r1.end > r2.end));
}

void day4::readData() {
    ifstream myfile;
    myfile.open("../4/input.txt");
    string myline;
    if ( myfile.is_open() ) {
        int containedRanges = 0;
        while ( myfile && !myfile.eof() ) { // equivalent to myfile.good()
            getline (myfile, myline);
            //cout << myline << "\n";

            unsigned long long int comma_index = myline.find(',');
            string first_range = myline.substr(0, comma_index);
            string second_range = myline.substr(comma_index + 1, myline.size() - comma_index + 1);
            Range range1{};
            range1.start = stoi(first_range.substr(0, first_range.find('-')));
            range1.end = stoi(first_range.substr(first_range.find('-') + 1, first_range.size() - first_range.find('-')));

            Range range2{};
            range2.start = stoi(second_range.substr(0, second_range.find('-')));
            range2.end = stoi(second_range.substr(second_range.find('-') + 1, second_range.size() - second_range.find('-')));

            //cout << range1.start << "-" << range1.end << "," << range2.start << "-" << range2.end << "\n";

           // cout << "Is range overlapping? : " << doesRangesOverlap(range1, range2) << "\n";

            if (doesRangesOverlap(range1, range2)) {
                containedRanges++;
            }

        }
        cout << "Overlapping ranges: " << containedRanges << "\n";
    } else {
        cout << "Couldn't open file\n";
    }
}

void day4::run() {
    readData();
}
