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
 * Karl Schmidt, February 14, 2007 | Fixed healer crash bug/bugnonetheless
 * Mike Malyuk, February 15, 2007 | Fixed more bugs, now shouldn't crash. Runs 2p til we implement AI
 *                                | Move range and Attack range don't show up for enemies (bug)
 */
#include "Level.h"                                // class implemented
//#include "Character.h"
#include "Archer.h"
#include "Knight.h"
#include "Healer.h"
#include "Mage.h"
#include "../Database/DBEngine.h"


/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

Level::Level()
: mState( FREE ), mMyTurn( true )
{
    // Useful point variables
    Point tempPoint(0,0);
    int xStart=0;
    int yBadStart=9;
    int yGoodStart=0;

    // Load party (player - good guys)
    //----------------------------------------------------------
    Character* tempChar;
    //std:vector<Character*> tempParty;

    // Archer
    tempChar = new Archer();
    tempPoint.Set(xStart, yGoodStart);
    tempChar->Move( tempPoint );
    mParty.push_back(tempChar);
    xStart++;

    // Knight
    tempChar = new Knight();
    tempPoint.Set(xStart, yGoodStart);
    tempChar->Move( tempPoint );
    mParty.push_back(tempChar);
    xStart++;

    // Healer
    tempChar = new Healer();
    tempPoint.Set(xStart, yGoodStart);
    tempChar->Move( tempPoint );
    mParty.push_back(tempChar);
    xStart++;

    // Mage
    tempChar = new Mage();
    tempPoint.Set(xStart, yGoodStart);
    tempChar->Move( tempPoint );
    mParty.push_back(tempChar);

    xStart = 0;

    // Create bad guys
    // ---------------------------------------------------
    //std:vector<Character*> tempBadGuys;

    // Archer
    tempChar = new Archer();
    tempPoint.Set(xStart, yBadStart);
    tempChar->Move( tempPoint );
    mEnemies.push_back(tempChar);
    xStart++;

    // Knight
    tempChar = new Knight();
    tempPoint.Set(xStart, yBadStart);
    tempChar->Move( tempPoint );
    mEnemies.push_back(tempChar);
    xStart++;

    // Healer
    tempChar = new Healer();
    tempPoint.Set(xStart, yBadStart);
    tempChar->Move( tempPoint );
    mEnemies.push_back(tempChar);
    xStart++;

    // Mage
    tempChar = new Mage();
    tempPoint.Set(xStart, yBadStart);
    tempChar->Move( tempPoint );
    mEnemies.push_back(tempChar);
    //std:vector<Character*> tempBad;


    /*vector<Character*>::iterator iter;
    vector<Point>::iterator piter;

    iter = mParty.begin();
    piter = mStart.begin();


    while(iter != mParty.end() && piter != mStart.end())
    {
        (*iter)->Move((*piter));
        iter++;
        piter++;
    }*/



}// Level

Level::Level(vector<Character*> party, vector<Character*> badguys, vector<Point> start, Map* map)
: mParty(party), mEnemies(badguys), mStart(start), mState(FREE), mThisMap(map), mMyTurn(true), mDefaultConstructor( false )
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

