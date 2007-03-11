/**
 * File: UIOverMapCursor.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, March 4, 2007 | Initial Creation
 * Karl Schmidt, March 9 2007	 | Changed textures to png
 */
#include "UIOverMapCursor.h"                                // class implemented


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
