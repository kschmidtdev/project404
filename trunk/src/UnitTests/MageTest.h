#ifndef __MAGETEST_H
#define __MAGETEST_H

#include <cxxtest/TestSuite.h>

#include <../GameEngine/Mage.h>

//
// A generated test suite: Just write tests!
//

class MageTest : public CxxTest::TestSuite
{
private:
// any variables that could be shared between tests
    Mage mage;
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
        mage.LevelUp();
        TS_ASSERT_EQUALS(mage.GetLevel(), 2);
        TS_ASSERT_EQUALS(mage.GetAttr(Character::POW), 7);
        TS_ASSERT_EQUALS(mage.GetAttr(Character::AGI), 5);
        TS_ASSERT_EQUALS(mage.GetAttr(Character::DEF), 2);
        TS_ASSERT_EQUALS(mage.GetHP(), 2);
        TS_ASSERT_EQUALS(mage.GetMaxHP(), 2);
    }

    //Test that all points are as they should be, test there are no more or less then should be
    void TestCalcAction()
    {
        vector<Point> points = mage.CalcAction();
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


#endif // __MAGETEST_H

