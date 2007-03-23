#ifndef __DBSTRINGTEST_H
#define __DBSTRINGTEST_H

#include <cxxtest/TestSuite.h>

#include <Database/DBString.h>

//
// A generated test suite: Just write tests!
//

class DBStringTest : public CxxTest::TestSuite
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
        DBString pString(908900, "Test String", "This is so correct" );

        TS_ASSERT_EQUALS( pString.GetUniqueID(), 908900 );
    }

    void testGetName()
    {
        DBString pString(908900, "Test String", "This is so correct" );

        TS_ASSERT_EQUALS( pString.GetName(), "Test String" );
    }

    void testGetData()
    {
        DBString pString(908900, "Test String", "This is so correct" );

        TS_ASSERT_EQUALS( pString.GetData(), "This is so correct" );
    }

    void testGetType()
    {
        DBString pString(908900, "Test String", "This is so correct" );

        TS_ASSERT_EQUALS( pString.GetType(), "DBString" );
    }

};


#endif // __DBSTRINGTEST_H

