/**
 * File: UITile.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, February 11 2007 | Initial Creation
 */
#include "UITile.h"                                // class implemented


/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

UITile::UITile()
: UIElement(), mCharacterImage( NULL )
{
    mElementImage = ResourceManager::GetInstance()->LoadTexture("defaultTile.bmp");
    //mVisible = true;
}// UITile


UITile::~UITile()
{
}// ~UITile


//============================= OPERATORS ====================================


//============================= OPERATIONS ===================================

void UITile::addCharacter(SDL_Surface *nSur)
{
    mCharacterImage = nSur;
}

void UITile::removeCharacter(void)
{
    mCharacterImage = NULL;
}



void UITile::RenderSelf(SDL_Surface* destination)
{
    if (mVisible==true)
    {
        if (mCharacterImage!=NULL) {
            SDLRenderer::GetInstance()->DrawImageAt(mCharacterImage, mPos.GetX(), mPos.GetY(), mCharacterImage->w, mCharacterImage->h, destination);
        } else if (mElementImage!=NULL) {
            SDLRenderer::GetInstance()->DrawImageAt(mElementImage, mPos.GetX(), mPos.GetY(), mElementImage->w, mElementImage->h, destination);
        } // ELSE do nothing
    }
}

//============================= ACCESS     ===================================
//============================= INQUIRY    ===================================

bool UITile::hasCharacter(void)
{
    if (mCharacterImage==NULL) {
        return false;
    } else {
        return true;
    }
}
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
