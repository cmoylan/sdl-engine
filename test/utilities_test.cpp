#include <iostream>
#include <list>

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "catch.hpp"
#include "utilities.h"

using namespace std;

void compareCollections(list<int> expected, list<int> actual)
{
    REQUIRE(expected.size() == actual.size());
    for (auto member : actual) {
        REQUIRE(member == expected.front());
        expected.pop_front();
    }
}

TEST_CASE("#differenToOrigin", "[utilities]")
{
    REQUIRE(Utilities::differenceToOrigin(10, 5) == 5);
    REQUIRE(Utilities::differenceToOrigin(0, 9) == 0);
    REQUIRE(Utilities::differenceToOrigin(-10, 9) == -1);
    REQUIRE(Utilities::differenceToOrigin(0, 1) == 0);


    //SECTION("with an offset smaller than tile size") {
    //    list<int> expected = { 0, 1, 2,
    //                           20, 21, 22,
    //                           40, 41, 42
    //                         };
    //    level.offsetX = PIXELS_PER_TILE_X - 1;
    //    level.offsetY = 9;
    //    auto result = level.layerIndicesOnScreen();
    //    compareCollections(expected, result);
    //}
    //
    //SECTION("with an offset larger than or equal to the tile size") {
    //    list<int> expected = { 21, 22, 23, 41, 42, 43, 61, 62, 63 };
    //    level.offsetX = PIXELS_PER_TILE_X + 1;
    //    level.offsetY = PIXELS_PER_TILE_Y;
    //    auto result = level.layerIndicesOnScreen();
    //    compareCollections(expected, result);
    //}
    //
    //SECTION("with just an x offset") {
    //    level.offsetX = (2 * PIXELS_PER_TILE_X) + 1;
    //    list<int> expected = { 2, 3, 4, 22, 23, 24, 42, 43, 44} ;
    //    auto result = level.layerIndicesOnScreen();
    //    compareCollections(expected, result);
    //};
    //
    //SECTION("with just a y offset") {
    //    list<int> expected = { 40, 41, 42, 60, 61, 62, 80, 81, 82 };
    //    level.offsetX = 0;
    //    level.offsetY = (2 * PIXELS_PER_TILE_Y) + 1;
    //    auto result = level.layerIndicesOnScreen();
    //    compareCollections(expected, result);
    //}
}
