#ifndef __ITEMTEST_H
#define __ITEMTEST_H

#include <cxxtest/TestSuite.h>

#include <../GameEngine/Item.h>

//
// A generated test suite: Just write tests!
//

class ItemTest : public CxxTest::TestSuite
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

    void TestItemFunctions()
    {
        Item item;
        //Test default
        TS_ASSERT_EQUALS(item.GetName(), "Base");
        TS_ASSERT_EQUALS(item.GetAttr(), 1);
    }

};


#endif // __ITEMTEST_H

