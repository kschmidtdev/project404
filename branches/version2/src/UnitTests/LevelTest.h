#ifndef __LEVELTEST_H
#define __LEVELTEST_H

#include <cxxtest/TestSuite.h>

#include <GameEngine/Level.h>
#include <Logger.h>
#include <GameEngine/Map.h>
#include <GameEngine/Character.h>
#include <Point.h>
#include <Database/DBEngine.h>
#include <SecurityManager.h>

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
        Logger::GetInstance( "unitTestLog.txt" );
        Logger::GetInstance()->Initialize();
        SecurityManager::GetInstance()->Initialize();
        SecurityManager::GetInstance()->LoadPasswordHashFile( "passwords" );
        DBEngine::GetInstance()->Initialize();
    }

    // Called after all unit tests in this suite, remove if note needed
    void tearDown()
    {
        DBEngine::GetInstance()->Shutdown();
        SecurityManager::GetInstance()->Shutdown();
        Logger::GetInstance()->Shutdown();
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
        Level levelBigConstructor( party, party, start);
        TS_ASSERT_LESS_THAN_EQUALS( levelBigConstructor.ReturnState(), Level::ATTACK );
        TS_ASSERT_LESS_THAN_EQUALS( 0, levelBigConstructor.ReturnState() );

        Level levelDatabaseLoading( 0 );
        TS_ASSERT_LESS_THAN_EQUALS( levelDatabaseLoading.ReturnState(), Level::ATTACK );
        TS_ASSERT_LESS_THAN_EQUALS( 0, levelDatabaseLoading.ReturnState() );
    }

    void testBasicOperations()
    {
        Level level( 0 );
        TS_ASSERT_EQUALS(level.GetTurn(), true);
        level.TakeTurn();
        TS_ASSERT_EQUALS(level.GetTurn(), false);
        level.TakeTurn();

        //nothing selected yet.
        TS_ASSERT(level.GetCurCharacter() == NULL);

        //Pull out party elements check
        vector<Character*> party = level.GetParty();
        vector<Character*>::iterator citer;
        citer = party.begin();
        TS_ASSERT_EQUALS((*citer)->GetName(), "Han");
        citer++;
        TS_ASSERT_EQUALS((*citer)->GetName(), "Karl");
        citer++;
        TS_ASSERT_EQUALS((*citer)->GetName(), "Mike");
        citer++;
        TS_ASSERT_EQUALS((*citer)->GetName(), "Andrew");
        citer++;
        //and that's all
        TS_ASSERT_EQUALS(citer, party.end());

        //Pull out enemy elements check
        vector<Character*> enemies = level.GetEnemies();
        vector<Character*>::iterator eiter;
        eiter = enemies.begin();
        TS_ASSERT_EQUALS((*eiter)->GetName(), "Enemy Type 1-A");
        eiter++;
        TS_ASSERT_EQUALS((*eiter)->GetName(), "Enemy Type 1-B");
        eiter++;
        TS_ASSERT_EQUALS((*eiter)->GetName(), "Enemy Type 1-C");
        eiter++;
        TS_ASSERT( eiter != enemies.end() );
        TS_ASSERT_EQUALS((*eiter)->GetName(), "Enemy Boss 1");
        eiter++;
        //and that's all
        TS_ASSERT_EQUALS(eiter, enemies.end());

        //Pull out all elements check
        vector<Character*> all = level.GetEveryone();
        vector<Character*>::iterator aiter;
        aiter = all.begin();
        TS_ASSERT_EQUALS((*aiter)->GetName(), "Han");
        aiter++;
        TS_ASSERT_EQUALS((*aiter)->GetName(), "Karl");
        aiter++;
        TS_ASSERT_EQUALS((*aiter)->GetName(), "Mike");
        aiter++;
        TS_ASSERT_EQUALS((*aiter)->GetName(), "Andrew");
        aiter++;
        TS_ASSERT_EQUALS((*aiter)->GetName(), "Enemy Type 1-A");
        aiter++;
        TS_ASSERT_EQUALS((*aiter)->GetName(), "Enemy Type 1-B");
        aiter++;
        TS_ASSERT_EQUALS((*aiter)->GetName(), "Enemy Type 1-C");
        aiter++;
        TS_ASSERT_EQUALS((*aiter)->GetName(), "Enemy Boss 1");
        aiter++;
        //and that's all
        TS_ASSERT_EQUALS(aiter, all.end());
    }

    void testUsageCase()
    {
        Level level( 0 );
        //check we are in free state
        TS_ASSERT_EQUALS(level.ReturnState(), Level::FREE);

        //party cannot be exhausted yet
        TS_ASSERT_EQUALS(level.AllExhaustedParty(), false);

        TS_ASSERT(level.GetCurCharacter() == NULL);
        level.OnSelect(Point(0,0));
        TS_ASSERT_EQUALS(level.GetCurCharacter()->GetName(), "Han");

        //into move state
        TS_ASSERT_EQUALS(level.ReturnState(), Level::MOVE);

        //Valid move
        //Nothing near to attack, set to free state
        level.OnSelect(Point(0,1));
        TS_ASSERT_EQUALS(level.ReturnState(), Level::FREE);
        TS_ASSERT_EQUALS(level.GetCurCharacter()->GetPoint(), Point(0,1));

        //should be exhausted
        TS_ASSERT_EQUALS(level.GetCurCharacter()->GetExhaust(), true);

        //lets cheat a bit for an attack
        level.OnSelect(Point(1,0));

        //stand still should move to attack
        level.OnSelect(Point(8,9));

        TS_ASSERT_EQUALS(level.ReturnState(), Level::ATTACK);

        //lets get the attack range
        vector<Point> apoints = level.GetAttackArea();
        vector<Point>::iterator aiter;
        aiter = apoints.begin();
        TS_ASSERT_EQUALS((*aiter), Point(7,9))
        aiter++;
        TS_ASSERT_EQUALS((*aiter), Point(9,9))
        aiter++;
        TS_ASSERT_EQUALS((*aiter), Point(8,8))
        aiter++;
        TS_ASSERT_EQUALS((*aiter), Point(8,10));
        aiter++;
        TS_ASSERT_EQUALS((*aiter), Point(7, 8));
        aiter++;
        TS_ASSERT_EQUALS((*aiter), Point(9, 10));
        aiter++;
        TS_ASSERT_EQUALS((*aiter), Point(9,8));
        aiter++;
        TS_ASSERT_EQUALS((*aiter), Point(7,10));
        aiter++;
        TS_ASSERT_EQUALS((*aiter), Point(6,9));
        aiter++;
        TS_ASSERT_EQUALS((*aiter), Point(10,9));
        aiter++;
        // 1,0 not valid, person
        TS_ASSERT_EQUALS((*aiter), Point(8,7));
        aiter++;
        TS_ASSERT_EQUALS((*aiter), Point(8,11));
        aiter++;
        TS_ASSERT_EQUALS(aiter, apoints.end());

        //test invalid
        level.OnSelect(Point(3,0));

        //state attack
        TS_ASSERT_EQUALS(level.ReturnState(), Level::ATTACK);

        //test in range no enemy
        level.OnSelect(Point(9,8));

        //state attack
        TS_ASSERT_EQUALS(level.ReturnState(), Level::ATTACK);

        level.OnSelect(Point(9,9));

        TS_ASSERT_EQUALS(level.ReturnState(), Level::FREE);
        TS_ASSERT_EQUALS(level.GetCurCharacter()->GetExhaust(), true);

        //Show ranges of others

        level.OnSelect(Point(2,0));
        level.OnSelect(Point(8,8));
        //cannot attack, only attacks adjacent
        TS_ASSERT_EQUALS(level.ReturnState(), Level::FREE);
        //Test party stuff lose cond win cond all exhausted

        level.OnSelect(Point(3,0));
        level.OnSelect(Point(9,8));

        //cannot attack adjacent, as an archer
        TS_ASSERT_EQUALS(level.ReturnState(), Level::FREE);

        //TestEndStates

        TS_ASSERT_EQUALS(level.AllExhaustedParty(), true);
        TS_ASSERT_EQUALS(level.GetTurn(), false);
        level.TakeTurn();
        TS_ASSERT_EQUALS(level.GetTurn(), true);

        //not all dead on either squad
        TS_ASSERT_EQUALS(level.GetWinCondition(), false);
        TS_ASSERT_EQUALS(level.GetLoseCondition(), false);

        vector<Character*> party = level.GetParty();
        vector<Character*>::iterator paiter;
        paiter = party.begin();
        (*paiter)->MakeDead();
        paiter++;
        (*paiter)->MakeDead();
        paiter++;
        (*paiter)->MakeDead();
        paiter++;
        (*paiter)->MakeDead();
        paiter++;
        TS_ASSERT_EQUALS(paiter, party.end());

        //now we're all dead
        TS_ASSERT_EQUALS(level.GetLoseCondition(), true);

        vector<Character*> enemies = level.GetEnemies();
        vector<Character*>::iterator eiter;
        eiter = enemies.begin();
        (*eiter)->MakeDead();
        eiter++;
        (*eiter)->MakeDead();
        eiter++;
        (*eiter)->MakeDead();
        eiter++;
        (*eiter)->MakeDead();
        eiter++;
        TS_ASSERT_EQUALS(eiter, enemies.end());

        //now they are all dead
        TS_ASSERT_EQUALS(level.GetWinCondition(), true);

        //test for a dead person
        TS_ASSERT(level.AIPointHasPerson(Point(8,9)) != NULL);
        TS_ASSERT(level.PointHasPerson(Point(9,9)) != NULL);

        //they are dead so they are exhausted
        TS_ASSERT_EQUALS(level.AllExhaustedEnemies(), true);
    }

    //all functions tested in usage case, this will show off the AI briefly(mirror class)
    //proves attacks and moves work for both sides
    void testOnAISelect()
    {
        Level level( 0 );
        level.OnSelect(Point(0,0));
        level.OnSelect(Point(0,0));
        level.OnSelect(Point(1,0));
        level.OnSelect(Point(1,0));
        level.OnSelect(Point(1,0));
        level.OnSelect(Point(2,0));
        level.OnSelect(Point(2,0));
        level.OnSelect(Point(3,0));
        level.OnSelect(Point(3,0));

        //now we are on AI turn
        TS_ASSERT_EQUALS(level.AllExhaustedParty(), true);
        level.SetState(Level::AIFREE);
        TS_ASSERT_EQUALS(level.ReturnState(), Level::AIFREE);
        level.OnAISelect(Point(9,9));

        //legit reset
        level.OnAISelect(Point(8,9));
        TS_ASSERT_EQUALS(level.ReturnState(), (int)Level::AIFREE);

        //cheat over
        level.OnAISelect(Point(0,9));
        level.OnAISelect(Point(0,1));
        //attackable
        TS_ASSERT_EQUALS(level.ReturnState(), Level::AIATTACK);
        level.OnAISelect(Point(0,0));
        TS_ASSERT_EQUALS(level.ReturnState(), (int)Level::AIFREE);
    }
};


#endif // __LEVELTEST_H

