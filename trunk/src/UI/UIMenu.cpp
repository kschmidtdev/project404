/**
 * File: UIMenu.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, February 10, 2007 | Initial creation and testing
 * Andrew Osborne, February 10, 2007 | Added some comments, deleted inputFunction
 * Andrew Osborne, February 11, 2007 | added 'm' to members, added input funcitonality, used Point addition/mult
 * Karl Schmidt, February 11 2007	 | Added checks to prevent crashes when textures are not loaded
 * Andrew Osborne, February 11, 2007 | added destructor
 * Karl Schmidt, February 14 2007 	 | Updated function capitalization, block style, typedefs, refs
 * Andrew Osborne, February 14, 2007 | added AddButton method
 * Karl Schmidt, February 15 2007 	 | Added wrap-around for navigating upwards and downwards on menu
 * Karl Schmidt, March 9 2007	 	 | Changed textures to png
 * Karl Schmidt, March 22 2007       | Correcting include orders and paths
 * Andrew Osborne, March 23 2007     | Added "ClearButtons" functionality
 * Andrew Osborne, March 24 2007 | Added Cancel event support
 * Andrew Osborne, March 24 2007 | Added ability to specifiy whether UIMenu is visible when it's disabled (mVisibleWhenDisabled)
 * Andrew osborne, March 24 2007 | Added SetBackground, SetSpacing, and SetCursorFunc.
 * Karl Schmidt, March 25 2007       | Added correct variable initialization (mParentLayout and mCancelEvent weren't being set to NULL on
 									   construction, as well as support for blank rows, and skipping over them, etc
 * Andrew Osborne, March 25 2007 | Fixed small crash bug, so program doesn't crash when you press enter on an empty menu.
 */

#include "UIMenu.h"                                // class implemented

#include <util.h>

#include <Point.h>
#include <UI/UILayout.h>
#include <UI/UIImage.h>
#include <UI/UIButton.h>
#include <UI/FuncObj.h>
#include <ResourceManager/ResourceManager.h>
#include <Renderer/SDLRenderer.h>

/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================


// The code in the constructor is temporary, it was used for testing
// It should be commented out or deleted once proper sub-classes are defined

UIMenu::UIMenu()
: mCursor( NULL ),
  mCursorFunc( NULL ),
  mParentLayout( NULL ),
  mCancelEvent( NULL ),
  mVisibleWhenDisabled( true )
{

    // Formating Button offset parameters in preperation for adding buttons later
    SDL_Surface *sample = NULL;
    sample = ResourceManager::GetInstance()->LoadTexture("menu_item.png");

    if( sample )
    {
    	// Setting location parameters
	    mButtonStart.Set(15, 15);
	    mButtonOffset.Set(0, (sample->h+8) );
	    mCursorOffset.Set(-2,-2);
    }

    // Set cursor parameters
    mCursorPos = 0;
    mMaxCursorPos = 0;

    // Create cursor
    mCursor = new UIImage("menu_select.png");

    // Set backgound
    mElementImage = ResourceManager::GetInstance()->LoadTexture("menu_back.png");

    SetPos(mPos);

}// UIMenu

UIMenu::~UIMenu()
{
    for ( UIButtonPtrItr iter = mButtons.begin(); iter!=mButtons.end(); ++iter )
    {
        if( *iter != NULL )
        {
            delete (*iter);
        }
    }

    // It is assumed button is always passed "new" in constructor
    for ( FuncObjPtrItr iter = mButtonFuncs.begin(); iter != mButtonFuncs.end(); ++iter )
    {
        if( *iter != NULL )
        {
            delete (*iter);
        }
    }
    // Need to add function Objects... when I add them

    delete mCursor;

}// ~UIMenu


//============================= OPERATORS ====================================
//============================= OPERATIONS ===================================

void UIMenu::RenderSelf(SDL_Surface* destination)
{
    if (mVisible)
    {
        // The menu must be rendered first
        if( mElementImage )
        {
            SDLRenderer::GetInstance()->DrawImageAt(mElementImage, mPos.GetX(), mPos.GetY(), mElementImage->w, mElementImage->h, destination);
        }

        // Cursor is rendered second
        mCursor->RenderSelf(destination);

        // Buttons are rendered second
        UIButtonPtrItr iter;

        for ( iter = mButtons.begin(); iter!=mButtons.end(); ++iter )
        {
            if( *iter != NULL )
            {
                (*iter)->RenderSelf(destination);
            }
        }
    }

}

