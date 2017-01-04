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


  /**
   * Given a file path, return just the filename and extension
   * @param path The full or relative path to a file
   * @return a string that is the filename and extension
   */
  inline string filenameFromPath(const string& path) {
    // FIXME: this is not portable
    unsigned found = path.find_last_of("/\\");
    return path.substr(found+1);
  }
}
