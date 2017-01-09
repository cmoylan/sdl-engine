#pragma once

#include <iostream>

using namespace std;

namespace Utilities {
    
    /**
     * Print the members of a collection to stdout
     * @param collection an instance of something that is iterable
     */
    template<class Iterable>
    void printCollection(Iterable collection)
    {
        for (const auto& member : collection) {
            cout << member << ", ";
        }
        cout << endl;
    }
}
