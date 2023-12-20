//
// Created by Nisse on 2022-12-18.
//
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <map>
#include <set>

using namespace std;
#include "day3.h"

// Lowercase item types a through z have priorities 1 through 26.
// Uppercase item types A through Z have priorities 27 through 52.

struct Rucksack {
    map<char, int> comp1;
    map<char, int> comp2;
};

struct Group {
    Rucksack r1;
    Rucksack r2;
    Rucksack r3;
};

void fillCompartment(string s, map<char, int> &compartment) {
    for (char c : s) {
        if (compartment.find(c) == compartment.end()) {
            // No such element
            compartment.insert(pair<char, int>{c, 1});
        } else {
            compartment[c]++;
        }
    }
}

int evalateChar(char c) {
    int lowerCaseValue = (int) c - 96;
    if (lowerCaseValue < 0) {
        return (int) c - (65 - 27);
    }
    return lowerCaseValue;
}

int evaluateDoubles(Rucksack rucksack) {
    int valueDoubleItems = 0;
    for (pair<char, int> item : rucksack.comp1) {
        if (rucksack.comp2.find(item.first) != rucksack.comp2.end()) {
            valueDoubleItems += evalateChar(item.first);
        }
    }
    return valueDoubleItems;
}

set<char> getRucksackItemSet(Rucksack rucksack) {
    set<char> items{};
    for (pair<char, int> p : rucksack.comp1) {
        items.insert(p.first);
    }

    for (pair<char, int> p : rucksack.comp2) {
        items.insert(p.first);
    }
    
    return items;
}

int findAndEvaluateBadge(const Group& group) {
    const set<char> &i1 = getRucksackItemSet(group.r1);
    const set<char> &i2 = getRucksackItemSet(group.r2);
    const set<char> &i3 = getRucksackItemSet(group.r3);

    char badge;
    for (char item : i1) {
        if (i2.find(item) != i2.end() && i3.find(item) != i3.end()) {
            badge = item;
            break;
        }
    }
    return evalateChar(badge);
}

vector<Rucksack> readData3() {
    ifstream myfile;
    myfile.open("../3/input.txt");
    string myline;
    vector<Rucksack> rucksacks = vector<Rucksack>{};
    if ( myfile.is_open() ) {
        while ( myfile && !myfile.eof() ) { // equivalent to myfile.good()
            getline (myfile, myline);
            //cout << myline << "\n";
            Rucksack rucksack{};
            myline.size();
            string comp1 = myline.substr(0, myline.size()/2);
            string comp2 = myline.substr(myline.size()/2, myline.size());
            fillCompartment(comp1, rucksack.comp1);
            fillCompartment(comp2, rucksack.comp2);
            rucksacks.push_back(rucksack);
        }
    } else {
        cout << "Couldn't open file\n";
    }
    return rucksacks;
}

int day3() {
    const vector<Rucksack> rucksacks = readData3();
    int valueOfAllDoubleItems = 0;
    for (const Rucksack& rucksack : rucksacks) {
        valueOfAllDoubleItems += evaluateDoubles(rucksack);
    }

    vector<Group> groups{};
    for (int i = 0; i < rucksacks.size() - 2; i += 3) {
        Group group{};
        group.r1 = rucksacks[i];
        group.r2 = rucksacks[i+1];
        group.r3 = rucksacks[i+2];

        groups.push_back(group);
    }

    int valueOfBadges = 0;
    for (Group group : groups) {
        valueOfBadges += findAndEvaluateBadge(group);
    }

    cout << "Total value of all double items: " << valueOfAllDoubleItems << "\n";

    cout << "The total value of all badges are: " << valueOfBadges << "\n";
    return 0;
}

/*
 * Del 2, gruppera ryggsäckarna i grupper om 3. Ta reda på sen vilket item som alla tre ryggsäckar har gemensamt. Hur kollar man det enklast... För varje item, kolla om nån av de andras ryggsäckar innehåller det, tills båda lookups ger tillbaks sant? Ja.
 */