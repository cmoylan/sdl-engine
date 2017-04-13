#pragma once

#include <cstdlib>
#include <set>

using namespace std;

static set<int> uuids;

const int MAX_UUID = 1000;

inline int generateUuid()
{
    int number;

    while (true) {
        number = rand() % MAX_UUID;
        if (uuids.find(number) == uuids.end()) {
            uuids.insert(number);
            return number;
        }
    }
}