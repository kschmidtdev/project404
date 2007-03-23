/**
 * File: UIOverMapCursor.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, March 4, 2007 | Initial Creation
 * Karl Schmidt, March 9 2007	 | Changed textures to png
 * Karl Schmidt, March 22 2007   | Correcting include orders and paths
 */

#include "UIOverMapCursor.h"                                // class implemented

#include <util.h>

#include <ResourceManager/ResourceManager.h>
#include <UI/UIOverMapTile.h>


/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

UIOverMapCursor::UIOverMapCursor()
: mOffset( Point(0,0) )
{
    mElementImage = ResourceManager::GetInstance()->LoadTexture("tileCursor.png");
}// UIOverMapCursor



UIOverMapCursor::~UIOverMapCursor()
{
    mCurTile = NULL;
}// ~UIOverMapCursor


//============================= OPERATORS ====================================



//============================= OPERATIONS ===================================
//============================= ACCESS     ===================================


void UIOverMapCursor::SetCurTile(UIOverMapTile* nCurTile)
{
    mCurTile = nCurTile;
    mPos = mCurTile->GetPos() + mOffset;
}

//============================= INQUIRY    ===================================


UIOverMapTile* UIOverMapCursor::GetCurTile(void)
{
    return mCurTile;
}


/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
