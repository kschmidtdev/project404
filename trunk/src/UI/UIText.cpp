/**
 * File: UIText.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, February 14 2007 | Initial Creation
 * Andrew Osborne, March 9 2007 | Added new ChangeText command that allows you to change all parameters
 * Karl Schmidt, March 20 2007   | Major adding of consts and reference usage, rearranging includes
 * Karl Schmidt, March 21 2007 | Re-arranged class to eliminate code duplication as much as possible,
 								 added support for black background text
 * Andrew Osborne, March 21 2007 | Added 'CenterText' as method, corrected bug.
 * Karl Schmidt, March 22 2007      | Correcting include orders and paths
 */

#include "UIText.h"                                // class implemented

#include <util.h>

#include <SDL/SDL.h>
#include <Renderer/SDLRenderer.h>

/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

UIText::UIText()
: UIElement()
{
    ChangeText( "Nothing Specified", 12, 0, 0, 0, false );
}// UIText

UIText::UIText( const string & text, const int size, const int r, const int g, const int b, const bool backBlack )
: UIElement(),
  mRed( r ),
  mGreen( g ),
  mBlue( b ),
  mSize( size ),
  mText( text ),
  mBackBlack( backBlack )
{
    MakeText();
}

UIText::UIText( const string & text)
: UIElement()
{
    ChangeText( text, 12, 0, 0, 0, false );
}

UIText::~UIText()
{
    DestroyText();
}// ~UIText




//============================= OPERATORS ====================================


//============================= OPERATIONS ===================================

void UIText::CenterText(UIElement* centerElement)
{

    // Find Text width
    //SDL_Surface *textSurface = mMessage->GetElement();

    int textWidth, textHeight;
    if( mElementImage )
    {
        textWidth = mElementImage->w;
        textHeight = mElementImage->h;
    }
    else
    {
        textWidth = textHeight = 0;
    }

    // Find Image Width
    int imageWidth, imageHeight;
    SDL_Surface* centerSurface = centerElement->GetElement();
    if (centerSurface)
    {
        imageWidth = centerSurface->w;
        imageHeight = centerSurface->h;
    }
    else
    {
        imageWidth = imageHeight = 0;
    }

    // Find Offset Point
    Point offset;
    offset.Set( (int) (imageWidth - textWidth) / 2, (int) (imageHeight - textHeight) / 2);

    // Move to position
    SetPos( centerElement->GetPos() + offset );

}


//============================= ACCESS     ===================================

void UIText::ChangeText(const string & newText)
{
    mText = newText;
    DestroyText();
    MakeText();
}

void UIText::ChangeText(const string & newText, const int s, const int r, const int g, const int b, const bool backBlack )
{
    mText = newText;
    mSize = s;
    mRed = r;
    mGreen = g;
    mBlue = b;
    mBackBlack = backBlack;

    DestroyText();
    MakeText();
}


void UIText::SetColour(const int r, const int g, const int b)
{
    mRed = r;
    mGreen = g;
    mBlue = b;

    DestroyText();
    MakeText();
}

void UIText::SetSize(const int s)
{
    mSize = s;
    DestroyText();
    MakeText();
}


//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

void UIText::MakeText()
{
    mElementImage = SDLRenderer::GetInstance()->CreateTextSurface( mText, mSize, mRed, mGreen, mBlue, mBackBlack );
}

void UIText::DestroyText()
{
    if( mElementImage )
    {
        SDL_FreeSurface( mElementImage );
    }
    mElementImage = NULL;
}

/////////////////////////////// PRIVATE    ///////////////////////////////////