void UIMenu::ProcessEvent( const InputManager::INPUTKEYS evt )
{
    // Come back to this later
    bool moved = false;

    switch(evt)
    {
        case InputManager::UP:
            // Move cursor up
            if (mCursorPos > 0)
            {
                --mCursorPos;
                if( mButtons[mCursorPos] == NULL )
                {
                    --mCursorPos;
                }
            }
            else if( mCursorPos <= 0 )
            {
                mCursorPos = mMaxCursorPos;
            }
            moved = true;
            //cursor->moveUp()
            break;
        case InputManager::DOWN:
            if( mCursorPos < mMaxCursorPos )
            {
                ++mCursorPos;
                if( mButtons[mCursorPos] == NULL )
                {
                    ++mCursorPos;
                }
            }
            else if( mCursorPos >= mMaxCursorPos )
            {
                mCursorPos = 0;
            }
            moved = true;
            break;
        case InputManager::CONFIRM:
            if (mButtonFuncs.size()>0)
            {
                if ( (mButtonFuncs[mCursorPos]) && (!mButtons[mCursorPos]->GetGhost()) )
                {
                    FuncObj *temp = mButtonFuncs[mCursorPos];
                    (*temp)();
                }
            }
            break;
        case InputManager::CANCEL:
            if ( (mParentLayout) && (mCancelEvent) )
            {
                mParentLayout->SetEventHandler(mCancelEvent);
            }
        default:
            break;

    }

    if (moved)
    {
        if (mCursorFunc)
            (*mCursorFunc)();
        mCursor->SetPos( mPos + mButtonStart + mCursorOffset + mButtonOffset*mCursorPos );
    }
}

//============================= ACCESS     ===================================

void UIMenu::SetPos( const Point & nPos)
{

    mPos = nPos;

    // Move cursor
    mCursor->SetPos( mPos + mButtonStart + mCursorOffset );

    // Move buttons
    UIButtonPtrItr iter;
    int i = 0;
    for ( iter = mButtons.begin(); iter!=mButtons.end(); ++iter )
    {
        if( *iter != NULL )
        {
            (*iter)->SetPos( mPos + mButtonStart + (mButtonOffset * i) );
        }
        i++;
    }

}


void UIMenu::AddButton( const std::string & nName, FuncObj* operation)
{
    UIButton *temp = new UIButton(nName);
    mButtons.push_back(temp);
    mButtonFuncs.push_back(operation);
    mMaxCursorPos = mButtons.size() - 1;
    SetPos( mPos );
}


void UIMenu::ClearButtons(void)
{

    // Erase button images
    for ( UIButtonPtrItr iter = mButtons.begin(); iter!=mButtons.end(); ++iter )
    {
        delete (*iter);
    }

    // Erase/delete function pointers
    for ( FuncObjPtrItr iter2 = mButtonFuncs.begin(); iter2!=mButtonFuncs.end(); ++iter2 )
    {
        delete (*iter2);
    }

    mButtons.clear();
    mButtonFuncs.clear();

    // Set cursor parameters
    mCursorPos = 0;
    mMaxCursorPos = 0;

}

void UIMenu::Enable(void)
{
    mCursor->SetVisible(true);
    this->SetVisible(true);
}

void UIMenu::Disable(void)
{
    mCursor->SetVisible(false);
    this->SetVisible( mVisibleWhenDisabled );
}

void UIMenu::SetGhost(int n, bool b)
{
    if (n<=mMaxCursorPos)
        mButtons[n]->SetGhost(b);

}

void UIMenu::SetSpacing(int newSpacing)
{
    SDL_Surface *sample = NULL;
    sample = ResourceManager::GetInstance()->LoadTexture("menu_item.png");

    if( sample )
    {
    	// Setting location parameters
	    mButtonOffset.Set(0, (sample->h+newSpacing) );

    }
    else
    {
        mButtonOffset.Set(0,newSpacing);
    }
    SetPos(mPos);
}

void UIMenu::SetBackground(const std::string & nName)
{
    mElementImage = ResourceManager::GetInstance()->LoadTexture(nName);
}

void UIMenu::SetCursorFunc(FuncObj* newCursorFunc)
{
    mCursorFunc = newCursorFunc;
}

void UIMenu::AddBlankRow()
{
    mButtons.push_back( NULL );
    mButtonFuncs.push_back( NULL );
    mMaxCursorPos = mButtons.size() - 1;
    SetPos( mPos );
}

//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ////////////////////////////////////
