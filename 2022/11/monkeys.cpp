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
#include <functional>

using namespace std;
#include "monkeys.h"


struct Monkey {
    vector<unsigned long long> items;
    function<unsigned long long(unsigned long long, unsigned long long)> function;
    string rightHandOfFuntion;
    int testDivisible;
    int throwsToTrue;
    int throwsToFalse;
    unsigned long long inspects = 0;

    bool operator > (const Monkey& monkey) const
    {
        return (inspects > monkey.inspects);
    }
};

long moduloFactor = 1;

bool debug = false;

int rounds = 10000;

void startThrowing(vector<Monkey> &monkies) {
    for (int i = 0; i < rounds; i++) {
        for (int m = 0; m < monkies.size(); m++) {
            Monkey &monkey = monkies[m];
            if (debug) {cout << "Monkey " << m << "\n";}
            for (unsigned long long item : monkey.items) {
                if (debug) {cout << "   Inspecting item with value " << item << "\n";}
                monkey.inspects++;
                unsigned long long level;
                if (monkey.rightHandOfFuntion == "old") {
                    level = monkey.function(item, item);
                } else {
                    unsigned long long rightHandValue = stoi(monkey.rightHandOfFuntion);
                    level = monkey.function(item, rightHandValue);
                }

                if (debug) {cout << "   Increasing level to " << level << "\n";}

                //level = level / 3;
                level = (level % moduloFactor);

                //if (level > moduloFactor) {
                //    cout << "Level decreased from " << level << " to " << level%moduloFactor << " though modulo." << "\n";
                //    level = (level % moduloFactor); // Sätta ett tak baserat på alla tals faktorer? Alla test-tals då... Är modulo 11 korrekt om
                //}

                // 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71
                /*if (level % 23 == 0) {
                    cout << "Dividing level with prime factor 23\n";
                    level = level / 23;
                }
                if (level % 29 == 0) {
                    cout << "Dividing level with prime factor 29\n";
                    level = level / 29;
                }
                if (level % 31 == 0) {
                    cout << "Dividing level with prime factor 31\n";
                    level = level / 31;
                }*/

                // talet innan modulots en faktor av 11?
                // test: 110 är delbart på 11, 110%11=0. Vad händer om jag delar 110 på en faktor av 11? Typ 11*2=22.
                //

                if (level % monkey.testDivisible == 0) {
                    // Throw to true-monkey
                    monkies[monkey.throwsToTrue].items.push_back(level);
                    if (debug) {cout << "   test is true, monkey " << m << " throws item " << item << " with new value of " << level << " to monkey " << monkey.throwsToTrue << ".\n";}
                } else {
                    // Throw to false-monkey
                    monkies[monkey.throwsToFalse].items.push_back(level);
                    if (debug) {cout << "   test is false, monkey " << m << " throws item " << item << " with new value of " << level << " to monkey " << monkey.throwsToFalse << ".\n";}

                }
            }
            monkey.items.clear();
        }
        if (debug) {
            cout << "round " << i+1 << " complete.\n";
            cout << "Item status: " << "\n";
            for (int i = 0; i < monkies.size(); i++) {
                cout << "Monkey " << i << ": ";
                for (int item : monkies[i].items) {
                    cout << item << ", ";
                }
                cout << "\n";
            }
            cout << "\n";
            cout << "===========" << "\n";
            cout << "\n";
        }
    }
}

void monkeys::readData() {
    ifstream myfile;
    myfile.open("../11/input.txt");
    string myline;
    if ( myfile.is_open() ) {
        vector<Monkey> monkies;
        // Keep a vector for each direction that for each index stores the highest tree yet. Will that do it?
        while (myfile && !myfile.eof()) { // equivalent to myfile.good()
            // monkey
            getline (myfile, myline);
            Monkey monkey{};
            cout << "monke: " << myline << "\n";
            // Items
            getline (myfile, myline);

            myline = myline.substr(myline.find("items:") + 7, myline.size());
            size_t pos;
            std::string token;
            string delimiter = ", ";
            cout << "items: ";
            cout << "starting items: " << myline << "\n";
            while ((pos = myline.find(delimiter)) != std::string::npos) {
                token = myline.substr(0, pos);
                std::cout << token << std::endl;
                monkey.items.push_back(stoi(token));
                myline.erase(0, pos + delimiter.length());
            }
            std::cout << myline << std::endl;
            monkey.items.push_back(stoi(myline));

            getline (myfile, myline);
            // operator
            pos = myline.find("old");
            myline = myline.substr(pos + 4, myline.size());
            cout << "operator?: " << myline << "\n";
            char op = myline[0];
            if (op == '*') {
                monkey.function = multiplies<unsigned long long>();
            } else if (op == '+') {
                monkey.function = plus<unsigned long long>();
            }

            monkey.rightHandOfFuntion = myline.substr(2, myline.size());

            getline (myfile, myline);
            // Test
            myline = myline.substr(21, myline.size());
            cout << "number to be divisible by: '" << myline << "'\n";
            monkey.testDivisible = stoi(myline);
            moduloFactor *= monkey.testDivisible;
            cout << "testProduct: " << moduloFactor << "\n";

            getline (myfile, myline);
            // Throw to monke if true
            myline = myline.substr(myline.find("monkey") + 7, myline.size());
            cout << "Throw to monke if true: " << myline << "\n";
            monkey.throwsToTrue = stoi(myline);

            getline (myfile, myline);
            myline = myline.substr(myline.find("monkey") + 7, myline.size());
            cout << "Throw to monke if false: " << myline << "\n";
            monkey.throwsToFalse = stoi(myline);

            monkies.push_back(monkey);
            getline (myfile, myline);
            // Empty line
        }
        cout << "have this many monkies: " << monkies.size() << "\n";

        cout << "Modulofactor = " << moduloFactor << "\n";

        startThrowing(monkies);

        for (int i = 0; i < monkies.size(); i++) {
            cout << "monkey " << i << " inspected items " << monkies[i].inspects << " number of times.\n";
        }

        sort(monkies.begin(), monkies.end(), greater<Monkey>());

        cout << "Monkey with most inspects: " << monkies[0].inspects << "\n";
        cout << "Monkey with most inspects: " << monkies[1].inspects << "\n";

        cout << "Multiple of the two with most inspects: " << monkies[0].inspects * monkies[1].inspects << "\n";

        /*
         * Solution part 1:
         *  Monkey with most inspects: 348
            Monkey with most inspects: 347
            Multiple of the two with most inspects: 120756
         */

    } else {
        cout << "derp file readings. \n";
    }
}

void monkeys::run() {
    readData();
}
