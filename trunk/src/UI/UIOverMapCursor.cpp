/**
 * File: UIOverMapCursor.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, March 4, 2007 | Initial Creation
 */
#include "UIOverMapCursor.h"                                // class implemented


/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

UIOverMapCursor::UIOverMapCursor()
: mOffset( Point(-2,-2) )
{
    mElementImage = ResourceManager::GetInstance()->LoadTexture("tileCursor.bmp");
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
