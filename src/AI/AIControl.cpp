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
 * Mike Malyuk, March 14, 2007    | Huge update to AI, now it acts smarter (better than the jig anyway)
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
    vector<Point> archPoints;
    Point p;
    int selector = 0;
    int randint;
    int start = 0;
    double distance = 10000;
    Point closest;
    switch(curState)
    {
        case Level::AIFREE:
            enemies = mLevel->GetEnemies();
            for(vector<Character*>::iterator eiter = enemies.begin(); eiter != enemies.end(); eiter++)
            {
                if((*eiter)->GetExhaust() == false)
                {
                    if( !(InputManager::GetInstance()->GetMode() == InputManager::PLAYBACK) )
                    {
                        SDL_Delay( AI_FAKE_TIME_WAIT );
                    }
                    return (*eiter)->GetPoint();
                }
            }
            return Point(-30,-30);
        case Level::AIMOVE:
            points = mMap.GetMovementRange(mLevel->GetEveryone(), mLevel->GetParty(), mLevel->GetCurCharacter());
            //If not a healer, push back enemies to look for
            if(mLevel->GetCurCharacter()->GetClassName() != "Healer")
            {
                enemies = mLevel->GetParty();
                for(vector<Character*>::iterator citer = enemies.begin(); citer != enemies.end(); citer++)
                {
                    if((*citer)->GetPoint() != Point(-5, -5))
                    {
                        selector++;
                    }
                }
                //lets randomly decide who is going to be our target
                randint = (rand()%selector);

                //if I don't have a target or I killed my target get a new one
                if(mLevel->GetCurCharacter()->GetTarget() == NULL || mLevel->GetCurCharacter()->GetTarget()->GetPoint() == Point(-5, -5))
                {
                    for(vector<Character*>::iterator citer = enemies.begin(); citer != enemies.end(); citer++)
                    {
                        //make sure he ain't dead!
                        if((*citer)->GetPoint() != Point(-5, -5))
                        {
                            if(start == randint)
                            {
                                mLevel->GetCurCharacter()->SetTarget((*citer));
                                break;
                            }
                            else
                            {
                                start++;
                            }
                        }
                    }
                }
            }
            else //I'm a healer lets get my friends
            {
                enemies = mLevel->GetEnemies();
                //If I don't have a target or my target is dead, get a new one!
                if(mLevel->GetCurCharacter()->GetTarget() == NULL || mLevel->GetCurCharacter()->GetTarget()->GetPoint() == Point(-5, -5))
                {
                    for(vector<Character*>::iterator citer = enemies.begin(); citer != enemies.end(); citer++)
                    {
                        //make sure he ain't dead and he needs healin!
                        if((*citer)->GetPoint() != Point(-5, -5) && (*citer)->GetHP() < (*citer)->GetMaxHP() && (*citer)->GetPoint() != mLevel->GetCurCharacter()->GetPoint())
                        {
                            mLevel->GetCurCharacter()->SetTarget((*citer));
                            break;
                        }
                    }
                }
                //no one needs healing? Lets run around like a chicken with its head cut off!
                if(mLevel->GetCurCharacter()->GetTarget() == NULL || mLevel->GetCurCharacter()->GetTarget()->GetPoint() == Point(-5, -5))
                {
                    p = *(points.begin());
                    points.clear();
                    return p;
                }
            }
            //if I'm not an archer, I can run right up to the guy
            if(mLevel->GetCurCharacter()->GetClassName() != "Archer")
            {
                for(vector<Point>::iterator piter = points.begin(); piter != points.end(); piter++)
                    {
                        if((sqrt(pow((double)((*piter).GetX() - mLevel->GetCurCharacter()->GetTarget()->GetPoint().GetX()), 2) + pow((double)((*piter).GetY() - mLevel->GetCurCharacter()->GetTarget()->GetPoint().GetY()), 2))) < distance)
                        {
                            closest = (*piter);
                            distance = (sqrt(pow((double)((*piter).GetX() - mLevel->GetCurCharacter()->GetTarget()->GetPoint().GetX()), 2) + pow((double)((*piter).GetY() - mLevel->GetCurCharacter()->GetTarget()->GetPoint().GetY()), 2)));
                        }
                    }
            }
            else //I'm an archer, if I run right beside them I can't attack, so lets not do that
            {
                //cout << mLevel->GetCurCharacter()->GetTarget()->GetPoint().GetX() - 1 << ", " << mLevel->GetCurCharacter()->GetTarget()->GetPoint().GetY() << endl;
                //cout << mLevel->GetCurCharacter()->GetTarget()->GetPoint().GetX() + 1 << ", " << mLevel->GetCurCharacter()->GetTarget()->GetPoint().GetY() << endl;
                //cout << mLevel->GetCurCharacter()->GetTarget()->GetPoint().GetX() << ", " << mLevel->GetCurCharacter()->GetTarget()->GetPoint().GetY() - 1 << endl;
                //cout << mLevel->GetCurCharacter()->GetTarget()->GetPoint().GetX() << ", " << mLevel->GetCurCharacter()->GetTarget()->GetPoint().GetY() + 1<< endl;
                for(vector<Point>::iterator piter = points.begin(); piter != points.end(); piter++)
                {
                    if((*piter) != Point(mLevel->GetCurCharacter()->GetTarget()->GetPoint().GetX(), mLevel->GetCurCharacter()->GetTarget()->GetPoint().GetY() + 1) &&
                        (*piter) != Point(mLevel->GetCurCharacter()->GetTarget()->GetPoint().GetX() + 1, mLevel->GetCurCharacter()->GetTarget()->GetPoint().GetY()) &&
                        (*piter) != Point(mLevel->GetCurCharacter()->GetTarget()->GetPoint().GetX(), mLevel->GetCurCharacter()->GetTarget()->GetPoint().GetY() - 1) &&
                        (*piter) != Point(mLevel->GetCurCharacter()->GetTarget()->GetPoint().GetX() - 1, mLevel->GetCurCharacter()->GetTarget()->GetPoint().GetY()) &&
                        (*piter) != Point(mLevel->GetCurCharacter()->GetTarget()->GetPoint()))
                    {
                        archPoints.push_back((*piter));
                    }
                }
                for(vector<Point>::iterator piter = archPoints.begin(); piter != archPoints.end(); piter++)
                {
                        //cout << (*piter).GetX() << ", " << (*piter).GetY() << endl;
                        if((sqrt(pow((double)((*piter).GetX() - mLevel->GetCurCharacter()->GetTarget()->GetPoint().GetX()), 2) + pow((double)((*piter).GetY() - mLevel->GetCurCharacter()->GetTarget()->GetPoint().GetY()), 2))) < distance)
                        {
                            closest = (*piter);
                            distance = (sqrt(pow((double)((*piter).GetX() - mLevel->GetCurCharacter()->GetTarget()->GetPoint().GetX()), 2) + pow((double)((*piter).GetY() - mLevel->GetCurCharacter()->GetTarget()->GetPoint().GetY()), 2)));
                        }
                }
            }
            points.clear();
            return closest;

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
