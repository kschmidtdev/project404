/**
 * File: UIButton.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, February 11 2007 | Initial Creation
 * Karl Schmidt, February 14 2007 	| Updated function capitalization, block style, typedefs
 * Karl Schmidt, March 9 2007	 	| Changed textures to png, fixed a warning
 * Andrew Osborne, March 19 2007    | Added Ghosting functionality
 */

#include <util.h>
#include "UIButton.h"                                // class implemented



int UIButton::mActiveRed = 0;
int UIButton::mActiveGreen = 0;
int UIButton::mActiveBlue = 0;
int UIButton::mGhostRed = 128;
int UIButton::mGhostGreen = 128;
int UIButton::mGhostBlue = 128;
int UIButton::mTextSize = 12;


/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

UIButton::UIButton()
: mText(" "), mOperation(NULL), mGhost( false )
{
    mElementImage = ResourceManager::GetInstance()->LoadTexture("menu_item.png");
}// UIButton

UIButton::UIButton(const string text)
: mOperation( NULL ), mGhost( false )
{
    mText.ChangeText(text, mTextSize, mActiveRed, mActiveGreen, mActiveBlue);
    mElementImage = ResourceManager::GetInstance()->LoadTexture("menu_item.png");
}

UIButton::~UIButton()
{
}// ~UIButton


//============================= OPERATORS ====================================


//============================= OPERATIONS ===================================

void UIButton::RenderSelf(SDL_Surface* destination)
{
    if ( ( mElementImage ) && ( mVisible ) )
    {
        SDLRenderer::GetInstance()->DrawImageAt(mElementImage, mPos.GetX(), mPos.GetY(), mElementImage->w, mElementImage->h, destination);
        mText.RenderSelf(destination);
    }

}

//============================= ACCESS     ===================================

void UIButton::SetPos( const Point & nPos )
{
    mPos = nPos;
    int textWidth, textHeight;
    textWidth = textHeight = 0;
    int buttonWidth, buttonHeight;
    SDL_Surface *textSurface = mText.GetElement();
    if( textSurface )
    {
        textWidth = textSurface->w;
        textHeight = textSurface->h;
    }
    buttonWidth = mElementImage->w;
    buttonHeight = mElementImage->h;
    int xOffset, yOffset;

    xOffset = (int) (buttonWidth - textWidth) / 2;
    yOffset = (int) (buttonHeight - textHeight) / 2;
    Point nPos2( xOffset, yOffset);
    nPos2 = nPos2 + nPos;
    mText.SetPos(nPos2);

}

/*void UIButton::SetOperation( FuncObj* nOperation)
{
    mOperation = nOperation;
}*/

void UIButton::SetGhost(bool b)
{
    if (b!=mGhost)
    {
        // Value has changed
        if (b)
        {
            // Ghost = true
            mText.SetColour(mGhostRed, mGhostGreen, mGhostBlue);
            mGhost = true;
        }
        else
        {
            // Ghost = false
            mText.SetColour(mActiveRed, mActiveGreen, mActiveBlue);
            mGhost = false;
        }
    }
}

//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
