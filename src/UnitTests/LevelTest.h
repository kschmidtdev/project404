#ifndef __LEVELTEST_H
#define __LEVELTEST_H

#include <cxxtest/TestSuite.h>

#include <GameEngine/Level.h>

//
// A generated test suite: Just write tests!
//

class LevelTest : public CxxTest::TestSuite
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

    void testLevelState()
    {
        // Testing these enum values is bad if they are changed, but then the unit tests
        // should
        Level levelDefaultConstructor;
        TS_ASSERT_LESS_THAN_EQUALS( levelDefaultConstructor.ReturnState(), Level::ATTACK );
        TS_ASSERT_LESS_THAN_EQUALS( 0, levelDefaultConstructor.ReturnState() );

        vector<Character*> party;
        vector<Point> start;
        Level levelBigConstructor( party, party, start, NULL );
        TS_ASSERT_LESS_THAN_EQUALS( levelBigConstructor.ReturnState(), Level::ATTACK );
        TS_ASSERT_LESS_THAN_EQUALS( 0, levelBigConstructor.ReturnState() );

        Level levelDatabaseLoading( 0 );
        TS_ASSERT_LESS_THAN_EQUALS( levelDatabaseLoading.ReturnState(), Level::ATTACK );
        TS_ASSERT_LESS_THAN_EQUALS( 0, levelDatabaseLoading.ReturnState() );
    }

};


#endif // __LEVELTEST_H

