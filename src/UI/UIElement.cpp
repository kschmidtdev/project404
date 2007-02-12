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
 */

#include <UIElement.h>                   // class implemented


/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

UIElement::UIElement(void)
: mElementImage( NULL )
{
    // Overridden initialization
    //rend = SDLRenderer::GetInstance();  // This needs to be overridden to allow for modularization
    //RSM = ResourceManager::GetInstance();


/*    mPos.SetX(100);

    // This should REALLY be overridden
    mElementImage = RSM->LoadTexture("nicePic.bmp");

    // NOw THIIIIIS is extrememly temperary
    rend->AddToRenderQueue(this);*/

}

UIElement::UIElement( const string filename)
: mElementImage( NULL )
{
    mElementImage = ResourceManager::GetInstance()->LoadTexture(filename);
}


UIElement::~UIElement(void)
{
}



//============================= OPERATORS ====================================
//============================= OPERATIONS ===================================


void UIElement::RenderSelf(SDL_Surface* destination)
{
    if( mElementImage )
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

/////////////////////////////// PRIVATE    ///////////////////////////////////


