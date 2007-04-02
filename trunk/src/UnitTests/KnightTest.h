#ifndef __KNIGHTTEST_H
#define __KNIGHTTEST_H

#include <cxxtest/TestSuite.h>

#include <GameEngine/Knight.h>

//
// A generated test suite: Just write tests!
//

class KnightTest : public CxxTest::TestSuite
{
private:
// any variables that could be shared between tests
    Knight knight;
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

    //Testing that level up correctly sets new values
    void TestLevelUp()
    {
        knight.LevelUp();
        TS_ASSERT_EQUALS(knight.GetLevel(), 2);
        TS_ASSERT_EQUALS(knight.GetAttr(Character::POW), 5);
        TS_ASSERT_EQUALS(knight.GetAttr(Character::AGI), 6);
        TS_ASSERT_EQUALS(knight.GetAttr(Character::DEF), 6);
        TS_ASSERT_EQUALS(knight.GetHP(), 8);
        TS_ASSERT_EQUALS(knight.GetMaxHP(), 8);
    }

    //Test that all points are as they should be, test there are no more or less then should be
    void TestCalcAction()
    {
        vector<Point> points = knight.CalcAction();
        vector<Point>::iterator iter;
        iter = points.begin();
        TS_ASSERT_EQUALS((*iter), Point(-1, 0));
        iter++;
        TS_ASSERT_EQUALS((*iter), Point(1, 0));
        iter++;
        TS_ASSERT_EQUALS((*iter), Point(0, -1));
        iter++;
        TS_ASSERT_EQUALS((*iter), Point(0, 1));
        iter++;
        TS_ASSERT_EQUALS(iter, points.end());
    }

};


#endif // __KNIGHTTEST_H

