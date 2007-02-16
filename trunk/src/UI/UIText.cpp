/**
 * File: UIText.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Name, Date | Work Done
 */
#include "UIText.h"                                // class implemented


/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

UIText::UIText()
{
    mRed = 0;
    mGreen = 0;
    mBlue = 0;
    mText = "Nothing Specified";
    mSize = 12;
}// UIText

UIText::UIText( const string text, int size, int r, int g, int b)
{
    UIElement::UIElement();
    mRed = r;
    mGreen = g;
    mBlue = b;
    mText = text;
    mSize = size;
    mElementImage = SDLRenderer::GetInstance()->CreateTextSurface(mText, mSize, mRed, mGreen, mBlue);
}

UIText::UIText( const string text)
{
    UIElement::UIElement();
    mRed = 0;
    mGreen = 0;
    mBlue = 0;
    mText = text;
    mSize = 12;
    mElementImage = SDLRenderer::GetInstance()->CreateTextSurface(mText, mSize, mRed, mGreen, mBlue);
}


void UIText::ChangeText(const string newText) {
    mText = newText;
    delete mElementImage;
    mElementImage = SDLRenderer::GetInstance()->CreateTextSurface(mText, mSize, mRed, mGreen, mBlue);
}


void UIText::SetColour(int r, int g, int b)
{
    mRed = r;
    mGreen = g;
    mBlue = b;
    delete mElementImage;
    mElementImage = SDLRenderer::GetInstance()->CreateTextSurface(mText, mSize, mRed, mGreen, mBlue);
}


UIText::~UIText()
{
    delete mElementImage;
}// ~UIText


//============================= OPERATORS ====================================


//============================= OPERATIONS ===================================
//============================= ACCESS     ===================================


//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
