/**
 * File: AIControl.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Mike Malyuk, February 15, 2007 | Initial Implementation
 * Mike Malyuk, February 15, 2007 | Fixed bounds so AI can't leave the grid
 * Karl Schmidt, March 9, 2007	  | Added proper enum usage, and faked AI 'thinking' pauses
 * Mike Malyuk, March 10, 2007    | Added map to calculate movement
 * Mike Malyuk, March 14, 2007    | Dijkstras method changed, added no params
 */

#include <util.h>

#include "AIControl.h"                                // class implemented

const int AI_FAKE_TIME_WAIT = 500;
/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

AIControl::AIControl(Level* level, Map map):mMap(map), mLevel(level)
{
}// AIControl
Point AIControl::DoAction()
{
    int curState = mLevel->ReturnState();
    vector<Character*> enemies;
    vector<Point> points;
    Point p;
    switch(curState)
    {
        case Level::AIFREE:
            enemies = mLevel->GetEnemies();
            for(vector<Character*>::iterator eiter = enemies.begin(); eiter != enemies.end(); eiter++)
            {
                if((*eiter)->GetExhaust() == false)
                {
                    SDL_Delay( AI_FAKE_TIME_WAIT );
                    return (*eiter)->GetPoint();
                }
            }
            return Point(-30,-30);
        case Level::AIMOVE:
            points = mMap.GetMovementRange(mLevel->GetEveryone(), mLevel->GetParty(), mLevel->GetCurCharacter());
            p = *(points.begin());
            points.clear();
            return p;

        case Level::AIATTACK:
            vector<Point> points = mLevel->GetAttackArea();
            Character* curChar = mLevel->GetCurCharacter();
            if(curChar->GetClassName() != "Healer")
            {
                vector<Character*> party = mLevel->GetParty();
                for(vector<Point>::iterator piter = points.begin(); piter != points.end(); piter++)
                {
                    for(vector<Character*>::iterator eiter = party.begin(); eiter != party.end(); eiter++)
                    {
                        if((*piter) == (*eiter)->GetPoint())
                        {
                            return (*piter);
                        }
                    }
                }
            }
            else
            {
                vector<Character*> enemy = mLevel->GetEnemies();
                for(vector<Point>::iterator piter = points.begin(); piter != points.end(); piter++)
                {
                    for(vector<Character*>::iterator eiter = enemy.begin(); eiter != enemy.end(); eiter++)
                    {
                        if((*piter) == (*eiter)->GetPoint())
                        {
                            return (*piter);
                        }
                    }
                }
            }
            return Point(-30, -30);
    }
    return Point(-30, -30);
}
AIControl::~AIControl()
{
}// ~AIControl


//============================= OPERATORS ====================================

//============================= OPERATIONS ===================================
//============================= ACCESS     ===================================
//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
