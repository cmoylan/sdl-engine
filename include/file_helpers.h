#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

namespace FileHelpers {

    /**
     * Return a file as a string
     * @param filename The file to load
     * @return a string composed of the contents of the file
     */
    inline string loadStringFromFile(const auto& filename)
    {
        cout << "hey";
        stringstream sstr;
        ifstream file;
cout << "uhhh";
        file.open(filename.c_str());
cout << "what" ;
        if (file.is_open()) {
            sstr << file.rdbuf();
            return sstr.str();
        }
        else {
            cout << "ERROR: unable to open file: " << filename << endl;
            return "";
        }
    }

}