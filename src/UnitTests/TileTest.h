#ifndef __TILETEST_H
#define __TILETEST_H

#include <cxxtest/TestSuite.h>
#include <../Point.h>
#include <../GameEngine/Tile.h>

//
// A generated test suite: Just write tests!
//

class TileTest : public CxxTest::TestSuite
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

    void testYourFunctionNameHere()
    {
        //Test constructors and getters
        Tile tile;
        Tile constructed(Point(0,3), "GRASS");
        TS_ASSERT_EQUALS(tile.GetPoint(), Point(0,0));
        TS_ASSERT_EQUALS(constructed.GetPoint(), Point(0,3));
        TS_ASSERT_EQUALS(tile.GetWeight(), 2);
        TS_ASSERT_EQUALS(constructed.GetWeight(), 2);
        TS_ASSERT_EQUALS(tile.GetType(), "GRASS");
        TS_ASSERT_EQUALS(constructed.GetType(), "GRASS");

        //Test if not grass weight is different
        Tile another(Point(0,3), "NOTGRASS");
        TS_ASSERT_EQUALS(another.GetType(), "NOTGRASS");
        TS_ASSERT_EQUALS(another.GetWeight(), 2);
    }

};


#endif // __TILETEST_H

