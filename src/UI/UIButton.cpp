/**
 * File: UIButton.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, February 11 2007 | Initial Creation
 */
#include "UIButton.h"                                // class implemented


/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

UIButton::UIButton()
{
    mElementImage = ResourceManager::GetInstance()->LoadTexture("testButton.bmp");
}// UIButton

UIButton::UIButton(const string text)
{
    mText.ChangeText(text);
    mElementImage = ResourceManager::GetInstance()->LoadTexture("testButton.bmp");
}

UIButton::~UIButton()
{
}// ~UIButton


//============================= OPERATORS ====================================


//============================= OPERATIONS ===================================

void UIButton::RenderSelf(SDL_Surface* destination)
{
    if ( ( mElementImage ) && ( mVisible ) )
    //if ( mElementImage )
    {
        SDLRenderer::GetInstance()->DrawImageAt(mElementImage, mPos.GetX(), mPos.GetY(), mElementImage->w, mElementImage->h, destination);
        mText.RenderSelf(destination);
    }

}

//============================= ACCESS     ===================================

void UIButton::setPos(Point nPos)
{
    mPos = nPos;
    int textWidth, textHeight;
    int buttonWidth, buttonHeight;
    SDL_Surface *textSurface = mText.getElement();
    textWidth = textSurface->w;
    textHeight = textSurface->h;
    buttonWidth = mElementImage->w;
    buttonHeight = mElementImage->h;
    int xOffset, yOffset;

    xOffset = (int) (buttonWidth - textWidth) / 2;
    yOffset = (int) (buttonHeight - textHeight) / 2;
    Point nPos2( xOffset, yOffset);
    nPos2 = nPos2 + nPos;
    mText.setPos(nPos2);

}

void UIButton::setOperation(FuncObj* nOperation)
{
    mOperation = nOperation;
}



//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
