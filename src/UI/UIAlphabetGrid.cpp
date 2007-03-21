/**
 * File: UIAlphabetGrid.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, March 20 2007 | Initial Creation
 */

#include <util.h>

#include "UIAlphabetGrid.h"                                // class implemented
#include "UIManager.h"

/*

ToDo List:
Make UItext have CenterText operations (cuz it's useful)
then create a stencil (temp) image that moves around and centers
the text where it should be.

*/

/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

UIAlphabetGrid::UIAlphabetGrid()
//: mAlphabet( "abcdefghijklmnopqrstuvwxyz" ), mCapitalAlphabet( "ABCDEFGHIJKLMNOPQRSTUVWXYZ" ),
: mCursor( NULL ), mCursorPos( Point(0,0) ),
mFontSize( 36 ), mFontRed ( 255 ), mFontGreen( 0 ), mFontBlue( 0 ),
mGrid( Point( 6, 3 ) ), mOffset( Point( 45, 45) )
{

    mAlphabet = "abcdefghijklmnopqrstuvwxyz";
    mCapitalAlphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    // Adding in 26 lower case letters
    string temp;

    string::iterator iter;
    for (iter = mAlphabet.begin(); iter!= mAlphabet.end(); ++iter)
    {
        temp = (*iter);
        mLetters.push_back( new UIText( temp, mFontSize, mFontRed, mFontGreen, mFontBlue) );
    }

    // Create Cursor
    mCursor = new UIImage("tileCursor.png");

    // Result
    mResult = "";
    mUIResult.ChangeText(" ", mFontSize, mFontRed, mFontGreen, mFontBlue);

    SetPos(mPos);

}// UIAlphabetGrid


UIAlphabetGrid::~UIAlphabetGrid()
{
}// ~UIAlphabetGrid


//============================= OPERATORS ====================================

//============================= OPERATIONS ===================================

void UIAlphabetGrid::RenderSelf(SDL_Surface* destination)
{
    int size = mLetters.size();
    for (int i= 0; i<size; i++)
    {
        mLetters[i]->RenderSelf(destination);
    }

    mCursor->RenderSelf(destination);

    mUIResult.RenderSelf(destination);
}

void UIAlphabetGrid::ProcessEvent( const InputManager::INPUTKEYS evt )
{

    switch(evt)
    {
        case InputManager::UP:
            // Move cursor up
            if (mCursorPos.GetY()>0)
            {
                mCursorPos = mCursorPos + Point(0,-1);
                UpdateCursor();
            }
            break;
        case InputManager::DOWN:
            if (mCursorPos.GetY()<mGrid.GetY())
            {
                mCursorPos = mCursorPos + Point(0,1);
                UpdateCursor();
            }
            break;
        case InputManager::LEFT:
            // Move cursor up
            if (mCursorPos.GetX()>0)
            {
                mCursorPos = mCursorPos + Point(-1,0);
                UpdateCursor();
            }
            break;
        case InputManager::RIGHT:
            if (mCursorPos.GetX()<mGrid.GetX())
            {
                mCursorPos = mCursorPos + Point(1,0);
                UpdateCursor();
            }
            break;
        case InputManager::CONFIRM:
            AddChar();
            break;
        case InputManager::CANCEL:
            RemoveChar();
            break;
        case InputManager::MENU:
            UIManager::GetInstance()->PopLayout();
            UIManager::GetInstance()->PushLayout("MainMenu");
        default:
            break;

    }
}

//============================= ACCESS     ===================================


void UIAlphabetGrid::SetPos( const Point & nPos )
{
    UIElement::SetPos(nPos);

    int size = mAlphabet.size();
    Point newPos = mPos;
    Point start = mPos;

    int columnCounter = 0;
    for (int i= 0; i<size; i++)
    {
        mCursor->SetPos( newPos );
        mLetters[i]->CenterText( mCursor );
        columnCounter++;
        if (columnCounter>mGrid.GetX())
        {
            newPos = newPos + Point (0, mOffset.GetY());
            newPos.SetX( start.GetX() );
            columnCounter = 0;
        }
        else
        {
            newPos = newPos + Point( mOffset.GetX(), 0 );
        }

    }

    // Cursor position
    UpdateCursor();

    // Result String
    mUIResult.SetPos( mPos + Point( 20, ( mGrid.GetY() + 1) * mOffset.GetY() ) );

}

//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

void UIAlphabetGrid::UpdateCursor(void)
{
    mCursor->SetPos( mPos + Point( mCursorPos.GetX() * mOffset.GetX(), mCursorPos.GetY() * mOffset.GetY() ) );
}

void UIAlphabetGrid::AddChar(void)
{
    // find mLetters index
    string temp;
    int index = mCursorPos.GetX() + mCursorPos.GetY() * ( mGrid.GetX() + 1);
    if (index<mLetters.size())
    {
        temp = mAlphabet[index];
        mResult += temp;
    }

    mUIResult.ChangeText(mResult);

}

void UIAlphabetGrid::RemoveChar(void)
{

    if (mResult.size()==1)
    {
        mResult = "";
    }
    else if (mResult.size()>1)
    {
        mResult = mResult.substr(0, mResult.size()-1);
    }

    mUIResult.ChangeText(mResult);

}
/////////////////////////////// PRIVATE    ///////////////////////////////////
