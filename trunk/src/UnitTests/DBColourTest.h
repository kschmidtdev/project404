#ifndef __DBCOLOURTEST_H
#define __DBCOLOURTEST_H

#include <cxxtest/TestSuite.h>

#include <Database/DBColour.h>

//
// A generated test suite: Just write tests!
//

class DBColourTest : public CxxTest::TestSuite
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
        int RGB[3] = { 45, 20, 65 };
        DBColour pColour(7487777, "ColourSet", RGB );

        TS_ASSERT_EQUALS( pColour.GetUniqueID(), 7487777);
    }

    void testGetName()
    {
        int RGB[3] = { 45, 20, 65 };
        DBColour pColour(7487777, "ColourSet", RGB );

        TS_ASSERT_EQUALS( pColour.GetName(), "ColourSet" );
    }

    void testGetData()
    {
        int RGB[3] = { 45, 20, 65 };
        DBColour pColour(7487777, "ColourSet", RGB );

        TS_ASSERT_EQUALS( pColour.GetData()[0], 45 );
        TS_ASSERT_EQUALS( pColour.GetData()[1], 20 );
        TS_ASSERT_EQUALS( pColour.GetData()[2], 65 );
    }

    void testGetRed()
    {
        int RGB[3] = { 45, 20, 65 };
        DBColour pColour(7487777, "ColourSet", RGB );

        TS_ASSERT_EQUALS( pColour.GetRed(), 45 );
    }

    void testGetGreen()
    {
        int RGB[3] = { 45, 20, 65 };
        DBColour pColour(7487777, "ColourSet", RGB );

        TS_ASSERT_EQUALS( pColour.GetGreen(), 20 );
    }

    void testGetBlue()
    {
        int RGB[3] = { 45, 20, 65 };
        DBColour pColour(7487777, "ColourSet", RGB );

        TS_ASSERT_EQUALS( pColour.GetBlue(), 65 );
    }

    void testGetType()
    {
        int RGB[3] = { 45, 20, 65 };
        DBColour pColour(7487777, "ColourSet", RGB );

        TS_ASSERT_EQUALS( pColour.GetType(), "DBColour" );
    }


};


#endif // __DBCOLOURTEST_H

