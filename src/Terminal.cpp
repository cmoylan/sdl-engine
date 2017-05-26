#include "Terminal.h"

// void Terminal::pressChar(string character)
// {
//     cout << character << endl;
//     if (character == "Return") {
//         runCommand();
//     }
//     else if (character == "Backspace") {
//         backspace();
//     }
//     else {
//         addChar(character);
//     }
// }


void Terminal::addChar(string character)
{
    command.append(character);
}


void Terminal::backspace()
{
    if (command.length() > 0) {
        command.pop_back();
    }
}


void Terminal::clear()
{
    command.clear();
}


void Terminal::runCommand()
{
    // add command to history
    // execute command
    // append execution result to history
    // display command prompt
    
    clear();
    
}


string Terminal::text()
{
    return header + command;
}
