/**
 * File: UIMenu.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, February 10, 2007 | Initial creation and testing
 * Andrew Osborne, February 10, 2007 | Added some comments, deleted inputFunction
 * Andrew Osborne, February 11, 2007 | added 'm' to members, added input funcitonality, used Point addition/mult
 * Karl Schmidt, February 11 2007 | Added checks to prevent crashes when textures are not loaded
 * Andrew Osborne, February 11, 2007 | added destructor
 * Karl Schmidt, February 14 2007 | Updated function capitalization, block style, typedefs, refs
 * Andrew Osborne, February 14, 2007 | added AddButton method
 */
#include "UIMenu.h"                                // class implemented
#include "Point.h"
#include "UIImage.h"
#include "UIButton.h"
#include "FuncObj.h"

/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================


// The code in the constructor is temporary, it was used for testing
// It should be commented out or deleted once proper sub-classes are defined

UIMenu::UIMenu()
: mCursor( NULL )
{

    // Formating Button offset parameters in preperation for adding buttons later
    SDL_Surface *sample = NULL;
    sample = ResourceManager::GetInstance()->LoadTexture("testButton.bmp");

    if( sample )
    {
    	// Setting location parameters
	    mButtonStart.Set(15, 15);
	    mButtonOffset.Set(0, (sample->h+10) );
	    mCursorOffset.Set(-5,-5);
    }


    // Set cursor parameters
    mCursorPos = 0;
    mMaxCursorPos = 0;

    // Create cursor
    mCursor = new UIImage("cursor.bmp");

    // Set backgound
    mElementImage = ResourceManager::GetInstance()->LoadTexture("testMenu.bmp");

    //SetPos( Point(0,0) );

}// UIMenu

UIMenu::~UIMenu()
{
    for ( UIElementPtrItr iter = mButtons.begin(); iter!=mButtons.end(); ++iter )
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
        UIElementPtrItr iter;
        //int size = buttons.size();

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
            if (mCursorPos>0)
            {
                mCursorPos--;
                mCursor->SetPos( mPos + mButtonStart + mCursorOffset + mButtonOffset*mCursorPos );
            }
            //cursor->moveUp()
            break;
        case InputManager::DOWN:
            if (mCursorPos<mMaxCursorPos)
            {
                mCursorPos++;
                mCursor->SetPos( mPos + mButtonStart + mCursorOffset + mButtonOffset*mCursorPos );
            }
            break;
        case InputManager::CONFIRM:
            if (mButtonFuncs[mCursorPos])
            {
                FuncObj *temp = mButtonFuncs[mCursorPos];
                (*temp)();
                //mButtonFuncs[mCursorPos]->();
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
    UIElementPtrItr iter;
    int i = 0;
    for ( iter = mButtons.begin(); iter!=mButtons.end(); ++iter )
    {
        (*iter)->SetPos( mPos + mButtonStart + (mButtonOffset * i) );
        i++;
    }


}


void UIMenu::AddButton( const string nName, FuncObj* operation)
{
    UIButton *temp = new UIButton(nName);
    mButtons.push_back(temp);
    mButtonFuncs.push_back(operation);
    mMaxCursorPos = mButtons.size() - 1;
    SetPos( mPos );
}

//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ////////////////////////////////////
