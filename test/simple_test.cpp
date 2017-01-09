#include <list>

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

#include "Level.h"

class Level;

using namespace std;

//TEST_CASE( "Factorials are computed", "[factorial]" ) {
//  SECTION("doing stuff") {
//      REQUIRE( Factorial(1) == 1 );
//      REQUIRE( Factorial(2) == 2 );
//      REQUIRE( Factorial(3) == 6 );
//      REQUIRE( Factorial(10) == 3628800 );
//  }
//}

void compareCollections(list<int> expected, list<int> actual)
{
  REQUIRE(expected.size() == actual.size());
  for (auto member : actual) {
    REQUIRE(member == expected.front());
    expected.pop_front();
  }
}

TEST_CASE( "#tilesOnScreen", "[level]" ) {
  Level level;
  level.loadFromJson("Test Level 2");
  level.tilesOnScreenX = 2;
  level.tilesOnScreenY = 2;

  SECTION("with no offset") {
    list<int> expected = { 0, 1, 2,
			   20, 21, 22,
			   40, 41, 42 };
    auto result = level.tilesOnScreen();
    compareCollections(expected, result);
  }

  SECTION("with an offset smaller than tile size") {
    list<int> expected = { 0, 1, 2, 20, 21, 22, 40, 41, 42 };
    level.offsetX = 9;
    level.offsetY = 9;
    auto result = level.tilesOnScreen();
    compareCollections(expected, result);
  }

  SECTION("with an offset larger than the tile size") {
    list<int> expected1 = { 1,2,3, 21, 22, 23, 41, 42, 43 };
    level.offsetX = level.pixelsPerTileX + 1;
    level.offsetY = level.pixelsPerTileY + 1;
    auto result = level.tilesOnScreen();
    compareCollections(expected1, result);

    level.offsetX = (2 * level.pixelsPerTileX) + 1;
    list<int> expected2 = { 2,3,4, 22,23,24, 42,43,44};
    result = level.tilesOnScreen();
    compareCollections(expected2, result);
  }
}
