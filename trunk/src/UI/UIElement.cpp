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
 */

#include <UIElement.h>                   // class implemented


/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

UIElement::UIElement(void)
: mVisible( true ), mElementImage( NULL )
{


}

/*UIElement::UIElement( const string filename)
: mElementImage( NULL ), mVisible( true )
{
    mElementImage = ResourceManager::GetInstance()->LoadTexture(filename);
}*/


UIElement::~UIElement(void)
{
}



//============================= OPERATORS ====================================
//============================= OPERATIONS ===================================


void UIElement::RenderSelf(SDL_Surface* destination)
{
    if ( ( mElementImage ) && ( mVisible ) )
    //if ( mElementImage )
    {
        SDLRenderer::GetInstance()->DrawImageAt(mElementImage, mPos.GetX(), mPos.GetY(), mElementImage->w, mElementImage->h, destination);
    }
}


//============================= ACCESS     ===================================


void UIElement::setPos(Point nPos)
{
    mPos = nPos;
}

void UIElement::setVisible(bool nVisible)
{
    mVisible = nVisible;
}


//============================= INQUIRY    ===================================

Point UIElement::getPos(void)
{
    return mPos;
}


bool UIElement::getVisible(void)
{
    return mVisible;
}

/////////////////////////////// PROTECTED  ///////////////////////////////////

//============================= INQUIRY    ===================================

SDL_Surface* UIElement::getElement(void)
{
    return mElementImage;
}


/////////////////////////////// PRIVATE    ///////////////////////////////////


