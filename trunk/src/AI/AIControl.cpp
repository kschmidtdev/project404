/**
 * File: AIControl.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Mike Malyuk, February 15 | Initial Implementation
 */
#include "AIControl.h"                                // class implemented


/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

AIControl::AIControl(Level* level, Point maxMap):mMax(maxMap), mLevel(level)
{
}// AIControl
Point AIControl::DoAction()
{
    int curState = mLevel->ReturnState();
    vector<Character*> enemies;
    vector<Point> points;
    switch(curState)
    {
        case 3:
            enemies = mLevel->GetEnemies();
            for(vector<Character*>::iterator eiter = enemies.begin(); eiter != enemies.end(); eiter++)
            {
                if((*eiter)->GetExhaust() == false)
                {
                    return (*eiter)->GetPoint();
                }
            }
            return Point(-30,-30);
        case 4:
            points = mLevel->GetMoveArea();
            for(vector<Point>::iterator piter = points.begin(); piter != points.end(); piter++)
            {
                if((*piter).GetX() >= 0 && (*piter).GetY() >= 0 && (*piter).GetX() <= mMax.GetX() && (*piter).GetY() <= mMax.GetY())
                {
                    points.clear();
                    return (*piter);
                }
            }
            return Point(-30, -30);
        case 5:
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
