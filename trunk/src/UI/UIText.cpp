/**
 * File: UIText.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, February 14 2007 | Initial Creation
 * Andrew Osborne, March 9 2007 | Added new ChangeText command that allows you to change all parameters
 * Karl Schmidt, March 20 2007   | Major adding of consts and reference usage, rearranging includes
 */


#include <util.h>


#include "UIText.h"                                // class implemented


/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

UIText::UIText()
: UIElement()
{
    mRed = 0;
    mGreen = 0;
    mBlue = 0;
    mText = "Nothing Specified";
    mSize = 12;
}// UIText

UIText::UIText( const string & text, const int size, const int r, const int g, const int b)
: UIElement()
{
    mRed = r;
    mGreen = g;
    mBlue = b;
    mText = text;
    mSize = size;
    mElementImage = SDLRenderer::GetInstance()->CreateTextSurface(mText, mSize, mRed, mGreen, mBlue);
}

UIText::UIText( const string & text)
: UIElement()
{
    mRed = 0;
    mGreen = 0;
    mBlue = 0;
    mText = text;
    mSize = 12;
    mElementImage = SDLRenderer::GetInstance()->CreateTextSurface(mText, mSize, mRed, mGreen, mBlue);
}

UIText::~UIText()
{
    if( mElementImage )
    {
        SDL_FreeSurface( mElementImage );
    }
    mElementImage = NULL;
}// ~UIText




//============================= OPERATORS ====================================


//============================= OPERATIONS ===================================

void UIText::CenterText(UIElement* e)
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
    SDL_Surface* s = e->GetElement();
    if (s)
    {
        imageWidth = s->w;
        imageHeight = s->h;
    }
    else
    {
        imageWidth = imageHeight = 0;
    }

    // Find Offset Point
    Point offset;
    offset.Set( (int) (imageWidth - textWidth) / 2, (int) (imageHeight - textHeight) / 2);

    // Move to position
    SetPos( e->GetPos() + offset );

}


//============================= ACCESS     ===================================

void UIText::ChangeText(const string & newText)
{
    mText = newText;
    if( mElementImage )
    {
        SDL_FreeSurface( mElementImage );
    }
    mElementImage = SDLRenderer::GetInstance()->CreateTextSurface(mText, mSize, mRed, mGreen, mBlue);
}

void UIText::ChangeText(const string & newText, const int s, const int r, const int g, const int b)
{
    mText = newText;
    mSize = s;
    mRed = r;
    mGreen = g;
    mBlue = b;
    if( mElementImage )
    {
        SDL_FreeSurface( mElementImage );
    }
    mElementImage = SDLRenderer::GetInstance()->CreateTextSurface(mText, mSize, mRed, mGreen, mBlue);
}


void UIText::SetColour(const int r, const int g, const int b)
{
    mRed = r;
    mGreen = g;
    mBlue = b;
    if( mElementImage )
    {
        SDL_FreeSurface( mElementImage );
    }
    mElementImage = SDLRenderer::GetInstance()->CreateTextSurface(mText, mSize, mRed, mGreen, mBlue);
}

void UIText::SetSize(const int s)
{
    mSize = s;
    if( mElementImage )
    {
        SDL_FreeSurface( mElementImage );
    }
    mElementImage = SDLRenderer::GetInstance()->CreateTextSurface(mText, mSize, mRed, mGreen, mBlue);
}


//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
