/**
 * File: Level.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Mike Malyuk, February 11, 2007 | Initial Implementation
 * Mike Malyuk, February 12, 2007 | Added getters for UI
 * Andrew Osborne, February 12, 2007 | Added default constructor to create test/version1 level
 * Mike Malyuk, February 12, 2007 | Added tiny fix to make sure we don't hang on empty spaces
 * Karl Schmidt, February 12 2007 | Added initializing values for some variables that weren't being set
 *                                  in the current default constructor
 * Mike Malyuk, February 14, 2007 | Added function PointHasPerson to return enemy state, Minor fixes.
 * Mike Malyuk, February 14, 2007 | Added healer specific code, fixed a few more bugs
 * Karl Schmidt, February 14 2007 | Fixed healer crash bug/bugnonetheless
 * Karl Schmidt, February 14 2007 | Fixed the newest constructor (gave member vars default values)
 * Mike Malyuk, February 15, 2007 | Fixed more bugs, now shouldn't crash. Runs 2p til we implement AI
 *                                | Move range and Attack range don't show up for enemies (bug)
 * Mike Malyuk, February 15, 2007 | Fixed small bug in Healer code
 * Karl Schmidt, February 15 2007 | Fixed an odd header include path
 * Karl Schmidt, February 15 2007 | Fixed slight memory leak
 * Karl Schmidt, March 04 2007    | Fixed another slight memory leak
 * Mike Malyuk, March 10 2007     | Removed move methods now in Map, cleared things out to work with new method
 * Karl Schmidt, March 12 2007	   | Turfed default constructor body since it's not really used anymore, and
 *									     is used in one area temporarily so it's causing memory leaks
 * Mike Malyuk, March 14 2007     | Set map in Level for evil Overlord
 * Seung Woo Han, March 14 2007   | Modified Level(int) constructor. Now This contructor takes integer value which is the battle
 *                                  number. No further changes will be made to Level(int battleNumber) I hope.
 * Seung Woo Han, March 15 2007   | ~Level modified. Previously, it shut down DBEngine which shouldn't be.
 * Karl Schmidt, March 14 2007	  | Fixed a small iterator dereferencing causing crash bug
 */

#include <util.h>

#include "Level.h"                                // class implemented
#include "Archer.h"
#include "Knight.h"
#include "Healer.h"
#include "Mage.h"
#include "Database/DBEngine.h"
#include <util.h>


/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

Level::Level()
: mState( FREE ), mMyTurn( true )
{
}// Level

Level::Level(vector<Character*> party, vector<Character*> badguys, vector<Point> start)
: mState(FREE), mParty(party), mEnemies(badguys), mStart(start), mCurChar(NULL),  mMyTurn(true), mDefaultConstructor( false )
{
    vector<Character*>::iterator iter;
    vector<Point>::iterator piter;
    iter = mParty.begin();
    piter = mStart.begin();
    while(iter != mParty.end() && piter != mStart.end())
    {
        (*iter)->Move((*piter));
        iter++;
        piter++;
    }
}

Level::Level(int battleNumber)
: mState(FREE), mCurChar( NULL ), mMyTurn( true )
{
    DBEngine* DBE = DBEngine::GetInstance();

    mMap = Map( DBE->LoadBattleMap( battleNumber ) );

    if( mMap.GetTiles().empty() )
    {
        return;
    }

    Point StartingPoint;
    DBVector2D* StartingVector;

    //// Party Setting ////
    vector<Character*>* PartyList = DBE->LoadParty( battleNumber ); // Get the pointer of party members in this level.
    vector<Character*>::iterator Iter1; // Iterator.
    for (Iter1 = PartyList->begin(); Iter1 != PartyList->end(); Iter1++)
    {
        StartingVector = DBE->LoadPartyStartingPoint( battleNumber, *Iter1 );
        StartingPoint.Set( StartingVector->GetX(), StartingVector->GetY() );
        (*Iter1)->Move( StartingPoint );
        mParty.push_back( (*Iter1) );
    }

    //// Enemies Setting ////
    vector<Character*>* EnemiesList = DBE->LoadEnemies( battleNumber ); // Get the pointer of enemy members in this level.
    vector<Character*>::iterator Iter2; // Iterator.
    for (Iter2 = EnemiesList->begin(); Iter2 != EnemiesList->end(); Iter2++)
    {
        StartingVector = DBE->LoadEnemiesStartingPoint( battleNumber, *Iter2 );
        StartingPoint.Set( StartingVector->GetX(), StartingVector->GetY() );
        (*Iter2)->Move( StartingPoint );
        mEnemies.push_back( (*Iter2) );
    }

    delete PartyList;
    delete EnemiesList;
}

