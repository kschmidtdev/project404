#ifndef __ARCHERTEST_H
#define __ARCHERTEST_H

#include <cxxtest/TestSuite.h>

#include <Point.h>
#include <../GameEngine/Archer.h>

//
// A generated test suite: Just write tests!
//

class ArcherTest : public CxxTest::TestSuite
{
private:
// any variables that could be shared between tests
    Archer archer;
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
        archer.LevelUp();
        TS_ASSERT_EQUALS(archer.GetLevel(), 2);
        TS_ASSERT_EQUALS(archer.GetAttr(Character::POW), 3);
        TS_ASSERT_EQUALS(archer.GetAttr(Character::AGI), 8);
        TS_ASSERT_EQUALS(archer.GetAttr(Character::DEF), 4);
        TS_ASSERT_EQUALS(archer.GetHP(), 4);
        TS_ASSERT_EQUALS(archer.GetMaxHP(), 4);
    }

    //Test that all points are as they should be, test there are no more or less then should be
    void TestCalcAction()
    {
        vector<Point> points = archer.CalcAction();
        vector<Point>::iterator iter;
        iter = points.begin();
        TS_ASSERT_EQUALS((*iter), Point(-1, -1));
        iter++;
        TS_ASSERT_EQUALS((*iter), Point(1, 1));
        iter++;
        TS_ASSERT_EQUALS((*iter), Point(1, -1));
        iter++;
        TS_ASSERT_EQUALS((*iter), Point(-1, 1));
        iter++;
        TS_ASSERT_EQUALS((*iter), Point(-2, 0));
        iter++;
        TS_ASSERT_EQUALS((*iter), Point(2, 0));
        iter++;
        TS_ASSERT_EQUALS((*iter), Point(0, -2));
        iter++;
        TS_ASSERT_EQUALS((*iter), Point(0, 2));
        iter++;
        TS_ASSERT_EQUALS(iter, points.end());
    }

};


#endif // __ARCHERTEST_H

