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
 */

#include <UIElement.h>                   // class implemented


/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

UIElement::UIElement(void)
: elementImage( NULL )
{
    // Overridden initialization
    //rend = SDLRenderer::GetInstance();  // This needs to be overridden to allow for modularization
    //RSM = ResourceManager::GetInstance();


/*    pos.SetX(100);

    // This should REALLY be overridden
    elementImage = RSM->LoadTexture("nicePic.bmp");

    // NOw THIIIIIS is extrememly temperary
    rend->AddToRenderQueue(this);*/

}

UIElement::UIElement( const string filename)
: elementImage( NULL )
{
    elementImage = ResourceManager::GetInstance()->LoadTexture(filename);
}


UIElement::~UIElement(void)
{
}



//============================= OPERATORS ====================================
//============================= OPERATIONS ===================================


void UIElement::RenderSelf(SDL_Surface* destination)
{
    if( elementImage )
    {
        SDLRenderer::GetInstance()->DrawImageAt(elementImage, pos.GetX(), pos.GetY(), elementImage->w, elementImage->h, destination);
    }
}


//============================= ACCESS     ===================================


void UIElement::setPos(Point nPos)
{
    pos = nPos;
}

void UIElement::setVisible(bool nVisible)
{
    visible = nVisible;
}


//============================= INQUIRY    ===================================

Point UIElement::getPos(void)
{
    return pos;
}


bool UIElement::getVisible(void)
{
    return visible;
}

/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////


