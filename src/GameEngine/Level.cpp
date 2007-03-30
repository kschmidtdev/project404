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
 * Karl Schmidt, March 12 2007    | Turfed default constructor body since it's not really used anymore, and
 *									     is used in one area temporarily so it's causing memory leaks
 * Mike Malyuk, March 14 2007     | Set map in Level for evil Overlord
 * Seung Woo Han, March 14 2007   | Modified Level(int) constructor. Now This contructor takes integer value which is the battle
 *                                  number. No further changes will be made to Level(int battleNumber) I hope.
 * Seung Woo Han, March 15 2007   | ~Level modified. Previously, it shut down DBEngine which shouldn't be.
 * Karl Schmidt, March 14 2007	  | Fixed a small iterator dereferencing causing crash bug
 * Mike Malyuk, March 16 2007     | Added fix to healer, no more annoying heal others when they do not need it.
 * Karl Schmidt, March 20 2007    | Major adding of consts and reference usage, rearranging includes
 * Karl Schmidt, March 21 2007    | Added storage of the last damage and healing values from attacking/defending and healing
 * Karl Schmidt, March 22 2007    | Changed name of GetClassName
 * Mike Malyuk, March 26, 2007    | Fixed bug with enemy healer healing when not allowed
 * Mike Malyuk, March 27, 2007    | Implemented method for counting turns, used for cash evaluation
 * Karl Schmidt, March 30 2007    | Added support for mLastAttackerLevelUp (UIGrid uses to check if an attacker leveled up)
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
: mState( FREE ),
  mMyTurn( true ),
  mLastDmgInflicted( 0 ),
  mLastDmgTaken( 0 ),
  mLastHealed( 0 ),
  mLastAttackerLevelUp( 0 ),
  mTurns( 1 )
{
}// Level

Level::Level( const CharacterPtrVec & party, const CharacterPtrVec & badguys, const PointVec & start)
: mState(FREE),
  mParty(party),
  mEnemies(badguys),
  mAttackArea(),
  mStart(start),
  mCurChar(NULL),
  mMap(),
  mMyTurn(true),
  mLastDmgInflicted( 0 ),
  mLastDmgTaken( 0 ),
  mLastHealed( 0 ),
  mLastAttackerLevelUp( 0 ),
  mTurns( 1 )
{
    CharacterPtrConstItr iter = mParty.begin();
    PointConstItr piter = mStart.begin();
    while(iter != mParty.end() && piter != mStart.end())
    {
        (*iter)->Move((*piter));
        iter++;
        piter++;
    }
}

