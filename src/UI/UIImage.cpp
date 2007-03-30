/**
 * File: UIImage.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, February 11 2007 | Initial Creation
 * Karl Schmidt, March 22 2007      | Correcting include orders and paths
 * Andrew Osborne, March 23 2007    | Added "SetImage" method to dynamically adjust image
 * Karl Schmidt, March 29 2007      | Added correct superclass constructor calling, alpha parameter and getter/setter
 */

#include "UIImage.h"                                // class implemented

#include <util.h>

#include <ResourceManager/ResourceManager.h>
#include <Renderer/SDLRenderer.h>

/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

UIImage::UIImage()
: UIElement(),
  mAlpha( 255 )
{
}// UIImage


UIImage::UIImage( const std::string & filename)
: UIElement(),
  mAlpha( 255 )
{
    mElementImage = ResourceManager::GetInstance()->LoadTexture(filename);
}

UIImage::~UIImage()
{
}// ~UIImage


//============================= OPERATORS ====================================
//============================= OPERATIONS ===================================

void UIImage::RenderSelf(SDL_Surface* destination)
{
    if ( ( mElementImage ) && ( mVisible ) )
    {
        SDLRenderer::GetInstance()->DrawImageAt(mElementImage, mPos.GetX(), mPos.GetY(), mElementImage->w, mElementImage->h, destination, mAlpha );
    }
}

//============================= ACCESS     ===================================

void UIImage::SetImage(const std::string & filename)
{
    mElementImage = ResourceManager::GetInstance()->LoadTexture(filename);
}

void UIImage::SetAlpha( const unsigned int alpha )
{
    mAlpha = alpha;
}

//============================= INQUIRY    ===================================

const unsigned int UIImage::GetAlpha() const
{
    return mAlpha;
}

/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