Level::~Level()
{
}// ~Level

//============================= OPERATIONS ===================================
void Level::TakeTurn()
{
    if(mMyTurn == true)
    {
        vector<Character*>::iterator iter;
        iter = mEnemies.begin();
        while( iter != mEnemies.end())
        {
            if((*iter)->IsDead() == false)
            {
                (*iter)->Invigorate();
            }
            iter++;
        }
        mMyTurn = false;
    }
    else
    {
        vector<Character*>::iterator iter;
        iter = mParty.begin();
        while( iter != mParty.end())
        {
            if((*iter)->IsDead() == false)
            {
                (*iter)->Invigorate();
            }
            iter++;
        }
        mMyTurn = true;
    }
}

Character* Level::OnSelect(Point p)
{
    //Need to select a character
    if(mState == FREE)
    {
        vector<Character*>::iterator iter;
        iter = mParty.begin();
        while( iter != mParty.end() && ((*iter)->GetPoint()) != p)
        {
            iter++;
        }
        if( iter != mParty.end() && *iter != NULL && !((*iter)->GetExhaust()) && (*iter)->GetPoint() == p)
        {
            mCurChar = (*iter);
            mState = MOVE;
            return *iter;
        }
        else
        {
            return NULL;
        }
    }
    //Need to move
    else if(mState == MOVE)
    {

            mCurChar->Move(p);
            cout << "Attacker " << mCurChar->GetName()  <<" (" << mCurChar->GetClassName() << ") moving to: " << mCurChar->GetPoint().GetX() << "," << mCurChar->GetPoint().GetY() << endl;
            if(mCurChar->GetClassName() != "Healer")
            {
                vector<Point> attackArea = mCurChar->CalcAction();
                vector<Character*>::iterator charIter;
                vector<Point>::iterator iter2;
                iter2 = attackArea.begin();
                charIter = mEnemies.begin();
                //check if enemies are in range, if not exhaust character
                while(charIter != mEnemies.end())
                {
                    while( iter2 != attackArea.end() && ((*iter2)) != ((*charIter)->GetPoint()))
                    {
                        iter2++;
                    }
                    if( iter2 != attackArea.end() && ((*iter2)) == ((*charIter)->GetPoint()) && !((*charIter)->IsDead()))
                    {
                        mAttackArea = attackArea;
                        mState = ATTACK;
                        return mCurChar;
                    }
                    iter2 = attackArea.begin();
                    charIter++;
                }
                mCurChar->Exhaust();
                mState = FREE;
                return NULL;
            }
            else if (mCurChar->GetClassName() == "Healer")
            {
                vector<Point> healArea = mCurChar->CalcAction();
                vector<Character*>::iterator charIter;
                vector<Point>::iterator iter2;
                iter2 = healArea.begin();
                charIter = mParty.begin();
                //check if enemies are in range, if not exhaust character
                while(charIter != mParty.end())
                {
                    while( ((*iter2)) != ((*charIter)->GetPoint()) && iter2 != healArea.end())
                    {
                        iter2++;
                    }
                    if(iter2 != healArea.end() && ((*iter2)) == ((*charIter)->GetPoint()) && !((*charIter)->IsDead()))
                    {
                        mAttackArea = healArea;
                        mState = ATTACK;
                        return mCurChar;
                    }
                    iter2 = healArea.begin();
                    charIter++;
                }
                mCurChar->Exhaust();
                mState = FREE;
                return NULL;
            }
            else
            {
            	tacAssert( false );
            	return NULL;
                //stub for future implementation
            }
    }
    else
    {
        if(mCurChar->GetClassName() != "Healer")
        {
            vector<Point>::iterator iter;
            vector<Point> attackArea = mCurChar->CalcAction();
            vector<Character*>::iterator charIter;
            vector<Point>::iterator iter2;
            iter2 = attackArea.begin();
            charIter = mEnemies.begin();
            while(iter2 != attackArea.end() && (*iter2) != p)
            {
                iter2++;
            }
            if(iter2 != attackArea.end() && (*iter2) == p)
            {
                while(charIter != mEnemies.end() && (*charIter)->GetPoint() != p)
                {
                    charIter++;
                }
                if( charIter != mEnemies.end() && (*charIter) != NULL && p == ((*charIter)->GetPoint()) && !((*charIter)->IsDead()))
                    {
                        mCurChar->Attack((*charIter));
                        mState = FREE;
                        return NULL;
                    }
                else
                {
                    return mCurChar;
                }
            }
            else
            {
                return mCurChar;
            }
        }
        else if(mCurChar->GetClassName() == "Healer")
        {
            vector<Point>::iterator iter;
            vector<Point> healArea = mCurChar->CalcAction();
            vector<Character*>::iterator charIter;
            vector<Point>::iterator iter2;
            iter2 = healArea.begin();
            charIter = mParty.begin();
            while(iter2 != healArea.end() && (*iter2) != p)
            {
                iter2++;
            }
            if(iter2 != healArea.end() && (*iter2) == p)
            {
                while(charIter != mParty.end() && (*charIter)->GetPoint() != p)
                {
                    charIter++;
                }
                if( charIter != mParty.end() && (*charIter) != NULL && p == ((*charIter)->GetPoint()) && !((*charIter)->IsDead()))
                {
                    //we know it's a healer
                    ((Healer*)mCurChar)->Heal((*charIter));
                    mState = FREE;
                    return NULL;
                }
                else
                {
                    return mCurChar;
                }
            }
            else
            {
                return mCurChar;
            }
        }
        else
        {
            tacAssert( false );
            return NULL;
            //stub for later implementation
        }
    }
    tacAssert( false );
    return NULL;
}