Level::Level(int)
{
    DBEngine DBE;
    DBE.Initialize();

    Point StartingPoint;
    DBVector2D* StartingVector;

    //// Party Setting ////
    vector<Character*>* PartyList = DBE.LoadParty(); // Get the pointer of party members in this level.
    vector<Character*>::iterator Iter1; // Iterator.
    for (Iter1 = PartyList->begin(); Iter1 != PartyList->end(); Iter1++)
    {
        StartingVector = DBE.LoadPartyStartingPoint( *Iter1 );
        StartingPoint.Set( StartingVector->GetX(), StartingVector->GetY() );
        (*Iter1)->Move( StartingPoint );
        mParty.push_back( (*Iter1) );
    }

    //// Enemies Setting ////
    vector<Character*>* EnemiesList = DBE.LoadEnemies(); // Get the pointer of enemy members in this level.
    vector<Character*>::iterator Iter2; // Iterator.
    for (Iter2 = EnemiesList->begin(); Iter2 != EnemiesList->end(); Iter2++)
    {
        StartingVector = DBE.LoadEnemiesStartingPoint( *Iter2 );
        StartingPoint.Set( StartingVector->GetX(), StartingVector->GetY() );
        (*Iter2)->Move( StartingPoint );
        mEnemies.push_back( (*Iter2) );
    }

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
        if( *iter != NULL && iter != mParty.end() && !((*iter)->GetExhaust()) && (*iter)->GetPoint() == p)
        {
            mCurChar = (*iter);
            mState = MOVE;
            mMoveArea.clear();
            GetMovement();
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
        vector<Point>::iterator iter;
        iter = mMoveArea.begin();
        while( (*iter) != p && iter != mMoveArea.end())
        {
            iter++;
        }

        if(iter != mMoveArea.end() && (*iter) == p)
        {
            mCurChar->Move(p);
            cout << "Attacker " << mCurChar->GetName()  <<" (" << mCurChar->GetClassName() << ") moving to: " << mCurChar->GetPoint().GetX() << "," << mCurChar->GetPoint().GetY() << endl;
            if(mCurChar->GetClassName() != "Healer")
            {
                vector<Point> attackarea = mCurChar->CalcAction();
                vector<Character*>::iterator chariter;
                vector<Point>::iterator iter2;
                iter2 = attackarea.begin();
                chariter = mEnemies.begin();
                //check if enemies are in range, if not exhaust character
                while(chariter != mEnemies.end())
                {
                    while( ((*iter2)) != ((*chariter)->GetPoint()) && iter2 != attackarea.end())
                    {
                        iter2++;
                    }
                    if(iter2 != attackarea.end() && ((*iter2)) == ((*chariter)->GetPoint()) && !((*chariter)->IsDead()))
                    {
                        mAttackArea = attackarea;
                        mState = ATTACK;
                        return mCurChar;
                    }
                    iter2 = attackarea.begin();
                    chariter++;
                }
                mCurChar->Exhaust();
                mState = FREE;
                return NULL;
            }
            else if (mCurChar->GetClassName() == "Healer")
            {
                vector<Point> healarea = mCurChar->CalcAction();
                vector<Character*>::iterator chariter;
                vector<Point>::iterator iter2;
                iter2 = healarea.begin();
                chariter = mParty.begin();
                //check if enemies are in range, if not exhaust character
                while(chariter != mParty.end())
                {
                    while( ((*iter2)) != ((*chariter)->GetPoint()) && iter2 != healarea.end())
                    {
                        iter2++;
                    }
                    if(iter2 != healarea.end() && ((*iter2)) == ((*chariter)->GetPoint()) && !((*chariter)->IsDead()))
                    {
                        mAttackArea = healarea;
                        mState = ATTACK;
                        return mCurChar;
                    }
                    iter2 = healarea.begin();
                    chariter++;
                }
                mCurChar->Exhaust();
                mState = FREE;
                return NULL;
            }
            else
            {
                //stub for future implementation
            }

        }
        else
        {
            return mCurChar;
        }
        mMoveArea.clear();
    }
    else
    {
        if(mCurChar->GetClassName() != "Healer")
        {
            vector<Point>::iterator iter;
            vector<Point> attackarea = mCurChar->CalcAction();
            vector<Character*>::iterator chariter;
            vector<Point>::iterator iter2;
            iter2 = attackarea.begin();
            chariter = mEnemies.begin();
            while(iter2 != attackarea.end() && (*iter2) != p)
            {
                iter2++;
            }
            if(iter2 != attackarea.end() && (*iter2) == p)
            {
                while(chariter != mEnemies.end() && (*chariter)->GetPoint() != p)
                {
                    chariter++;
                }
                if( chariter != mEnemies.end() && (*chariter) != NULL && p == ((*chariter)->GetPoint()) && !((*chariter)->IsDead()))
                    {
                        mCurChar->Attack((*chariter));
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
                if( charIter != mParty.end() && (*charIter) != NULL && charIter != mParty.end() && p == ((*charIter)->GetPoint()) && !((*charIter)->IsDead()))
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
            //stub for later implementation
        }
    }
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
            mMoveArea.clear();
            GetMovement();
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
        vector<Point>::iterator iter;
        iter = mMoveArea.begin();
        while( (*iter) != p && iter != mMoveArea.end())
        {
            iter++;
        }

        if(iter!= mMoveArea.end() && (*iter) == p)
        {
            mCurChar->Move(p);
            cout << "Attacker " << mCurChar->GetName()  <<" (" << mCurChar->GetClassName() << ") moving to: " << mCurChar->GetPoint().GetX() << "," << mCurChar->GetPoint().GetY() << endl;
            if(mCurChar->GetClassName() != "Healer")
            {
                vector<Point> attackarea = mCurChar->CalcAction();
                vector<Character*>::iterator chariter;
                vector<Point>::iterator iter2;
                iter2 = attackarea.begin();
                chariter = mParty.begin();
                //check if enemies are in range, if not exhaust character
                while(chariter != mParty.end())
                {
                    while( ((*iter2)) != ((*chariter)->GetPoint()) && iter2 != attackarea.end())
                    {
                        iter2++;
                    }
                    if(iter2 != attackarea.end() && ((*iter2)) == ((*chariter)->GetPoint()) && !((*chariter)->IsDead()))
                    {
                        mAttackArea = attackarea;
                        mState = AIATTACK;
                        return mCurChar;
                    }
                    iter2 = attackarea.begin();
                    chariter++;
                }
                mCurChar->Exhaust();
                mState = AIFREE;
                return NULL;
            }
            else if (mCurChar->GetClassName() == "Healer")
            {
                vector<Point> healarea = mCurChar->CalcAction();
                vector<Character*>::iterator chariter;
                vector<Point>::iterator iter2;
                iter2 = healarea.begin();
                chariter = mEnemies.begin();
                //check if enemies are in range, if not exhaust character
                while(chariter != mEnemies.end())
                {
                    while( ((*iter2)) != ((*chariter)->GetPoint()) && iter2 != healarea.end())
                    {
                        iter2++;
                    }
                    if(iter2 != healarea.end() && ((*iter2)) == ((*chariter)->GetPoint()) && !((*chariter)->IsDead()))
                    {
                        mAttackArea = healarea;
                        mState = AIATTACK;
                        return mCurChar;
                    }
                    iter2 = healarea.begin();
                    chariter++;
                }
                mCurChar->Exhaust();
                mState = AIFREE;
                return NULL;
            }
            else
            {
                //stub for future implementation
            }

        }

        else
        {
            return mCurChar;
        }
        mMoveArea.clear();
    }
    else
    {
        if(mCurChar->GetClassName() != "Healer")
        {
            vector<Point>::iterator iter;
            vector<Point> attackarea = mCurChar->CalcAction();
            vector<Character*>::iterator chariter;
            vector<Point>::iterator iter2;
            iter2 = attackarea.begin();
            chariter = mParty.begin();
            while(iter2 != attackarea.end() && (*iter2) != p)
            {
                iter2++;
            }
            if(iter2 != attackarea.end() && (*iter2) == p)
            {
                while(chariter != mParty.end() && (*chariter)->GetPoint() != p)
                {
                    chariter++;
                }
                if( chariter != mParty.end() && (*chariter) != NULL && p == ((*chariter)->GetPoint()) && !((*chariter)->IsDead()))
                    {
                        mCurChar->Attack((*chariter));
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
                if( charIter != mEnemies.end() && (*charIter) != NULL && charIter != mParty.end() && p == ((*charIter)->GetPoint()) && !((*charIter)->IsDead()))
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
}
//============================= ACCESS     ===================================
//============================= INQUIRY    ===================================
    int Level::ReturnState()
    {
        return mState;
    }

    void Level::GetMovement()
    {
        int move = (mCurChar->GetAttr(Character::AGI))/2;
        int x = mCurChar->GetPoint().GetX();
        int y = mCurChar->GetPoint().GetY();
        for(int i = move; i >=0; i--)
        {
            mMoveArea.push_back(Point(x+(move-i), y+i));
            mMoveArea.push_back(Point(x-(move-i),y-i));
            if(i != move && i != 0)
            {
                mMoveArea.push_back(Point(x+(move-i), y-i));
                mMoveArea.push_back(Point(x-(move-i),y+i));
            }

        }

        GetMovementHelp(move-1, x, y);
    }

    void Level::GetMovementHelp(int move, int x, int y)
    {
        if(move == 0)
        {
            vector<Character*> chars = GetEveryone();
            vector<Character*>::iterator iter;
            vector<Point>::iterator piter;
            piter = mMoveArea.begin();
            iter = chars.begin();
            while(iter != chars.end())
            {
                while( ((*piter)) != ((*iter)->GetPoint()) && piter != mMoveArea.end())
                {
                    piter++;
                }
                if(piter != mMoveArea.end() && ((*piter)) == ((*iter)->GetPoint()) && !((*iter)->IsDead()))
                {
                    mMoveArea.erase(piter);
                }
                piter = mMoveArea.begin();
                iter++;
            }
            mMoveArea.push_back(Point(x,y));
            return;
        }
        else
        {

            for(int i = move; i >=0; i--)
            {
                mMoveArea.push_back(Point(x+(move-i), y+i));
                mMoveArea.push_back(Point(x-(move-i),y-i));
                if(i != move && i != 0)
                {
                    mMoveArea.push_back(Point(x+(move-i), y-i));
                    mMoveArea.push_back(Point(x-(move-i),y+i));
                }
            }
            GetMovementHelp(move-1, x, y);
        }
    }

    Map* Level::GetMap()
    {
        return mThisMap;
    }

    bool Level::GetTurn()
    {
        return mMyTurn;
    }

    bool Level::GetLoseCondition()
    {
        vector<Character*>::iterator iter;

        iter = mParty.begin();

        int allDead = 0;

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

        int allDead = 0;

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

    vector<Point> Level::GetMoveArea()
    {
        return mMoveArea;
    }

    vector<Point> Level::GetAttackArea()
    {
        return mAttackArea;
    }

    bool Level::AllExhaustedParty()
    {
        vector<Character*>::iterator iter;
        iter = mParty.begin();
        int count = 0;
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
        int count = 0;
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
