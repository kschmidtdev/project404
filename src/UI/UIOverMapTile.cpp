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
 * Karl Schmidt, March 22 2007   | Correcting include orders and paths
 * Karl Schmidt, March 29 2007   | Added correct superclass constructor calling
 */
#include "UIOverMapTile.h"                                // class implemented

#include <util.h>

#include <GameEngine/GameEngine.h>
#include <ResourceManager/ResourceManager.h>

/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

UIOverMapTile::UIOverMapTile()
: UIElement(), mNextTile( NULL ), mPrevTile( NULL ), mLeftTile( NULL ), mRightTile( NULL ),
mUpTile( NULL ), mDownTile( NULL ), mDefeated( false ), mCity( NULL ),
mCityFileName( "charTile.png" ), mVictoryFileName( "victory.png" )
{
    // Default image for now, should change later
    mElementImage = ResourceManager::GetInstance()->LoadTexture("charTile.png");
}// UIOverMapTile

UIOverMapTile::UIOverMapTile(int x, int y)
: UIElement(), mNextTile( NULL ), mPrevTile( NULL ), mLeftTile( NULL ), mRightTile( NULL ),
mUpTile( NULL ), mDownTile( NULL ), mDefeated( false ), mCity( NULL ),
mCityFileName( "charTile.png" ), mVictoryFileName( "victory.png" )
{
    // Default image for now, should change later
    mElementImage = ResourceManager::GetInstance()->LoadTexture(mCityFileName);
    mMapOffset.Set(x,y);

}// UIOverMapTile

UIOverMapTile::UIOverMapTile(int x, int y, string fileName)
: UIElement(), mNextTile( NULL ), mPrevTile( NULL ), mLeftTile( NULL ), mRightTile( NULL ),
mUpTile( NULL ), mDownTile( NULL ), mDefeated( false ), mCity( NULL ),
mCityFileName( "charTile.png" ), mVictoryFileName( "victory.png" )
{
    // Default image for now, should change later
    mElementImage = ResourceManager::GetInstance()->LoadTexture(mCityFileName);
    mMapOffset.Set(x,y);

}// UIOverMapTile

UIOverMapTile::UIOverMapTile(City *c)
: UIElement(), mNextTile( NULL ), mPrevTile( NULL ), mLeftTile( NULL ), mRightTile( NULL ),
mUpTile( NULL ), mDownTile( NULL ), mDefeated( false ), mCity( NULL ),
mCityFileName( "charTile.png" ), mVictoryFileName( "victory.png" )
{
    // Default image for now, should change later
    mCity = c;
    mElementImage = ResourceManager::GetInstance()->LoadTexture( mCityFileName );
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

void UIOverMapTile::LevelUndefeated(void)
{
    if (mDefeated)
    {
        // Allow advancement if such advancement exists
        if (mNextTile)
        {
            mNextTile->DisablePrevMove();
            DisableNextMove();
        }

        // Change current picture to that of a "victory" flag
        SDL_Surface* temp = ResourceManager::GetInstance()->LoadTexture(mCityFileName);
        if (temp)
            mElementImage = temp;

        // Declare level defeated
        mDefeated = false;

    }

}

void UIOverMapTile::BattleInit(void)
{
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
        LevelUndefeated();
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

/*void UIOverMapTile::SetScroll(UIScrollText* s)
{
    mSroll = s;
}*/

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

void UIOverMapTile::DisableNextMove(void)
{
    SetRight(NULL);
    SetUp(NULL);
}


void UIOverMapTile::DisablePrevMove(void)
{
    SetLeft(NULL);
    SetDown(NULL);
}
/////////////////////////////// PRIVATE    ///////////////////////////////////
