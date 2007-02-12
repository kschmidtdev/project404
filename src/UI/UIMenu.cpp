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
 */
#include "UIMenu.h"                                // class implemented
#include "Point.h"

/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================


// The code in the constructor is temporary, it was used for testing
// It should be commented out or deleted once proper sub-classes are defined

UIMenu::UIMenu()
: mCursor( NULL )
{
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
    mMaxCursorPos = 2;

    // Create cursor
    mCursor = new UIElement("cursor.bmp");

    // Create button
    UIElement *tempButton;
    for (int i=0; i<3; i++)
    {
        tempButton = new UIElement("testButton.bmp");
        mButtons.push_back( tempButton );
    }

    // Set backgound
    elementImage = ResourceManager::GetInstance()->LoadTexture("testMenu.bmp");

    setPos( Point(0,0) );

}// UIMenu

UIMenu::~UIMenu()
{
}// ~UIMenu


//============================= OPERATORS ====================================
//============================= OPERATIONS ===================================

void UIMenu::RenderSelf(SDL_Surface* destination)
{
    // The menu must be rendered first
    if( elementImage )
    {
        SDLRenderer::GetInstance()->DrawImageAt(elementImage, pos.GetX(), pos.GetY(), elementImage->w, elementImage->h, destination);
    }

    // Cursor is rendered second
    mCursor->RenderSelf(destination);

    // Buttons are rendered second
    std::vector<UIElement*>::iterator iter;
    //int size = buttons.size();

    for (iter = mButtons.begin();
            iter!=mButtons.end(); iter++)
    {
        (*iter)->RenderSelf(destination);
    }

}

void UIMenu::ProcessEvent( const InputManager::INPUTKEYS evt )
{
    // Come back to this later
    switch(evt) {
        case InputManager::UP:
            // Move cursor up
            if (mCursorPos>0) {
                mCursorPos--;
                mCursor->setPos( pos + mButtonStart + mCursorOffset + mButtonOffset*mCursorPos );
            }
            //cursor->moveUp()
            break;
        case InputManager::DOWN:
            if (mCursorPos<mMaxCursorPos) {
                mCursorPos++;
                mCursor->setPos( pos + mButtonStart + mCursorOffset + mButtonOffset*mCursorPos );
            }
            break;
        default:
            break;

    }



}




//============================= ACCESS     ===================================

void UIMenu::setPos(Point nPos)
{
    pos = nPos;

    // Move cursor
    mCursor->setPos( pos + mButtonStart + mCursorOffset );

    // Move buttons
    std::vector<UIElement*>::iterator iter;
    int i = 0;
    for (iter = mButtons.begin();
            iter!=mButtons.end(); iter++)
    {
        (*iter)->setPos( pos + mButtonStart + (mButtonOffset * i) );
        i++;
    }


}


//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ////////////////////////////////////