Level::Level( const int battleNumber)
: mState(FREE),
  mParty(),
  mEnemies(),
  mAttackArea(),
  mStart(),
  mCurChar( NULL ),
  mMap(),
  mMyTurn( true ),
  mLastDmgInflicted( 0 ),
  mLastDmgTaken( 0 ),
  mLastHealed( 0 ),
  mTurns( 1 )
{
    DBEngine* DBE = DBEngine::GetInstance();

    mMap = Map( DBE->LoadBattleMap( battleNumber ) );

    if( mMap.GetTiles().empty() )
    {
        return;
    }

    Point StartingPoint;
    DBVector2D* StartingVector = NULL;

    //// Party Setting ////
    CharacterPtrVec* PartyList = DBE->LoadParty( battleNumber ); // Get the pointer of party members in this level.
    CharacterPtrConstItr Iter1; // Iterator.
    for (Iter1 = PartyList->begin(); Iter1 != PartyList->end(); Iter1++)
    {
        StartingVector = DBE->LoadPartyStartingPoint( battleNumber, *Iter1 );
        StartingPoint.Set( StartingVector->GetX(), StartingVector->GetY() );
        (*Iter1)->Move( StartingPoint );
        (*Iter1)->RestoreToFullLife();
        mParty.push_back( (*Iter1) );
    }

    //// Enemies Setting ////
    CharacterPtrVec* EnemiesList = DBE->LoadEnemies( battleNumber ); // Get the pointer of enemy members in this level.
    CharacterPtrConstItr Iter2; // Iterator.
    for (Iter2 = EnemiesList->begin(); Iter2 != EnemiesList->end(); Iter2++)
    {
        StartingVector = DBE->LoadEnemiesStartingPoint( battleNumber, *Iter2 );
        StartingPoint.Set( StartingVector->GetX(), StartingVector->GetY() );
        (*Iter2)->Move( StartingPoint );
        (*Iter2)->RestoreToFullLife();
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
        CharacterPtrConstItr iter;
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
        CharacterPtrConstItr iter;
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

Character* Level::OnSelect( const Point & p )
{
    //Need to select a character
    if(mState == FREE)
    {
        CharacterPtrConstItr iter;
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
            cout << "Attacker " << mCurChar->GetName()  <<" (" << mCurChar->GetCharacterClassName() << ") moving to: " << mCurChar->GetPoint().GetX() << "," << mCurChar->GetPoint().GetY() << endl;
            if(mCurChar->GetCharacterClassName() != "Healer")
            {
                const PointVec& attackArea = mCurChar->CalcAction();
                CharacterPtrConstItr charIter;
                PointConstItr iter2;
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
            else if (mCurChar->GetCharacterClassName() == "Healer")
            {
                const PointVec& healArea = mCurChar->CalcAction();
                CharacterPtrConstItr charIter;
                PointConstItr iter2;
                iter2 = healArea.begin();
                charIter = mParty.begin();
                //check if enemies are in range, if not exhaust character
                while(charIter != mParty.end())
                {
                    while( ((*iter2)) != ((*charIter)->GetPoint()) && iter2 != healArea.end())
                    {
                        iter2++;
                    }
                    if(iter2 != healArea.end() && ((*iter2)) == ((*charIter)->GetPoint()) && !((*charIter)->IsDead()) && (*charIter)->GetHP() != (*charIter)->GetMaxHP())
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
        if(mCurChar->GetCharacterClassName() != "Healer")
        {
            PointConstItr iter;
            const PointVec& attackArea = mCurChar->CalcAction();
            CharacterPtrConstItr charIter;
            PointConstItr iter2;
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
                    Character* defender = (*charIter);
                    int attackerHealth = mCurChar->GetHP();
                    int defenderHealth = defender->GetHP();
                    int attackerLevel = mCurChar->GetLevel();

                    mCurChar->Attack( defender );

                    mLastDmgTaken = mCurChar->GetHP() - attackerHealth;
                    mLastDmgInflicted = defender->GetHP() - defenderHealth;
                    mLastAttackerLevelUp = mCurChar->GetLevel() - attackerLevel;

                    mState = FREE;
                    return defender;
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
        else if(mCurChar->GetCharacterClassName() == "Healer")
        {
            PointConstItr iter;
            const PointVec & healArea = mCurChar->CalcAction();
            CharacterPtrConstItr charIter;
            PointConstItr iter2;
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
                if( charIter != mParty.end() && (*charIter) != NULL && p == ((*charIter)->GetPoint()) && !((*charIter)->IsDead()) && (*charIter)->GetHP() != (*charIter)->GetMaxHP())
                {
                    Character* toBeHealed = (*charIter);
                    //we know it's a healer

                    int targetHealth = toBeHealed->GetHP();

                    ((Healer*)mCurChar)->Heal(toBeHealed);

                    mLastHealed = toBeHealed->GetHP() - targetHealth;

                    mState = FREE;
                    return toBeHealed;
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

Character* Level::OnAISelect( const Point & p )
{
    //Need to select a character
    if(mState == AIFREE)
    {
        CharacterPtrConstItr iter;
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
            cout << "Attacker " << mCurChar->GetName()  <<" (" << mCurChar->GetCharacterClassName() << ") moving to: " << mCurChar->GetPoint().GetX() << "," << mCurChar->GetPoint().GetY() << endl;
            if(mCurChar->GetCharacterClassName() != "Healer")
            {
                const PointVec& attackArea = mCurChar->CalcAction();
                CharacterPtrConstItr charIter;
                PointConstItr iter2;
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
            else if (mCurChar->GetCharacterClassName() == "Healer")
            {
                const PointVec & healArea = mCurChar->CalcAction();
                CharacterPtrConstItr charIter;
                PointConstItr iter2;
                iter2 = healArea.begin();
                charIter = mEnemies.begin();
                //check if enemies are in range, if not exhaust character
                while(charIter != mEnemies.end())
                {
                    while( ((*iter2)) != ((*charIter)->GetPoint()) && iter2 != healArea.end())
                    {
                        iter2++;
                    }
                    if(iter2 != healArea.end() && ((*iter2)) == ((*charIter)->GetPoint()) && !((*charIter)->IsDead())&& (*charIter)->GetHP() != (*charIter)->GetMaxHP())
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
        if(mCurChar->GetCharacterClassName() != "Healer")
        {
            PointConstItr iter;
            const PointVec& attackArea = mCurChar->CalcAction();
            CharacterPtrConstItr charIter;
            PointConstItr iter2;
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
                    Character* defender = (*charIter);
                    int attackerHealth = mCurChar->GetHP();
                    int defenderHealth = defender->GetHP();
                    int attackerLevel = mCurChar->GetLevel();

                    mCurChar->Attack( defender );

                    mLastDmgTaken = mCurChar->GetHP() - attackerHealth;
                    mLastDmgInflicted = defender->GetHP() - defenderHealth;
                    mLastAttackerLevelUp = mCurChar->GetLevel() - attackerLevel;

                    mState = AIFREE;
                    return defender;
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
        else if(mCurChar->GetCharacterClassName() == "Healer")
        {
            PointConstItr iter;
            const PointVec& healArea = mCurChar->CalcAction();
            CharacterPtrConstItr charIter;
            PointConstItr iter2;
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

                if( charIter != mEnemies.end() && (*charIter) != NULL && charIter != mEnemies.end() && p == ((*charIter)->GetPoint()) && !((*charIter)->IsDead())&& (*charIter)->GetHP() != (*charIter)->GetMaxHP())
                {
                    Character* toBeHealed = (*charIter);

                    int targetHealth = toBeHealed->GetHP();

                    //we know it's a healer
                    ((Healer*)mCurChar)->Heal( toBeHealed );

                    mLastHealed = toBeHealed->GetHP() - targetHealth;

                    mState = AIFREE;
                    return toBeHealed;
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

    const bool Level::GetTurn() const
    {
        return mMyTurn;
    }

    const bool Level::GetLoseCondition() const
    {
        unsigned int allDead = 0;
        for( CharacterPtrConstItr i = mParty.begin(); i != mParty.end(); ++i )
        {
            if( (*i)->IsDead() )
            {
                ++allDead;
            }
        }

        if( allDead == mParty.size() )
        {
            return true;
        }

        return false;
    }

    const bool Level::GetWinCondition() const
    {
        unsigned int allDead = 0;

        for( CharacterPtrConstItr i = mEnemies.begin(); i != mEnemies.end(); ++i )
        {
            if( (*i)->IsDead() )
            {
                ++allDead;
            }
        }

        if( allDead == mEnemies.size() )
        {
            return true;
        }

        return false;
    }

    const CharacterPtrVec Level::GetEveryone() const
    {
        CharacterPtrVec temp;
        temp.insert( temp.end(), mParty.begin(), mParty.end() );
        temp.insert(temp.end(),mEnemies.begin(),mEnemies.end());
        return temp;
    }

    const PointVec& Level::GetAttackArea() const
    {
        return mAttackArea;
    }

    const bool Level::AllExhaustedParty()
    {
        CharacterPtrConstItr iter;
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

    const bool Level::AllExhaustedEnemies()
    {
        CharacterPtrConstItr iter;
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
            mTurns++;
            return true;
        }
        return false;
    }

    Character* Level::PointHasPerson( const Point & p ) const
    {
        Character* charToFind = NULL;
        for( CharacterPtrConstItr i = mEnemies.begin(); i != mEnemies.end(); ++i )
        {
            if( (*i)->GetPoint() == p )
            {
                charToFind = *i;
                break;
            }
        }

        if( charToFind != NULL && charToFind->IsDead() )
        {
            return charToFind;
        }

        return NULL;
    }

    Character* Level::AIPointHasPerson( const Point & p ) const
    {
        Character* charToFind = NULL;
        for( CharacterPtrConstItr i = mParty.begin(); i != mParty.end(); ++i )
        {
            if( (*i)->GetPoint() == p )
            {
                charToFind = *i;
                break;
            }
        }

        if( charToFind != NULL && charToFind->IsDead() )
        {
            return charToFind;
        }

        return NULL;
    }

    const CharacterPtrVec& Level::GetEnemies() const
    {
        return mEnemies;
    }

    const CharacterPtrVec& Level::GetParty() const
    {
        return mParty;
    }
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
