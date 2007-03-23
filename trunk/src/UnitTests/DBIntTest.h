#ifndef __DBINTTEST_H
#define __DBINTTEST_H

#include <cxxtest/TestSuite.h>

#include <Database/DBInt.h>

//
// A generated test suite: Just write tests!
//

class DBIntTest : public CxxTest::TestSuite
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

    void testGetUniqueID()
    {
        DBInt pInt(101010, "Ten", 11);

        TS_ASSERT_EQUALS( pInt.GetUniqueID(), 101010 );
    }

    void testGetName()
    {
        DBInt pInt(101010, "Ten", 11);

        TS_ASSERT_EQUALS( pInt.GetName(), "Ten" );
    }

    void testGetData()
    {
        DBInt pInt(101010, "Ten", 11);

        TS_ASSERT_EQUALS( pInt.GetData(), 11 );
    }

    void testGetType()
    {
        DBInt pInt(101010, "Ten", 11);

        TS_ASSERT_EQUALS( pInt.GetType(), "DBInt" );
    }
};


#endif // __DBINTTEST_H

