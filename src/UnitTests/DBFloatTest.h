#ifndef __DBFLOATTEST_H
#define __DBFLOATTEST_H

#include <cxxtest/TestSuite.h>

#include <Database/DBFloat.h>

//
// A generated test suite: Just write tests!
//

class DBFloatTest : public CxxTest::TestSuite
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
        DBFloat pFloat(123456, "One Point One", 1.1 );

        TS_ASSERT_EQUALS( pFloat.GetUniqueID(), 123456 );
    }

    void testGetName()
    {
        DBFloat pFloat(123456, "One Point One", 1.1 );

        TS_ASSERT_EQUALS( pFloat.GetName(), "One Point One" );
    }

    void testGetData()
    {
        DBFloat pFloat(123456, "One Point One", 1.1F );

        TS_ASSERT_EQUALS( pFloat.GetData(), 1.1F );
    }

    void testGetType()
    {
        DBFloat pFloat(123456, "One Point One", 1.1F );

        TS_ASSERT_EQUALS( pFloat.GetType(), "DBFloat" );
    }

};


#endif // __DBFLOATTEST_H

