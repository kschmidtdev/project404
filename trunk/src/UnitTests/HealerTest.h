#ifndef __HEALERTEST_H
#define __HEALERTEST_H

#include <cxxtest/TestSuite.h>

#include <GameEngine/Healer.h>

//
// A generated test suite: Just write tests!
//

class HealerTest : public CxxTest::TestSuite
{
private:
// any variables that could be shared between tests
    Healer healer;
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
        healer.LevelUp();
        TS_ASSERT_EQUALS(healer.GetLevel(), 2);
        TS_ASSERT_EQUALS(healer.GetAttr(Character::POW), 5);
        TS_ASSERT_EQUALS(healer.GetAttr(Character::AGI), 5);
        TS_ASSERT_EQUALS(healer.GetAttr(Character::DEF), 2);
        TS_ASSERT_EQUALS(healer.GetHP(), 3);
        TS_ASSERT_EQUALS(healer.GetMaxHP(), 3);
    }

    //Test that all points are as they should be, test there are no more or less then should be
    void TestCalcAction()
    {
        vector<Point> points = healer.CalcAction();
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


#endif // __HEALERTEST_H

