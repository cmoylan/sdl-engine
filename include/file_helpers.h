#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

namespace FileHelpers {

    /**
     * Return the contents of a file as a string
     * @param filename The file to load
     * @return a string composed of the contents of the file
     */
    inline string loadStringFromFile(const string& filename)
    {
        stringstream sstr;
        ifstream file(filename);

         if (file.is_open()) {
             sstr << file.rdbuf();
             file.close();
             return sstr.str();
         }
         else {
             cout << "ERROR: unable to open file: " << filename << endl;
             return "";
         }
     }

}