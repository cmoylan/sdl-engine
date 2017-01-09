#pragma once

#include <iostream>

using namespace std;

namespace Utilities {
    
    /**
     * Print the members of a collection to stdout
     */
    void printCollection(auto collection)
    {
        for (auto member : collection) {
            cout << member << ", ";
        }
        cout << endl;
    }
}