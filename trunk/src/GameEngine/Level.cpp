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
 *									 in the current default constructor
 */
#include "Level.h"                                // class implemented
//#include "Character.h"
#include "Archer.h"
#include "Knight.h"
#include "Healer.h"
#include "Mage.h"


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

Level::~Level()
{
}// ~Level

//============================= OPERATIONS ===================================
void Level::TakeTurn()
{
    if(mMyTurn == true)
    {
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
            cout << ((*iter))->GetPoint().GetX() << endl;
            mCurChar = (*iter);
            mState = MOVE;
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
        mMoveArea.clear();
        if((*iter) == p)
        {
            mCurChar->Move(p);

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
                if(((*iter2)) == ((*chariter)->GetPoint()) && !((*chariter)->IsDead()))
                {
                    mAttackArea = attackarea;
                    mState = ATTACK;
                    return mCurChar;
                }
                chariter++;
            }
            mCurChar->Exhaust();
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
        if((*iter2) == p)
        {
            while(chariter != mEnemies.end() && (*chariter)->GetPoint() != p)
            {
                chariter++;
            }
            if( (*chariter) != NULL && p == ((*chariter)->GetPoint()) && !((*chariter)->IsDead()))
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
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
