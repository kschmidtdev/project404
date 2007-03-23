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
 */

#include "UIMenu.h"                                // class implemented

#include <util.h>

#include <Point.h>
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
: mCursor( NULL )
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
        delete (*iter);
    }

    // It is assumed button is always passed "new" in constructor
    for ( FuncObjPtrItr iter2 = mButtonFuncs.begin(); iter2!=mButtonFuncs.end(); ++iter2 )
    {
        delete (*iter2);
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
            (*iter)->RenderSelf(destination);
        }
    }

}

void UIMenu::ProcessEvent( const InputManager::INPUTKEYS evt )
{
    // Come back to this later
    switch(evt)
    {
        case InputManager::UP:
            // Move cursor up
            if (mCursorPos > 0)
            {
                mCursorPos--;
            }
            else if( mCursorPos == 0 )
            {
                mCursorPos = mMaxCursorPos;
            }
            mCursor->SetPos( mPos + mButtonStart + mCursorOffset + mButtonOffset*mCursorPos );
            //cursor->moveUp()
            break;
        case InputManager::DOWN:
            if( mCursorPos < mMaxCursorPos )
            {
                mCursorPos++;
            }
            else if( mCursorPos == mMaxCursorPos )
            {
                mCursorPos = 0;
            }
            mCursor->SetPos( mPos + mButtonStart + mCursorOffset + mButtonOffset*mCursorPos );
            break;
        case InputManager::CONFIRM:
            if ( (mButtonFuncs[mCursorPos]) && (!mButtons[mCursorPos]->GetGhost()) )
            {
                FuncObj *temp = mButtonFuncs[mCursorPos];
                (*temp)();
            }
            break;
        default:
            break;

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
        (*iter)->SetPos( mPos + mButtonStart + (mButtonOffset * i) );
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


void UIMenu::SetGhost(int n, bool b)
{
    if (n<=mMaxCursorPos)
        mButtons[n]->SetGhost(b);

}

//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ////////////////////////////////////
