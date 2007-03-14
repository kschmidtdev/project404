#ifndef __AICONTROLTEST_H
#define __AICONTROLTEST_H

#include <cxxtest/TestSuite.h>

#include <../AI/AIControl.h>
#include <../GameEngine/Level.h>
#include <../Point.h>
#include <../GameEngine/Character.h>
//
// A generated test suite: Just write tests!
//

class AIControlTest : public CxxTest::TestSuite
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

    void testAI()
    {
        Map map;
        Level* level = new Level( 0 );
        Point p(9,9);
        AIControl ai(level, map);
        level->SetState(Level::AIFREE);
        //test point retrieval
        Point spot = ai.DoAction();
        vector<Character*> guys = level->GetEnemies();
        vector<Character*>::iterator iter = guys.begin();
        while(iter != guys.end())
        {
            if((*iter)->GetPoint() == spot)
            {
                break;
            }
            iter++;
        }
        //it exists in list
        TS_ASSERT_EQUALS((*iter)->GetPoint(), spot);

        level->OnAISelect(Point(1,9));
        TS_ASSERT_EQUALS(level->ReturnState(), Level::AIMOVE);

        Point another = ai.DoAction();
        vector<Point> points = map.GetMovementRange(level->GetEveryone(), level->GetEnemies(), level->GetCurCharacter());
        vector<Point>::iterator ppiter;
        ppiter = points.begin();
        while(ppiter != points.end())
        {
            if((*ppiter) == another)
            {
                break;
            }
            ppiter++;
        }
        //it exists in list
        TS_ASSERT_EQUALS((*ppiter), another);
        level->GetCurCharacter()->Move(Point(0,1));
        TS_ASSERT_EQUALS(level->ReturnState(), Level::AIMOVE);
        level->OnAISelect(Point(0,1));


        TS_ASSERT_EQUALS(level->ReturnState(), Level::AIATTACK);
        Point spotted = ai.DoAction();
        vector<Character*> guyss = level->GetEveryone();
        vector<Character*>::iterator iterer = guyss.begin();
        while(iterer != guyss.end())
        {
            if((*iterer)->GetPoint() == spotted)
            {
                break;
            }
            iterer++;
        }
        //it exists in list
        TS_ASSERT_EQUALS((*iterer)->GetPoint(), spotted);
    }

};


#endif // __AICONTROLTEST_H

