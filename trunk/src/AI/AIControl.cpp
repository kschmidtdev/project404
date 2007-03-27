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
 * Karl Schmidt, March 20 2007    | Major adding of consts and reference usage, rearranging includes
 * Karl Schmidt, March 22 2007    | Changed name of GetClassName
 * Karl Schmidt, March 23 2007    | Removed unneeded include
 * Mike Malyuk, March 26, 2007    | Added new AI level (2). Tries to back off and regroup. Smarter healing.
 */

#include "AIControl.h"                                // class implemented

#include <util.h>

#include <cstdlib>
#include <ctime>
#include <cmath>

#include <GameEngine/Character.h>
#include <InputManager.h>
#include <GameEngine/Level.h>

namespace
{
    const int AI_FAKE_TIME_WAIT = 500;
}

/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

AIControl::AIControl(Level* level, const Map & map, int difficulty):mMap(map), mLevel(level), mDifficulty(difficulty)
{
}// AIControl

Point AIControl::DoAction()
{

    int curState = mLevel->ReturnState();
    PointVec points;
    PointVec archPoints;
    Point p;
    int selector = 0;
    int randint;
    int start = 0;
    double distance = 10000;
    Point closest;
    if(mDifficulty == 1)
    {
        switch(curState)
        {
            case Level::AIFREE:
            {
                const CharacterPtrVec& enemies = mLevel->GetEnemies();
                for(CharacterPtrConstItr eiter = enemies.begin(); eiter != enemies.end(); eiter++)
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
            }
            break;

            case Level::AIMOVE:
            {
                points = mMap.GetMovementRange(mLevel->GetEveryone(), mLevel->GetParty(), mLevel->GetCurCharacter());
                //If not a healer, push back enemies to look for
                if(mLevel->GetCurCharacter()->GetCharacterClassName() != "Healer")
                {
                    const CharacterPtrVec& enemies = mLevel->GetParty();
                    for(CharacterPtrConstItr citer = enemies.begin(); citer != enemies.end(); citer++)
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
                        for(CharacterPtrConstItr citer = enemies.begin(); citer != enemies.end(); citer++)
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
                    const CharacterPtrVec& enemies = mLevel->GetEnemies();
                    //If I don't have a target or my target is dead, get a new one!
                    if(mLevel->GetCurCharacter()->GetTarget() == NULL || mLevel->GetCurCharacter()->GetTarget()->GetPoint() == Point(-5, -5))
                    {
                        for(CharacterPtrConstItr citer = enemies.begin(); citer != enemies.end(); citer++)
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
                if(mLevel->GetCurCharacter()->GetCharacterClassName() != "Archer")
                {
                    for(PointConstItr piter = points.begin(); piter != points.end(); piter++)
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
                    for(PointConstItr piter = points.begin(); piter != points.end(); piter++)
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
                    for(PointConstItr piter = archPoints.begin(); piter != archPoints.end(); piter++)
                    {
                            if((sqrt(pow((double)((*piter).GetX() - mLevel->GetCurCharacter()->GetTarget()->GetPoint().GetX()), 2) + pow((double)((*piter).GetY() - mLevel->GetCurCharacter()->GetTarget()->GetPoint().GetY()), 2))) < distance)
                            {
                                closest = (*piter);
                                distance = (sqrt(pow((double)((*piter).GetX() - mLevel->GetCurCharacter()->GetTarget()->GetPoint().GetX()), 2) + pow((double)((*piter).GetY() - mLevel->GetCurCharacter()->GetTarget()->GetPoint().GetY()), 2)));
                            }
                    }
                }
                points.clear();
                return closest;
            }
            break;

            case Level::AIATTACK:
            {
                const PointVec& points = mLevel->GetAttackArea();
                Character* curChar = mLevel->GetCurCharacter();
                if(curChar->GetCharacterClassName() != "Healer")
                {
                    const CharacterPtrVec & party = mLevel->GetParty();
                    for(PointConstItr piter = points.begin(); piter != points.end(); piter++)
                    {
                        for(CharacterPtrConstItr eiter = party.begin(); eiter != party.end(); eiter++)
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
                    const CharacterPtrVec & enemy = mLevel->GetEnemies();
                    for(PointConstItr piter = points.begin(); piter != points.end(); piter++)
                    {
                        for(CharacterPtrConstItr eiter = enemy.begin(); eiter != enemy.end(); eiter++)
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
            break;
        }
    }
    else
    {
        switch(curState)
        {
            case Level::AIFREE:
            {
                const CharacterPtrVec& enemies = mLevel->GetEnemies();
                for(CharacterPtrConstItr eiter = enemies.begin(); eiter != enemies.end(); eiter++)
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
            }
            break;

            case Level::AIMOVE:
            {
                points = mMap.GetMovementRange(mLevel->GetEveryone(), mLevel->GetParty(), mLevel->GetCurCharacter());
                //If not a healer, push back enemies to look for
                if(mLevel->GetCurCharacter()->GetCharacterClassName() != "Healer")
                {
                    const CharacterPtrVec& enemies = mLevel->GetParty();
                    for(CharacterPtrConstItr citer = enemies.begin(); citer != enemies.end(); citer++)
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
                        for(CharacterPtrConstItr citer = enemies.begin(); citer != enemies.end(); citer++)
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
                    const CharacterPtrVec& enemies = mLevel->GetEnemies();
                    //If I don't have a target or my target is dead, get a new one!
                    if(mLevel->GetCurCharacter()->GetTarget() == NULL || mLevel->GetCurCharacter()->GetTarget()->GetPoint() == Point(-5, -5) || mLevel->GetCurCharacter()->GetTarget()->GetMaxHP() == mLevel->GetCurCharacter()->GetTarget()->GetHP())
                    {
                        for(CharacterPtrConstItr citer = enemies.begin(); citer != enemies.end(); citer++)
                        {
                            //make sure he ain't dead and he needs healin!
                            if((*citer)->GetPoint() != Point(-5, -5) && (*citer)->GetHP() < (*citer)->GetMaxHP() && (*citer)->GetPoint() != mLevel->GetCurCharacter()->GetPoint())
                            {
                                if(mLevel->GetCurCharacter()->GetTarget() != NULL && ((mLevel->GetCurCharacter()->GetTarget()->GetMaxHP() - mLevel->GetCurCharacter()->GetTarget()->GetHP()) > ((*citer)->GetMaxHP() - (*citer)->GetHP())))
                                {
                                    mLevel->GetCurCharacter()->SetTarget((*citer));
                                }
                                else
                                {
                                    mLevel->GetCurCharacter()->SetTarget((*citer));
                                }
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
                if(mLevel->GetCurCharacter()->GetCharacterClassName() == "Knight")
                {
                    if(mMap.AIAttackOrNot(mLevel->GetEveryone(), mLevel->GetParty(), mLevel->GetCurCharacter()))
                    {
                        for(PointConstItr piter = points.begin(); piter != points.end(); piter++)
                        {
                            if((sqrt(pow((double)((*piter).GetX() - mLevel->GetCurCharacter()->GetTarget()->GetPoint().GetX()), 2) + pow((double)((*piter).GetY() - mLevel->GetCurCharacter()->GetTarget()->GetPoint().GetY()), 2))) < distance)
                            {
                                closest = (*piter);
                                distance = (sqrt(pow((double)((*piter).GetX() - mLevel->GetCurCharacter()->GetTarget()->GetPoint().GetX()), 2) + pow((double)((*piter).GetY() - mLevel->GetCurCharacter()->GetTarget()->GetPoint().GetY()), 2)));
                            }
                        }
                    }
                    else
                    {
                        points = mMap.AIGoWhere(mLevel->GetEveryone(), mLevel->GetParty(), mLevel->GetEnemies(), mLevel->GetCurCharacter());
                        if(points.size() == 0)
                        {
                            points.push_back(mLevel->GetCurCharacter()->GetPoint());
                        }

                        for(PointConstItr piter = points.begin(); piter != points.end(); piter++)
                        {
                            //std::cout << mLevel->GetCurCharacter()->GetName() << std::endl;
                            //std::cout << (*piter).GetX() << ", " << (*piter).GetY() << std::endl;
                            if((sqrt(pow((double)((*piter).GetX() - mLevel->GetCurCharacter()->GetTarget()->GetPoint().GetX()), 2) + pow((double)((*piter).GetY() - mLevel->GetCurCharacter()->GetTarget()->GetPoint().GetY()), 2))) < distance)
                            {
                                closest = (*piter);
                                distance = (sqrt(pow((double)((*piter).GetX() - mLevel->GetCurCharacter()->GetTarget()->GetPoint().GetX()), 2) + pow((double)((*piter).GetY() - mLevel->GetCurCharacter()->GetTarget()->GetPoint().GetY()), 2)));
                            }
                        }
                    }
                }
                else if (mLevel->GetCurCharacter()->GetCharacterClassName() == "Healer")
                {
                    if(mMap.AIAttackOrNot(mLevel->GetEveryone(), mLevel->GetEnemies(), mLevel->GetCurCharacter()))
                    {
                        for(PointConstItr piter = points.begin(); piter != points.end(); piter++)
                        {
                            if((sqrt(pow((double)((*piter).GetX() - mLevel->GetCurCharacter()->GetTarget()->GetPoint().GetX()), 2) + pow((double)((*piter).GetY() - mLevel->GetCurCharacter()->GetTarget()->GetPoint().GetY()), 2))) < distance)
                            {
                                closest = (*piter);
                                distance = (sqrt(pow((double)((*piter).GetX() - mLevel->GetCurCharacter()->GetTarget()->GetPoint().GetX()), 2) + pow((double)((*piter).GetY() - mLevel->GetCurCharacter()->GetTarget()->GetPoint().GetY()), 2)));
                            }
                        }
                    }
                    else
                    {
                        points = mMap.AIGoWhere(mLevel->GetEveryone(), mLevel->GetParty(), mLevel->GetEnemies(), mLevel->GetCurCharacter());
                        if(points.size() == 0)
                        {
                            points.push_back(mLevel->GetCurCharacter()->GetPoint());
                        }

                        for(PointConstItr piter = points.begin(); piter != points.end(); piter++)
                        {
                            //std::cout << mLevel->GetCurCharacter()->GetName() << std::endl;
                            //std::cout << (*piter).GetX() << ", " << (*piter).GetY() << std::endl;
                            if((sqrt(pow((double)((*piter).GetX() - mLevel->GetCurCharacter()->GetTarget()->GetPoint().GetX()), 2) + pow((double)((*piter).GetY() - mLevel->GetCurCharacter()->GetTarget()->GetPoint().GetY()), 2))) < distance)
                            {
                                closest = (*piter);
                                distance = (sqrt(pow((double)((*piter).GetX() - mLevel->GetCurCharacter()->GetTarget()->GetPoint().GetX()), 2) + pow((double)((*piter).GetY() - mLevel->GetCurCharacter()->GetTarget()->GetPoint().GetY()), 2)));
                            }
                        }
                    }
                }
                else //I'm an archer, if I run right beside them I can't attack, so lets not do that
                {
                    if(mMap.AIAttackOrNot(mLevel->GetEveryone(), mLevel->GetParty(), mLevel->GetCurCharacter()))
                    {
                        for(PointConstItr piter = points.begin(); piter != points.end(); piter++)
                        {
                            if((*piter) != Point(mLevel->GetCurCharacter()->GetTarget()->GetPoint().GetX(), mLevel->GetCurCharacter()->GetTarget()->GetPoint().GetY() + 1) &&
                                (*piter) != Point(mLevel->GetCurCharacter()->GetTarget()->GetPoint().GetX() + 1, mLevel->GetCurCharacter()->GetTarget()->GetPoint().GetY()) &&
                                (*piter) != Point(mLevel->GetCurCharacter()->GetTarget()->GetPoint().GetX(), mLevel->GetCurCharacter()->GetTarget()->GetPoint().GetY() - 1) &&
                                (*piter) != Point(mLevel->GetCurCharacter()->GetTarget()->GetPoint().GetX() - 1, mLevel->GetCurCharacter()->GetTarget()->GetPoint().GetY()))
                            {
                                archPoints.push_back((*piter));
                            }
                        }
                        for(PointConstItr piter = archPoints.begin(); piter != archPoints.end(); piter++)
                        {
                                if((sqrt(pow((double)((*piter).GetX() - mLevel->GetCurCharacter()->GetTarget()->GetPoint().GetX()), 2) + pow((double)((*piter).GetY() - mLevel->GetCurCharacter()->GetTarget()->GetPoint().GetY()), 2))) < distance)
                                {
                                    closest = (*piter);
                                    distance = (sqrt(pow((double)((*piter).GetX() - mLevel->GetCurCharacter()->GetTarget()->GetPoint().GetX()), 2) + pow((double)((*piter).GetY() - mLevel->GetCurCharacter()->GetTarget()->GetPoint().GetY()), 2)));
                                }
                        }
                    }
                    else
                    {
                        points = mMap.AIGoWhere(mLevel->GetEveryone(), mLevel->GetParty(), mLevel->GetEnemies(), mLevel->GetCurCharacter());
                        if(points.size() == 0)
                        {
                            points.push_back(mLevel->GetCurCharacter()->GetPoint());
                        }
                        for(PointConstItr piter = points.begin(); piter != points.end(); piter++)
                        {
                            if((*piter) != Point(mLevel->GetCurCharacter()->GetTarget()->GetPoint().GetX(), mLevel->GetCurCharacter()->GetTarget()->GetPoint().GetY() + 1) &&
                                (*piter) != Point(mLevel->GetCurCharacter()->GetTarget()->GetPoint().GetX() + 1, mLevel->GetCurCharacter()->GetTarget()->GetPoint().GetY()) &&
                                (*piter) != Point(mLevel->GetCurCharacter()->GetTarget()->GetPoint().GetX(), mLevel->GetCurCharacter()->GetTarget()->GetPoint().GetY() - 1) &&
                                (*piter) != Point(mLevel->GetCurCharacter()->GetTarget()->GetPoint().GetX() - 1, mLevel->GetCurCharacter()->GetTarget()->GetPoint().GetY()))
                            {
                                archPoints.push_back((*piter));
                            }
                        }
                        for(PointConstItr piter = archPoints.begin(); piter != archPoints.end(); piter++)
                        {
                                if((sqrt(pow((double)((*piter).GetX() - mLevel->GetCurCharacter()->GetTarget()->GetPoint().GetX()), 2) + pow((double)((*piter).GetY() - mLevel->GetCurCharacter()->GetTarget()->GetPoint().GetY()), 2))) < distance)
                                {
                                    closest = (*piter);
                                    distance = (sqrt(pow((double)((*piter).GetX() - mLevel->GetCurCharacter()->GetTarget()->GetPoint().GetX()), 2) + pow((double)((*piter).GetY() - mLevel->GetCurCharacter()->GetTarget()->GetPoint().GetY()), 2)));
                                }
                        }
                    }
                }
                points.clear();
                return closest;
            }
            break;

            case Level::AIATTACK:
            {
                const PointVec& points = mLevel->GetAttackArea();
                Character* curChar = mLevel->GetCurCharacter();
                if(curChar->GetCharacterClassName() != "Healer")
                {
                    const CharacterPtrVec & party = mLevel->GetParty();
                    for(PointConstItr piter = points.begin(); piter != points.end(); piter++)
                    {
                        for(CharacterPtrConstItr eiter = party.begin(); eiter != party.end(); eiter++)
                        {
                            if((*piter) == (*eiter)->GetPoint() && (*piter) == mLevel->GetCurCharacter()->GetTarget()->GetPoint())
                            {
                                return (*piter);
                            }
                        }
                    }
                    for(PointConstItr piter = points.begin(); piter != points.end(); piter++)
                    {
                        for(CharacterPtrConstItr eiter = party.begin(); eiter != party.end(); eiter++)
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
                    const CharacterPtrVec & enemy = mLevel->GetEnemies();
                    for(PointConstItr piter = points.begin(); piter != points.end(); piter++)
                    {
                        for(CharacterPtrConstItr eiter = enemy.begin(); eiter != enemy.end(); eiter++)
                        {
                            if((*piter) == (*eiter)->GetPoint() && (*piter) == mLevel->GetCurCharacter()->GetTarget()->GetPoint())
                            {
                                return (*piter);
                            }
                        }
                    }
                    for(PointConstItr piter = points.begin(); piter != points.end(); piter++)
                    {
                        for(CharacterPtrConstItr eiter = enemy.begin(); eiter != enemy.end(); eiter++)
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
            break;
        }
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
