#ifndef __ARMORITEMTEST_H
#define __ARMORITEMTEST_H

#include <cxxtest/TestSuite.h>

#include <GameEngine/ArmorItem.h>

//
// A generated test suite: Just write tests!
//

class ArmorItemTest : public CxxTest::TestSuite
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

    void TestArmorFunctions()
    {
        //Test creation and get
        ArmorItem armor("SHIELD", 2);
        TS_ASSERT_EQUALS(armor.GetName(), "SHIELD");
        TS_ASSERT_EQUALS(armor.GetAttr(), 2);
    }

};


#endif // __ARMORITEMTEST_H