Character* Level::OnAISelect(Point p)
{
    //Need to select a character
    if(mState == AIFREE)
    {
        vector<Character*>::iterator iter;
        iter = mEnemies.begin();
        while( iter != mEnemies.end() && ((*iter)->GetPoint()) != p)
        {
            iter++;
        }
        if( *iter != NULL && iter != mEnemies.end() && !((*iter)->GetExhaust()) && (*iter)->GetPoint() == p)
        {
            mCurChar = (*iter);
            mState = AIMOVE;
            return *iter;
        }
        else
        {
            return NULL;
        }
    }
    //Need to move
    else if(mState == AIMOVE)
    {
            mCurChar->Move(p);
            cout << "Attacker " << mCurChar->GetName()  <<" (" << mCurChar->GetClassName() << ") moving to: " << mCurChar->GetPoint().GetX() << "," << mCurChar->GetPoint().GetY() << endl;
            if(mCurChar->GetClassName() != "Healer")
            {
                vector<Point> attackArea = mCurChar->CalcAction();
                vector<Character*>::iterator charIter;
                vector<Point>::iterator iter2;
                iter2 = attackArea.begin();
                charIter = mParty.begin();
                //check if enemies are in range, if not exhaust character
                while(charIter != mParty.end())
                {
                    while( ((*iter2)) != ((*charIter)->GetPoint()) && iter2 != attackArea.end())
                    {
                        iter2++;
                    }
                    if(iter2 != attackArea.end() && ((*iter2)) == ((*charIter)->GetPoint()) && !((*charIter)->IsDead()))
                    {
                        mAttackArea = attackArea;
                        mState = AIATTACK;
                        return mCurChar;
                    }
                    iter2 = attackArea.begin();
                    charIter++;
                }
                mCurChar->Exhaust();
                mState = AIFREE;
                return NULL;
            }
            else if (mCurChar->GetClassName() == "Healer")
            {
                vector<Point> healArea = mCurChar->CalcAction();
                vector<Character*>::iterator charIter;
                vector<Point>::iterator iter2;
                iter2 = healArea.begin();
                charIter = mEnemies.begin();
                //check if enemies are in range, if not exhaust character
                while(charIter != mEnemies.end())
                {
                    while( ((*iter2)) != ((*charIter)->GetPoint()) && iter2 != healArea.end())
                    {
                        iter2++;
                    }
                    if(iter2 != healArea.end() && ((*iter2)) == ((*charIter)->GetPoint()) && !((*charIter)->IsDead()))
                    {
                        mAttackArea = healArea;
                        mState = AIATTACK;
                        return mCurChar;
                    }
                    iter2 = healArea.begin();
                    charIter++;
                }
                mCurChar->Exhaust();
                mState = AIFREE;
                return NULL;
            }
            else
            {
            	tacAssert( false );
            	return NULL;
                //stub for future implementation
            }
    }
    else
    {
        if(mCurChar->GetClassName() != "Healer")
        {
            vector<Point>::iterator iter;
            vector<Point> attackArea = mCurChar->CalcAction();
            vector<Character*>::iterator charIter;
            vector<Point>::iterator iter2;
            iter2 = attackArea.begin();
            charIter = mParty.begin();
            while(iter2 != attackArea.end() && (*iter2) != p)
            {
                iter2++;
            }
            if(iter2 != attackArea.end() && (*iter2) == p)
            {
                while(charIter != mParty.end() && (*charIter)->GetPoint() != p)
                {
                    charIter++;
                }
                if( charIter != mParty.end() && (*charIter) != NULL && p == ((*charIter)->GetPoint()) && !((*charIter)->IsDead()))
                    {
                        mCurChar->Attack((*charIter));
                        mState = AIFREE;
                        return NULL;
                    }
                else
                {
                    return mCurChar;
                }
            }
            else
            {
                return mCurChar;
            }
        }
        else if(mCurChar->GetClassName() == "Healer")
        {
            vector<Point>::iterator iter;
            vector<Point> healArea = mCurChar->CalcAction();
            vector<Character*>::iterator charIter;
            vector<Point>::iterator iter2;
            iter2 = healArea.begin();
            charIter = mEnemies.begin();
            while(iter2 != healArea.end() && (*iter2) != p)
            {
                iter2++;
            }
            if(iter2 != healArea.end() && (*iter2) == p)
            {
                while(charIter != mEnemies.end() && (*charIter)->GetPoint() != p)
                {
                    charIter++;
                }
                if( charIter != mEnemies.end() && (*charIter) != NULL && charIter != mEnemies.end() && p == ((*charIter)->GetPoint()) && !((*charIter)->IsDead()))
                {
                    //we know it's a healer
                    ((Healer*)mCurChar)->Heal((*charIter));
                    mState = AIFREE;
                    return NULL;
                }
                else
                {
                    return mCurChar;
                }
            }
            else
            {
                return mCurChar;
            }
        }
        else
        {
            //stub for later implementation
        }
    }
    tacAssert( false );
    return NULL;
}
//============================= ACCESS     ===================================
//============================= INQUIRY    ===================================
    int Level::ReturnState()
    {
        return mState;
    }

    bool Level::GetTurn()
    {
        return mMyTurn;
    }

    bool Level::GetLoseCondition()
    {
        vector<Character*>::iterator iter;

        iter = mParty.begin();

        unsigned int allDead = 0;

        while(iter != mParty.end())
        {
            if((*iter)->IsDead())
            {
                allDead++;
            }
            iter ++;
        }
        if(allDead == mParty.size())
        {
            return true;
        }
        return false;
    }
    bool Level::GetWinCondition()
    {
        vector<Character*>::iterator iter;

        iter = mEnemies.begin();

        unsigned int allDead = 0;

        while(iter != mEnemies.end())
        {
            if((*iter)->IsDead())
            {
                allDead++;
            }
            iter++;
        }
        if(allDead == mEnemies.size())
        {
            return true;
        }
        return false;
    }
    vector<Character*> Level::GetEveryone()
    {
        vector<Character*> temp = mParty;
        temp.insert(temp.end(),mEnemies.begin(),mEnemies.end());
        return temp;
    }

    vector<Point> Level::GetAttackArea()
    {
        return mAttackArea;
    }

    bool Level::AllExhaustedParty()
    {
        vector<Character*>::iterator iter;
        iter = mParty.begin();
        unsigned int count = 0;
        while(iter != mParty.end())
        {
            if((*iter)->GetExhaust())
            {
                count++;
            }
            iter++;
        }
        if(count == mParty.size())
        {
            TakeTurn();
            return true;
        }
        return false;
    }

    bool Level::AllExhaustedEnemies()
    {
        vector<Character*>::iterator iter;
        iter = mEnemies.begin();
        unsigned int count = 0;
        while(iter != mEnemies.end())
        {
            if((*iter)->GetExhaust())
            {
                count++;
            }
            iter++;
        }
        if(count == mEnemies.size())
        {
            TakeTurn();
            return true;
        }
        return false;
    }

    Character* Level::PointHasPerson(Point p)
    {
        vector<Character*>::iterator iter;
        iter = mEnemies.begin();
        while(iter!=mEnemies.end() && (*iter)->GetPoint() != p)
        {
            iter++;
        }
        if(iter!=mEnemies.end() && (*iter)->GetPoint() == p && (*iter)->IsDead())
        {
            return (*iter);
        }
        return NULL;
    }

    Character* Level::AIPointHasPerson(Point p)
    {
        vector<Character*>::iterator iter;
        iter = mParty.begin();
        while(iter!=mParty.end() && (*iter)->GetPoint() != p)
        {
            iter++;
        }
        if(iter!=mParty.end() && (*iter)->GetPoint() == p && (*iter)->IsDead())
        {
            return (*iter);
        }
        return NULL;
    }

    vector<Character*> Level::GetEnemies()
    {
        return mEnemies;
    }

    vector<Character*> Level::GetParty()
    {
        return mParty;
    }
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
