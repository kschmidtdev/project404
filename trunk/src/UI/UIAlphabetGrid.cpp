/**
 * File: UIAlphabetGrid.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, March 20 2007 | Initial Creation
 * Karl Schmidt, March 22 2007   | Correcting include orders and paths
 * Karl Schmidt, March 23 2007   | Got rid of more using namespace std; usage
 * Andrew Osborne, March 23 2007 | Added start offset and background image (also made small position adjustments)
 *                                  and font colour change
 * Andrew Osborne, March 23 2007 | Added fix to prevent crash when 'main string' is set to nothing ("")
 */

#include "UIAlphabetGrid.h"                                // class implemented

#include <util.h>

#include <UI/UIManager.h>
#include <ResourceManager/ResourceManager.h>


/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

UIAlphabetGrid::UIAlphabetGrid()
//: mAlphabet( "abcdefghijklmnopqrstuvwxyz" ), mCapitalAlphabet( "ABCDEFGHIJKLMNOPQRSTUVWXYZ" ),
: mCursor( NULL ), mCursorPos( Point(0,0) ),
mFontSize( 36 ), mFontRed ( 96 ), mFontGreen( 57 ), mFontBlue( 19 ),
mGrid( Point( 6, 3 ) ), mOffset( Point( 45, 45) ), mGridStart( Point(20,20) )
{

    mElementImage = ResourceManager::GetInstance()->LoadTexture("alpha_back.png");

    mAlphabet = "abcdefghijklmnopqrstuvwxyz";
    mCapitalAlphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    // Adding in 26 lower case letters
    std::string temp;

    std::string::iterator iter;
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
    for( UITextItr i = mLetters.begin(); i != mLetters.end(); ++i )
    {
        delete *i;
    }
    mLetters.clear();

    if( mCursor )
    {
        delete mCursor;
    }
    mCursor = NULL;

}// ~UIAlphabetGrid


//============================= OPERATORS ====================================

//============================= OPERATIONS ===================================

void UIAlphabetGrid::RenderSelf(SDL_Surface* destination)
{
    UIElement::RenderSelf(destination);

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
    Point newPos = mPos + mGridStart;
    Point start = newPos;

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
    mUIResult.SetPos( mPos + mGridStart + Point( 20, ( mGrid.GetY() + 1) * mOffset.GetY() + 5 ) );

}

//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

void UIAlphabetGrid::UpdateCursor(void)
{
    mCursor->SetPos( mPos + mGridStart + Point( mCursorPos.GetX() * mOffset.GetX(), mCursorPos.GetY() * mOffset.GetY() ) );
}

void UIAlphabetGrid::AddChar(void)
{
    // find mLetters index
    std::string temp;
    unsigned int index = mCursorPos.GetX() + mCursorPos.GetY() * ( mGrid.GetX() + 1);
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

    if (mResult=="")
    {
        mUIResult.ChangeText(" ");
    }
    else
    {
        mUIResult.ChangeText(mResult);
    }
}
/////////////////////////////// PRIVATE    ///////////////////////////////////
