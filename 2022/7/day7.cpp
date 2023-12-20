//
// Created by Nisse on 2022-12-20.
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
#include "day7.h"

struct File {
    int size;
    string name;
};

struct Folder {
    map<string, Folder> folders{};
    vector<File> files{};
    string name;
    Folder * parent{};
};

bool isLsCommand(string &s) {
    return (s.substr(0, 5)).find("ls") != -1 && s.substr(0, 1).find('$') != -1;
}

bool isCdCommadn(string &s) {
    return (s.substr(0, 5)).find("cd") != -1 && s.substr(0, 1).find('$') != -1;
}

bool isDirEntry(string &s) {
    return s.substr(0, 3).find("dir") != -1;
}

bool isFileEntry(string &s) {
    return isdigit(s[0]);
}

File readFile(string &s) {
    int fileSize = stoi(s.substr(0, s.find(' ')));
    string name = s.substr(s.find(' '), s.size());
    return File{fileSize, name};
}

int sizeOfFolder(Folder &f, int &size, int &closestYet) {
    int fileSize = 0;
    for (File &file : f.files) {
        cout << "checking size of file: " << file.name << ", it is: " << file.size << ".\n";
        fileSize += file.size;
    }
    int folderSize = 0;
    for (pair<string, Folder> folder : f.folders ) {
        folderSize += sizeOfFolder(folder.second, size, closestYet);
    }
    int totalSize = fileSize + folderSize;
    if (totalSize < 100000) {
        cout << "adding folder " << f.name << " to total size. " << " current Size: " << size << ", adding: " << totalSize << "\n";
        size += totalSize;
    }
    if (totalSize > 8381165 && totalSize < closestYet) {
        cout << "Setting closes yet from " << closestYet << " to " << totalSize << "\n";
        closestYet = totalSize;
    }
    return totalSize;
}

bool fileExists(vector<File> &files, string name) {
    for (File &file : files) {
        if (file.name == name) {
            return true;
        }
    }
    return false;
}

void day7::readData() {
    ifstream myfile;
    myfile.open("../7/input.txt");
    string myline;
    if ( myfile.is_open() ) {
        Folder root;
        root.name = "/";
        Folder * currentFolder = &root;
        int linenumber = 0;
        while ( myfile && !myfile.eof() ) { // equivalent to myfile.good()
            getline (myfile, myline);
            if (myline == "dir thf" || myline == "$ cd thf" || myline == "dir qgbg" || myline == "dir wfvqv") {
                cout << "herp\n";
            }
            linenumber++;
            cout << linenumber << " " << myline << "\n";
            if (myline.find("$ cd /") != -1 && currentFolder->name.find('/') != -1) {
                cout << "go to root as first argument.\n";
                continue;
            }
            if (isLsCommand(myline)) {
                cout << "was ls\n";
            } else if (isCdCommadn(myline)) {
                cout << "was cd: ";
                if (myline.find("..") != -1) {
                    currentFolder = currentFolder->parent;
                    cout << " go to above folder: " << currentFolder->name << "\n";
                } else if (myline.find("cd /") != -1) {
                    cout << "Error: Going to root again, shouldn't happen.\n";
                    currentFolder = &root;
                } else {
                    string newFolderName = myline.substr(5, myline.size());
                    if (currentFolder->folders.find(newFolderName) != currentFolder->folders.end()) {
                        currentFolder = &currentFolder->folders.find(newFolderName)->second;
                        cout << " Current folder set to new folder: " << currentFolder->name << "\n";
                    } else {
                        cout << "Error: Could not find folder to go to. Has it been read correctly?\n";
                    }
                    cout << "go to new folder " << newFolderName << ".\n";
                }
            } else if (isDirEntry(myline)){
                cout << "was Dir\n";
                string newFolderName = myline.substr(4, myline.size());
                if (currentFolder->folders.find(newFolderName) == currentFolder->folders.end()) {
                    auto * newFolder = new Folder;
                    newFolder->name = newFolderName;
                    newFolder->parent = currentFolder;
                    currentFolder->folders.insert(pair<string, Folder>(newFolderName, *newFolder));
                    cout << "new Dir '" << newFolderName << "' inserted into currentFolder: " << currentFolder->name << "\n";
                    if (newFolderName == "qgbg") {
                        cout << "wat in tarnation, address of newly created folder: " << newFolder << "\n";
                    }if (newFolderName != "qgbg") {
                        cout << "wat in non-tarnation, address of newly created folder: " << newFolder << "\n";
                    }
                } else {
                    cout << "New dir " << newFolderName << " was already present under folder " << currentFolder->name << ".\n";
                }
            } else if (isFileEntry(myline)) {
                cout << "was file\n";
                const File &file = readFile(myline);
                if (!fileExists(currentFolder->files, file.name)) {
                    currentFolder->files.push_back(file);
                }
            } else {
                cout << "Error: something else." << "\n";
            }

        }
        cout << "done." << "\n";
        int totalSize = 0;
        int closestYet = INT32_MAX;
        cout << "Size of root folder: " << sizeOfFolder(root, totalSize, closestYet) << "\n";
        cout << "totalSize: " << totalSize << "\n";
        cout << "best sized folder to delete: " << closestYet << "\n";
    } else {
        cout << "Couldn't open file\n";
    }
}

void day7::run() {
    readData();
}
