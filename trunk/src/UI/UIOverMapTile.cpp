/**
 * File: UIOverMapTile.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, March 4, 2007 | Initial Creation
 * Karl Schmidt, March 9 2007	 | Changed textures to png
 * Andrew Osborne, March 11 2007 | Added next/previous notion to tiles (with LevelDefeated method)
 * Andrew Osborne, March 13 2007 | Added BattleInit funcitonality
 */
#include "UIOverMapTile.h"                                // class implemented
#include "GameEngine/GameEngine.h"

/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

UIOverMapTile::UIOverMapTile()
: mNextTile( NULL ), mPrevTile( NULL ), mLeftTile( NULL ), mRightTile( NULL ),
mUpTile( NULL ), mDownTile( NULL ), mDefeated( false ), mCity( NULL )
{
    // Default image for now, should change later
    mElementImage = ResourceManager::GetInstance()->LoadTexture("charTile.png");
}// UIOverMapTile

UIOverMapTile::UIOverMapTile(int x, int y)
: mNextTile( NULL ), mPrevTile( NULL ), mLeftTile( NULL ), mRightTile( NULL ),
mUpTile( NULL ), mDownTile( NULL ), mDefeated( false ), mCity( NULL )
{
    // Default image for now, should change later
    mElementImage = ResourceManager::GetInstance()->LoadTexture("charTile.png");
    mMapOffset.Set(x,y);

}// UIOverMapTile

UIOverMapTile::UIOverMapTile(int x, int y, string fileName)
: mNextTile( NULL ), mPrevTile( NULL ), mLeftTile( NULL ), mRightTile( NULL ),
mUpTile( NULL ), mDownTile( NULL ), mDefeated( false ), mCity( NULL )
{
    // Default image for now, should change later
    mElementImage = ResourceManager::GetInstance()->LoadTexture(fileName);
    mMapOffset.Set(x,y);

}// UIOverMapTile

UIOverMapTile::UIOverMapTile(City *c)
: mNextTile( NULL ), mPrevTile( NULL ), mLeftTile( NULL ), mRightTile( NULL ),
mUpTile( NULL ), mDownTile( NULL ), mDefeated( false ), mCity( NULL )
{
    // Default image for now, should change later
    mCity = c;
    mElementImage = ResourceManager::GetInstance()->LoadTexture( "charTile.png" );
    mMapOffset = c->GetMapPos();
}


UIOverMapTile::~UIOverMapTile()
{
    mLeftTile = NULL;
    mRightTile = NULL;
    mUpTile = NULL;
    mDownTile = NULL;
}// ~UIOverMapTile


//============================= OPERATORS ====================================



//============================= OPERATIONS ===================================


void UIOverMapTile::LevelDefeated(void)
{
    if (!mDefeated)
    {

        // Allow advancement if such advancement exists
        if (mNextTile)
        {
            mNextTile->EnablePrevMove();
            EnableNextMove();
        }

        // Change current picture to that of a "victory" flag
        SDL_Surface* temp = ResourceManager::GetInstance()->LoadTexture("victory.png");
        if (temp)
            mElementImage = temp;

        // Declare level defeated
        mDefeated = true;

    }
}

void UIOverMapTile::BattleInit(void)
{
    // Battle init currently doesn't use characters...
    // And currently there's only one map....
    GameEngine::GetInstance()->BattleInit(mCity);
}

void UIOverMapTile::Update(void)
{
    if (mCity->IsDefeated())
    {
        LevelDefeated();
    }
    else
    {

    }
}

//============================= ACCESS     ===================================


void UIOverMapTile::SetLeft(UIOverMapTile* l)
{
    mLeftTile = l;
}

void UIOverMapTile::SetRight(UIOverMapTile* r)
{
    mRightTile = r;
}


void UIOverMapTile::SetUp(UIOverMapTile* u)
{
    mUpTile = u;
}


void UIOverMapTile::SetDown(UIOverMapTile* d)
{
    mDownTile = d;
}

void UIOverMapTile::SetNextPrev(UIOverMapTile* next, UIOverMapTile* prev)
{
    mNextTile = next;
    mPrevTile = prev;
}


//============================= INQUIRY    ===================================




UIOverMapTile* UIOverMapTile::GetLeft(void)
{
    return mLeftTile;
}


UIOverMapTile* UIOverMapTile::GetRight(void)
{
    return mRightTile;
}


UIOverMapTile* UIOverMapTile::GetUp(void)
{
    return mUpTile;
}


UIOverMapTile* UIOverMapTile::GetDown(void)
{
    return mDownTile;
}

Point UIOverMapTile::GetMapOffset(void)
{
    return mMapOffset;
}

/////////////////////////////// PROTECTED  ///////////////////////////////////


void UIOverMapTile::EnableNextMove(void)
{
    SetRight(mNextTile);
    SetUp(mNextTile);
}


void UIOverMapTile::EnablePrevMove(void)
{
    SetLeft(mPrevTile);
    SetDown(mPrevTile);
}

/////////////////////////////// PRIVATE    ///////////////////////////////////
