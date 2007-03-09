/**
 * File: UITile.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, February 11 2007 | Initial Creation
 * Karl Schmidt,   February 14 2007 | Updated function capitalization, block style, typedefs, refs
 * Mike Malyuk,     March 8 2007    | Added UITile constructor taking Tile in preparation for use of map
 */


#include <util.h>


#include "UITile.h"                                // class implemented


/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

UITile::UITile()
: UIElement(), mCharacterImage( NULL )
{
    mElementImage = ResourceManager::GetInstance()->LoadTexture("defaultTile.bmp");
    //mVisible = true;
}// UITile

UITile::UITile(Tile t)
: UIElement(), mCharacterImage( NULL )
{
    mElementImage = ResourceManager::GetInstance()->LoadTexture(t.GetPic());
    int mTotalOffset = 2 + mElementImage->w;
    mPos = Point (10 + t.GetPoint().GetX()*mTotalOffset, 10 + t.GetPoint().GetY()*mTotalOffset);
}

UITile::~UITile()
{
}// ~UITile


//============================= OPERATORS ====================================


//============================= OPERATIONS ===================================

void UITile::AddCharacter(SDL_Surface *nSur)
{
    mCharacterImage = nSur;
}

void UITile::RemoveCharacter(void)
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

bool UITile::HasCharacter(void)
{
    if (mCharacterImage==NULL) {
        return false;
    } else {
        return true;
    }
}
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
