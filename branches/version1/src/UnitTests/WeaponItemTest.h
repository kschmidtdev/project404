#ifndef __WEAPONITEMTEST_H
#define __WEAPONITEMTEST_H

#include <cxxtest/TestSuite.h>

#include <../GameEngine/WeaponItem.h>

//
// A generated test suite: Just write tests!
//

class WeaponItemTest : public CxxTest::TestSuite
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

    void TestWeaponFunctions()
    {
        //Test creation and get
        WeaponItem weapon("SWORD", 2);
        TS_ASSERT_EQUALS(weapon.GetName(), "SWORD");
        TS_ASSERT_EQUALS(weapon.GetAttr(), 2);
    }

};


#endif // __WEAPONITEMTEST_H

