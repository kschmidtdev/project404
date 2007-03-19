/**
 * File: UIList.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, March 18 2007 | Initial Creation
 */
#include "UIList.h"                                // class implemented


//int City::_idCount = 1;

/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

UIList::UIList(string t)
mConfirmFunc( NULL ), mCancelFunc( NULL ), mCurIndex( 0 ), mMaxIndex( 0 ),

{

    // Background image
    mElementImage = ResourceManager::GetInstance()->LoadTexture("ListBackgournd.png");

    int xStart = 7;
    int yStart = 7;
    int extraSpace = 7;
    //mFontSize = 16;

    // Title
    mTitleStart.Set(xStart, yStart); // Position relative to List
    mTitle.ChangeText(t, mFontSize, mFontRed, mFontGreen, mFontBlue);

    // Data
    mDataOffset.Set(0, mFontSize + extraSpace);

    mDataStart = mTitleStart + mDataOffset;

    // Cursor
    mCursor = new UICursor("listCursor.png", Point(-xStart, (int) -extraSpace/2 ), NULL);

    SetPos(mPos);

}// UIList


UIList::~UIList()
{
}// ~UIList


//============================= OPERATORS ====================================

//============================= OPERATIONS ===================================

void UIList::RenderSelf(SDL_Surface *destination)
{

    UIElement::RenderSelf(destination);

    mCursor.RenderSelf(destination);

    for (UITextItr iter = mUIList.begin(); iter != mUIList.end())
    {
        (*iter).RenderSelf(destination);
    }

}

void UIList::ProcessEvent( const InputManager::INPUTKEYS evt )
{

}

//============================= ACCESS     ===================================

void UIList::SetPos( const Point & nPos)
{
    UIElement::SetPos(nPos);

    mTitle.SetPos( mPos + mTitleStart );

    Point newPos = mTitle.GetPos() + mDataOffset;

    for (UITextItr iter = mUIList.begin(); iter != mUIList.end())
    {
        (*iter).SetPos( newPos );
        newPos = newPos + mDataOffset;
    }

    mCursor.UpdatePos();

}

//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
