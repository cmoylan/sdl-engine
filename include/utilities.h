#pragma once

#include <iostream>

using namespace std;

namespace Utilities {
    
    /**
     * Print the members of a collection to stdout
     */
    template<class Iterable>
    void printCollection(Iterable collection)
    {
        for (auto member : collection) {
            cout << member << ", ";
        }
        cout << endl;
    }
}
