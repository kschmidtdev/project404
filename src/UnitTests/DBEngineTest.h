#ifndef __DBENGINETEST_H
#define __DBENGINETEST_H

#include <cxxtest/TestSuite.h>

#include <../Database/DBEngine.h>

//
// A generated test suite: Just write tests!
//

class DBEngineTest : public CxxTest::TestSuite
{
private:
// any variables that could be shared between tests

// Unit Tests:
public:

    // Called before all unit tests in this suite, remove if not needed
    void setUp()
    {
        Logger::GetInstance( "dbManagerUnitTestLog.txt" );
        Logger::GetInstance()->Initialize();

        DBEngine::GetInstance()->Initialize();
    }

    // Called after all unit tests in this suite, remove if note needed
    void tearDown()
    {
        DBEngine::GetInstance()->Shutdown();
        DatabaseManager::GetInstance()->Shutdown();
        Logger::GetInstance()->Shutdown();
    }

    void testLoadParties()
    {

    }

    void testLoadEnemies()
    {

    }

    void testLoadPartyStartingPoint()
    {
        Healer newCharacter("Han", 1, NULL, NULL);

    }

    void testLoadEnemiesStartingPoint()
    {
        Knight newCharacter("Enemy Boss", 1, NULL, NULL);
    }

    void testGetCharacterList()
    {
        TS_ASSERT( DBEngine::GetInstance()->GetCharacterList() );
    }

    void testGetItemList()
    {
        TS_ASSERT( DBEngine::GetInstance()->GetItemList() );
    }
};


#endif // __DBENGINETEST_H

