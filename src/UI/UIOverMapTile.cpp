/**
 * File: UIOverMapTile.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, March 4, 2007 | Initial Creation
 * Karl Schmidt, March 9 2007	 | Changed textures to png
 */
#include "UIOverMapTile.h"                                // class implemented


/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

UIOverMapTile::UIOverMapTile()
: mLeftTile( NULL ), mRightTile( NULL ), mUpTile( NULL ), mDownTile( NULL ), mMapOffset( Point(0,0) )
{
    // Default image for now, should change later
    mElementImage = ResourceManager::GetInstance()->LoadTexture("charTile.png");
}// UIOverMapTile

UIOverMapTile::UIOverMapTile(int x, int y)
: mLeftTile( NULL ), mRightTile( NULL ), mUpTile( NULL ), mDownTile( NULL ), mMapOffset( Point(0,0) )
{
    // Default image for now, should change later
    mElementImage = ResourceManager::GetInstance()->LoadTexture("charTile.png");
    mMapOffset.Set(x,y);

}// UIOverMapTile

UIOverMapTile::UIOverMapTile(int x, int y, string fileName)
: mLeftTile( NULL ), mRightTile( NULL ), mUpTile( NULL ), mDownTile( NULL ), mMapOffset( Point(0,0) )
{
    // Default image for now, should change later
    mElementImage = ResourceManager::GetInstance()->LoadTexture(fileName);
    mMapOffset.Set(x,y);

}// UIOverMapTile

UIOverMapTile::~UIOverMapTile()
{
    mLeftTile = NULL;
    mRightTile = NULL;
    mUpTile = NULL;
    mDownTile = NULL;
}// ~UIOverMapTile


//============================= OPERATORS ====================================



//============================= OPERATIONS ===================================
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

/////////////////////////////// PRIVATE    ///////////////////////////////////
