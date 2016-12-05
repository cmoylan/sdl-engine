#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>


namespace FileHelpers {

    /**
     * Return a file as a string
     * @param filename The file to load
     * @return a string composed of the contents of the file
     */
    inline std::string loadStringFromFile(const std::string& filename)
    {
        std::stringstream sstr;
        std::ifstream file;

        file.open(filename.c_str(), std::ifstream::in);

        if (file.is_open()) {
            sstr << file.rdbuf();
            return sstr.str();
        }
        else {
            std::cout << "ERROR: unable to open file: " << filename << std::endl;
            return "";
        }
    };

}