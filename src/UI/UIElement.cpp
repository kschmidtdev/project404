/**
 * File: UIElement.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, February 7, 2007 | Initial creation
 * Andrew Osborne, February 10, 2007 | Got it to work
 * Andrew Osborne, February 10, 2007 | Added documentation, removed RSM/rend references
 * Karl Schmidt, February 11 2007 | Added checks that prevent game from crashing if textures are missing
 * Andrew Osborne, February 11 2007 | Added destructor
 * Karl Schmidt, February 13 2007 | Rearranged initializer list to prevent warning
 * Karl Schmidt, February 14 2007 | Updated function capitalization, block style, typedefs, refs
 */

#include <util.h>


#include <UIElement.h>                   // class implemented


/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

UIElement::UIElement(void)
: mVisible( true ), mElementImage( NULL )
{


}


UIElement::~UIElement(void)
{
}



//============================= OPERATORS ====================================
//============================= OPERATIONS ===================================


void UIElement::RenderSelf(SDL_Surface* destination)
{
    if ( ( mElementImage ) && ( mVisible ) )
    {
        SDLRenderer::GetInstance()->DrawImageAt(mElementImage, mPos.GetX(), mPos.GetY(), mElementImage->w, mElementImage->h, destination);
    }
}


//============================= ACCESS     ===================================


void UIElement::SetPos( const Point & nPos )
{
    mPos = nPos;
}

void UIElement::SetVisible( const bool nVisible )
{
    mVisible = nVisible;
}


//============================= INQUIRY    ===================================

Point UIElement::GetPos(void)
{
    return mPos;
}


bool UIElement::GetVisible(void) const
{
    return mVisible;
}

/////////////////////////////// PROTECTED  ///////////////////////////////////

//============================= INQUIRY    ===================================

SDL_Surface* UIElement::GetElement(void)
{
    return mElementImage;
}


/////////////////////////////// PRIVATE    ///////////////////////////////////


