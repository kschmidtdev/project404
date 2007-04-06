#ifndef __DBENGINETEST_H
#define __DBENGINETEST_H

#include <cxxtest/TestSuite.h>

#include <Database/DBEngine.h>
#include <Logger.h>
#include <SecurityManager.h>

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
        Logger::GetInstance( "dbEngineUnitTestLog.txt" );
        Logger::GetInstance()->Initialize();

        SecurityManager::GetInstance()->Initialize();
        SecurityManager::GetInstance()->LoadPasswordHashFile( "passwords" );
        DBEngine::GetInstance()->Initialize();
    }

    // Called after all unit tests in this suite, remove if note needed
    void tearDown()
    {
        DBEngine::GetInstance()->Shutdown();
        DatabaseManager::GetInstance()->Shutdown();
        SecurityManager::GetInstance()->Shutdown();
        Logger::GetInstance()->Shutdown();
    }

    void testLoadParties()
    {
        vector<Character*>* PartyList = DBEngine::GetInstance()->LoadParty( 1 );

        TS_ASSERT_EQUALS( PartyList->size(), 4 ); // size of the vector should be 4.
    }

    void testLoadEnemies()
    {
        vector<Character*>* EnemiesList = DBEngine::GetInstance()->LoadEnemies( 4 );

        TS_ASSERT_EQUALS( EnemiesList->size(), 6 ); // size of the vector should be 6.
    }

    void testLoadBattleMap()
    {
        vector<Tile> testMap( DBEngine::GetInstance()->LoadBattleMap( 1 ) );

        TS_ASSERT_EQUALS( testMap.size(), 100 ); // size of the vector should be 1.
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

