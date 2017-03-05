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
 
    /**
     * Return the max of 2 numbers
     */
    inline int max(int a, int b)
    {
        return (a >= b) ? a : b;
    }
    
    /**
     * 
     */
    inline int differenceToOrigin(int number, int difference, int origin = 0) 
    {
        if (number < origin) {
            return number + difference;
        }
        else if (number > origin) {
            return number - difference;
        }
        return number;
    }
    
}
