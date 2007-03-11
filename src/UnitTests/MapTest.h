#ifndef __MAPTEST_H
#define __MAPTEST_H

#include <cxxtest/TestSuite.h>

#include <GameEngine/Map.h>

//
// A generated test suite: Just write tests!
//

class MapTest : public CxxTest::TestSuite
{
private:
// any variables that could be shared between tests

// Unit Tests:
public:

    // Called before all unit tests in this suite, remove if not needed
    void setUp()
    {

    }

    // Called after all unit tests in this suite, remove if note needed
    void tearDown()
    {

    }

    void TestMapAddAndGet()
    {

        Tile one(Point(0,0), "ONE");
        Tile two(Point(0,1), "TWO");
        vector<Tile> tiles;
        tiles.push_back(one);
        tiles.push_back(two);
        Map another(tiles);
        TS_ASSERT_EQUALS(another.GetTile(Point(0,1)).GetType(), "TWO");
        TS_ASSERT_EQUALS(another.GetTile(Point(0,0)).GetType(), "ONE");


    }

};


#endif // __MAPTEST_H

