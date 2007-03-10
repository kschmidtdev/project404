/**
 * File: UITile.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, February 11 2007 | Initial Creation
 * Karl Schmidt,   February 14 2007 | Updated function capitalization, block style, typedefs, refs
 * Mike Malyuk,     March 8 2007    | Added UITile constructor taking Tile in preparation for use of map
 * Karl Schmidt, March 9 2007	 	| Changed textures to png, fixed some style issues, changed so characters
 									  are rendered on top of tile if there is one at that tile, took out
 									  magic offset numbers
 */


#include <util.h>


#include "UITile.h"                                // class implemented


/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

UITile::UITile()
: UIElement(), mCharacterImage( NULL )
{
    mElementImage = ResourceManager::GetInstance()->LoadTexture("defaultTile.png");
}// UITile

UITile::UITile(Tile t)
: UIElement(), mCharacterImage( NULL )
{
    mElementImage = ResourceManager::GetInstance()->LoadTexture(t.GetPic());
    int mTotalOffset = mElementImage->w;
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
    if( mVisible )
    {
        if( mElementImage )
        {
            SDLRenderer::GetInstance()->DrawImageAt(mElementImage, mPos.GetX(), mPos.GetY(), mElementImage->w, mElementImage->h, destination);
        }

        // If we have a character, render it on top of the tile
        if( mCharacterImage != NULL )
        {
            SDLRenderer::GetInstance()->DrawImageAt(mCharacterImage, mPos.GetX(), mPos.GetY(), mCharacterImage->w, mCharacterImage->h, destination);
        }
    }
}

//============================= ACCESS     ===================================
//============================= INQUIRY    ===================================

bool UITile::HasCharacter(void)
{
    if( mCharacterImage == NULL )
    {
        return false;
    }
    else
    {
        return true;
    }
}
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
