#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include "day1.h"

using namespace std;

struct Elf {
    vector<int> foods;
};

int sumElfFood(const Elf& elf) {
    int sum = 0;
    for (int food : elf.foods) {
        sum += food;
    }
    return sum;
}

bool compareElfs(const Elf& elf1, const Elf& elf2) {
    return sumElfFood(elf1) > sumElfFood(elf2);
}

int day1() {
    ifstream myfile;
    myfile.open("../1/input1_a.txt");
    string myline;
    vector<Elf> elfs = vector<Elf>{};
    vector<int> foods;
    int maxFood = 0;
    if ( myfile.is_open() ) {
        while ( myfile ) { // equivalent to myfile.good()
            getline (myfile, myline);
            //cout << myline << '\n';
            if (myline == "") {
                Elf elf;
                elf.foods = foods;
                elfs.push_back(elf);
                if (sumElfFood(elf) > maxFood) {
                    maxFood = sumElfFood(elf);
                }
                foods = vector<int>{};
                //cout << "linebreak\n";
            } else {
                foods.push_back(stoi(myline));
            }
        }
    }
    else {
        cout << "Couldn't open file\n";
    }
    cout << "maxFood: " << maxFood << "\n";

    sort(elfs.begin(), elfs.end(), compareElfs);

    cout << "Top three elf foods:\n";
    cout << sumElfFood(elfs[0]) << "\n";
    cout << sumElfFood(elfs[1]) << "\n";
    cout << sumElfFood(elfs[2]) << "\n";

    cout << "Sum of top three elfs food: " << sumElfFood(elfs[0]) + sumElfFood(elfs[1]) + sumElfFood(elfs[2]);

    return 0;
}
