/**
 * File: Level.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Mike Malyuk, February 11, 2007 | Initial Implementation
 * Mike Malyuk, February 12, 2007 | Added getters for UI
 */
#include "Level.h"                                // class implemented


/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

Level::Level()
{
}// Level

Level::Level(vector<Character*> party, vector<Character*> badguys, vector<Point> start, Map* map)
: mParty(party), mEnemies(badguys), mStart(start), mState(FREE), mThisMap(map), mMyTurn(true)
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
        if(((*iter)) != NULL && !((*iter)->GetExhaust()))
        {
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
