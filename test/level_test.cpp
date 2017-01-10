#include <iostream>
#include <list>

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

#include "Level.h"

using namespace std;

class Level;

// SCENARIO("Level stuff", "[level]" ) {
//     GIVEN( "A vector with some items" ) {
//         WHEN( "the size is increased" ) {
//             Level level;
//             level.loadFromJson("Test Level 2");
// 
//             THEN( "the size and capacity change" ) {
//                 level.printPlatforms();
//                 REQUIRE( 1 == 1 );
//                 REQUIRE( 2 == 2 );
//             }
//         }
//     }
// }

TEST_CASE("#scroll_by", "[level]") {
    SECTION("scrolls the level") {
        Level level;
        level.loadFromJson("Test Level 2");
        //level.
        REQUIRE(level.offsetX == 0);
        REQUIRE(level.offsetY == 0);
        
        level.scrollBy(10, 10);
        REQUIRE(level.offsetX == 10);
        REQUIRE(level.offsetY == 10);
    }
}

void compareTiles(auto expected, auto given) {
        REQUIRE(expected.size() == given.size());
        
        for (auto tile : expected) {
            REQUIRE(tile == given.front());
            given.pop_front();
        }
}


TEST_CASE("#tilesOnScreen", "[level]") {
    Level level;
    level.loadFromJson("Test Level 2");
    level.tilesOnScreenX = 2;
    level.tilesOnScreenY = 2;
    
    SECTION("returns the tiles in the current sector") {
        list<int> expected = { 0, 1, 2, 
                               20, 21, 22,
                               40, 41, 42 };
        auto result = level.tilesOnScreen();
        compareTiles(expected, result);
    }
    
    SECTION("returns correct tiles when level is offset") {
        level.scrollBy(10, 10);
        list<int> expected = { 1, 2, 3, 
                               21, 22, 23,
                               41, 42, 43 };
        auto result = level.tilesOnScreen();
        compareTiles(expected, result);
    }
}