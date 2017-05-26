#pragma once

#include <iostream>
#include <string>

using namespace std;

class Terminal {
public:
    string header = "Ready.\n> ";
    string command;

    //void pressChar(string character);

    string text();

    void addChar(string character);
    void backspace();
    void clear();
    void runCommand();

};