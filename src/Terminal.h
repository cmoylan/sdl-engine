#pragma once

#include <string>

class Terminal {
public:
    String command;

    void pressChar(String character);

    String draw();

private:
    void addChar(String character);
    void backspace();
    void clear();
    void runCommand();

};