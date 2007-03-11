/**
 * File: UIText.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, February 14 2007 | Initial Creation
 * Andrew Osborne, March 9 2007 | Added new ChangeText command that allows you to change all parameters
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

UIText::UIText( const string text, int size, int r, int g, int b)
: UIElement()
{
    mRed = r;
    mGreen = g;
    mBlue = b;
    mText = text;
    mSize = size;
    mElementImage = SDLRenderer::GetInstance()->CreateTextSurface(mText, mSize, mRed, mGreen, mBlue);
}

UIText::UIText( const string text)
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
//============================= ACCESS     ===================================

void UIText::ChangeText(const string newText)
{
    mText = newText;
    if( mElementImage )
    {
        SDL_FreeSurface( mElementImage );
    }
    mElementImage = SDLRenderer::GetInstance()->CreateTextSurface(mText, mSize, mRed, mGreen, mBlue);
}

void UIText::ChangeText(const string newText, int s, int r, int g, int b)
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


void UIText::SetColour(int r, int g, int b)
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

void UIText::SetColour(int s)
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
