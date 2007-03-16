#ifndef __MAPTEST_H
#define __MAPTEST_H

#include <cxxtest/TestSuite.h>

#include <GameEngine/Map.h>
#include <Logger.h>
#include <GameEngine/Character.h>
#include <Point.h>
#include <Database/DBEngine.h>
//
// A generated test suite: Just write tests!
//

class MapTest : public CxxTest::TestSuite
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

    void TestMapAddAndGet()
    {

        Tile one(Point(0,0), "ONE");
        Tile two(Point(0,1), "TWO");
        vector<Tile> tiles;
        tiles.push_back(one);
        tiles.push_back(two);
        Map another(tiles);
        TS_ASSERT_EQUALS(another.GetTile(Point(0,1)).GetType(), "TWO");
        TS_ASSERT_EQUALS(another.GetTile(Point(0,0)).GetType(), "ONE");
    }

    void TestUltraSuperMap()
    {
        DBEngine* DBE = DBEngine::GetInstance();
        Map map = Map(DBE->LoadBattleMap( 1 ));
        vector<Character*> enemies;
        vector<Character*> heroes;
        vector<Character*> all;
        Archer* enemy = new Archer("YDONOAF", 1, NULL, NULL);
        enemy->Move(Point(9,9));
        enemies.push_back(enemy);
        Knight* hero = new Knight("HERO!", 2, NULL, NULL);
        hero->Move(Point(0,0));
        heroes.push_back(hero);
        all.push_back(enemy);
        all.push_back(hero);
        vector<Point> move = map.GetMovementRange(all, enemies, hero);

        // hero is at 0,0, his AGI at level 2 will be 6, movement = 3
        // 0,1 1,0 are grass he may move on these. 2,0 is road costing 1, he can move here. He can also stay put.
        // we should get back [0,0 0,1 1,0 2,0], no fringes, and no bad points (0, -1) or (-1, 0)

        int need = 4;
        int count = 0;
        for(vector<Point>::iterator piter = move.begin(); piter != move.end(); piter++)
        {
            if((*piter) == Point(0,0) || (*piter) == Point(0,1) || (*piter) == Point(1,0) || (*piter) == Point(2,0))
            {
                count++;
            }
            //we got something unexpected throw an error by breaking and resetting count
            else
            {
                count = 0;
                break;
            }
        }
        //Got all the points!
        TS_ASSERT_EQUALS(need, count);

        //lets test immovable objects!
        // A rock exists at 1,1 this should throw a wrench in the works!
        hero->Move(Point(0,1));
        move = map.GetMovementRange(all, enemies, hero);

        //ok new situation, hero stands on grass. He has a rock to his right
        //rock immovable, cannot move to this spot. However it should also
        //block any movement "through" the rock. Therefor I do not expect (2,1)
        //grass up and down [0,0 0,2] each cost 2, neither gets us closer to road.
        //Therefore these are the only points along with own. No negatives either
        need = 3;
        count = 0;
        for(vector<Point>::iterator piter = move.begin(); piter != move.end(); piter++)
        {
            if((*piter) == Point(0,0) || (*piter) == Point(0,2) || (*piter) == Point(0,1))
            {
                count++;
            }
            //we got something unexpected throw an error by breaking and resetting count
            else
            {
                count = 0;
                break;
            }
        }
        //Got all the points! (of course!)
        TS_ASSERT_EQUALS(need, count);

        //got this far huh? how about enemies, they block too?
        //lets move the enemy somewhere fun (4,5)!!
        enemy->Move(Point(6,5));

        hero->Move(Point(5,5));
        move = map.GetMovementRange(all, enemies, hero);
        //Conundrum. Hero is on the road over the water. Enemy stands in front! Where can he go!
        //Well we can't go through the enemy, nor stand on him, (7,5) out
        //Go backwards on road [4,5 3,5 2,5] also can go off road [5,6 4,6 4,4] also on water [5,4] and self (5,5)
        need = 8;
        count = 0;

        for(vector<Point>::iterator piter = move.begin(); piter != move.end(); piter++)
        {
            if((*piter) == Point(4,5) || (*piter) == Point(3,5) || (*piter) == Point(2,5) ||
                (*piter) == Point(5,6) || (*piter) == Point(4,6) || (*piter) == Point(5,4) ||
                (*piter) == Point(5,5) || (*piter) == Point(4,4))
            {
                count++;
            }
            //we got something unexpected throw an error by breaking and resetting count
            else
            {
                count = 0;
                break;
            }
        }
        TS_ASSERT_EQUALS(need, count);

        //That's it SURROUND HIM!! HE WILL ERROR WITH NO WHERE TO GO BWAHAHA
        enemy = new Archer("YDONOAF", 1, NULL, NULL);
        enemy->Move(Point(4,5));
        enemies.push_back(enemy);
        all.push_back(enemy);
        enemy = new Archer("YDONOAF", 1, NULL, NULL);
        enemy->Move(Point(5,6));
        enemies.push_back(enemy);
        all.push_back(enemy);
        enemy = new Archer("YDONOAF", 1, NULL, NULL);
        enemy->Move(Point(5,4));
        enemies.push_back(enemy);
        all.push_back(enemy);

        hero->Move(Point(5,5));
        move = map.GetMovementRange(all, enemies, hero);
        //Stuck behind a wall, should only return his own spot.
        need = 1;
        count = 0;

        for(vector<Point>::iterator piter = move.begin(); piter != move.end(); piter++)
        {
            if((*piter) == Point(5,5))
            {
                count++;
            }
            //we got something unexpected throw an error by breaking and resetting count
            else
            {
                count = 0;
                break;
            }
        }
        TS_ASSERT_EQUALS(need, count);

        for( vector<Character*>::iterator aiter = all.begin(); aiter != all.end(); aiter++)
        {
            delete (*aiter);
        }
        heroes.clear();
        enemies.clear();
        all.clear();
    }

};


#endif // __MAPTEST_H

