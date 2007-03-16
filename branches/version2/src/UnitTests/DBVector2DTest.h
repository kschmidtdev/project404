#ifndef __DBVECTOR2DTEST_H
#define __DBVECTOR2DTEST_H

#include <cxxtest/TestSuite.h>

#include <../Database/DBVector2D.h>

//
// A generated test suite: Just write tests!
//

class DBVector2DTest : public CxxTest::TestSuite
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
        int xy[2] = { 5, 4 };
        DBVector2D pVector2D(454555, "newVector2D", xy );

        TS_ASSERT_EQUALS( pVector2D.GetUniqueID(), 454555 );
    }

    void testGetName()
    {
        int xy[2] = { 5, 4 };
        DBVector2D pVector2D(454555, "newVector2D", xy );

        TS_ASSERT_EQUALS( pVector2D.GetName(), "newVector2D" );
    }

    void testGetData()
    {
        int xy[2] = { 5, 4 };
        DBVector2D pVector2D(454555, "newVector2D", xy );

        TS_ASSERT_EQUALS( pVector2D.GetData()[0], 5 );
        TS_ASSERT_EQUALS( pVector2D.GetData()[1], 4 );
    }

    void testGetX()
    {
        int xy[2] = { 5, 4 };
        DBVector2D pVector2D(454555, "newVector2D", xy );

        TS_ASSERT_EQUALS( pVector2D.GetX(), 5 );
    }

    void testGetY()
    {
        int xy[2] = { 5, 4 };
        DBVector2D pVector2D(454555, "newVector2D", xy );

        TS_ASSERT_EQUALS( pVector2D.GetY(), 4 );
    }

    void testGetType()
    {
        int xy[2] = { 5, 4 };
        DBVector2D pVector2D(454555, "newVector2D", xy );

        TS_ASSERT_EQUALS( pVector2D.GetType(), "DBVector2D" );
    }

};


#endif // __DBVECTOR2DTEST_H

