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
 * Andrew Osborne, March 24 2007 | Made UIEventListener 'compatable' (added Enable, Disable)
 * Andrew Osborne, March 24 2007 | Created functionality to allow you to specify what is done upon pressing the 'cancel' button
 * Mike Malyuk,    March 31 2007 | Added DONE and MENU to alphabet. Fixed Crash error. Removed unused params
 *                               | Repositioned, used proper checks for mLetters.
 */

#include "UIAlphabetGrid.h"                                // class implemented

#include <util.h>
#include <iostream>
#include <UI/UIManager.h>
#include <ResourceManager/ResourceManager.h>
#include <UI/UILayout.h>
#include <SecurityManager.h>
#include <Database/DBEngine.h>


/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

UIAlphabetGrid::UIAlphabetGrid()
//: mAlphabet( "abcdefghijklmnopqrstuvwxyz" ), mCapitalAlphabet( "ABCDEFGHIJKLMNOPQRSTUVWXYZ" ),
: mCursor( NULL ), mCursorPos( Point(0,0) ),
mFontSize( 36 ), mFontRed ( 96 ), mFontGreen( 57 ), mFontBlue( 19 ),
mGrid( Point( 6, 4 ) ), mOffset( Point( 45, 45) ), mGridStart( Point(30,20) )
{

    mElementImage = ResourceManager::GetInstance()->LoadTexture("alpha_back.png");
    mAlphabet = "abcdefghijklmnopqrstuvwxyz";

    // Adding in 26 lower case letters
    std::string temp;

    std::string::iterator iter;
    for (iter = mAlphabet.begin(); iter!= mAlphabet.end(); ++iter)
    {
        temp = (*iter);
        mLetters.push_back( new UIText( temp, mFontSize, mFontRed, mFontGreen, mFontBlue) );
    }
    mLetters.push_back( new UIText("", 16, mFontRed, mFontGreen, mFontBlue ) );
    mLetters.push_back( new UIText("", 16, mFontRed, mFontGreen, mFontBlue ) );
    mLetters.push_back( new UIText("MAIN", 16, mFontRed, mFontGreen, mFontBlue ) );
    mLetters.push_back( new UIText("", 16, mFontRed, mFontGreen, mFontBlue ) );
    mLetters.push_back( new UIText("", 16, mFontRed, mFontGreen, mFontBlue ) );
    mLetters.push_back( new UIText("", 16, mFontRed, mFontGreen, mFontBlue ) );
    mLetters.push_back( new UIText("", 16, mFontRed, mFontGreen, mFontBlue ) );
    mLetters.push_back( new UIText("", 16, mFontRed, mFontGreen, mFontBlue ) );
    mLetters.push_back( new UIText("DONE", 16, mFontRed, mFontGreen, mFontBlue ) );
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
            std::cout << mCursorPos.GetX() << ", " << mCursorPos.GetY() << std::endl;
            if(mCursorPos == Point(6,4))
            {
                // Don't allow them to proceed if they didn't enter anything
                // We should really tell them they did something wrong when this occurs
                if( GetString() == "" || GetString() == " " )
                {

                }
                else{
                    if( SecurityManager::GetInstance()->GetUserHash( GetString() ) == "" )
                    {
                        DBEngine::GetInstance()->SetCurrentProfileName( GetString() );
                        SecurityManager::GetInstance()->AddUser( DBEngine::GetInstance()->GetCurrentProfileName(), "rrrr" );
                    }

                    UIManager::GetInstance()->PopLayout();
                    UIManager::GetInstance()->PushLayout("MainMenu");
                }
            }
            else if(mCursorPos == Point(0,4))
            {
                UIManager::GetInstance()->PopLayout();
            }
            else if(mResult.size() < 9 && (mCursorPos.GetY() < 3 || (mCursorPos.GetY() == 3 && mCursorPos.GetX() < 5)))
            {
                AddChar();
            }
            else
            {

            }
            break;
        case InputManager::CANCEL:
            RemoveChar();
            break;
        default:
            break;

    }
}



void UIAlphabetGrid::Enable(void)
{
    if (mCursor)
        mCursor->SetVisible(true);
}

void UIAlphabetGrid::Disable(void)
{
    if (mCursor)
        mCursor->SetVisible(false);
}


//============================= ACCESS     ===================================


void UIAlphabetGrid::SetPos( const Point & nPos )
{
    UIElement::SetPos(nPos);

    int size = mLetters.size();
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
    mUIResult.SetPos( mPos + mGridStart + Point( -5, ( mGrid.GetY() + 1) * mOffset.GetY() + 5 ) );

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
    if (index<mAlphabet.size())
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
