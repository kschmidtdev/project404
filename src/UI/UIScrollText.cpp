/**
 * File: UIScrollText.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, March 12 2007 | Initial Creation
 * Karl Schmidt, March 15 2007   | Added ClearText implementation
 */
#include "UIScrollText.h"                                // class implemented


/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

UIScrollText::UIScrollText()
: mMaxLength( 0 ), mMaxLines( 4 ), mColourRed( 0 ), mColourGreen( 0 ), mColourBlue( 0 ),
mFontSize( 18 ), mLineSpacing( 7 ), mCurStartIndex( 0 )
{

    mElementImage = ResourceManager::GetInstance()->LoadTexture("scrollBox.png");

    mStartPoint.Set(10,12);
    mLineOffest.Set(0, mFontSize + mLineSpacing);

    mUILines.clear();
    mStringLines.clear();

    UIText *tempText;
    for (int i=0; i<mMaxLines; i++)
    {
        tempText = new UIText(" ", mFontSize, mColourRed, mColourGreen, mColourBlue);
        mUILines.push_back( tempText );
    }

    SetPos(mPos);

}// UIScrollText



UIScrollText::~UIScrollText()
{
    for (UITextItr iter = mUILines.begin(); iter!=mUILines.end(); ++iter)
    {
        delete (*iter);
        (*iter) = NULL;
    }
    mUILines.clear();

}// ~UIScrollText


//============================= OPERATORS ====================================



//============================= OPERATIONS ===================================

void UIScrollText::RenderSelf(SDL_Surface *destination)
{

    UIElement::RenderSelf(destination);

    if (mVisible)
    {
        for (int i=0; i<mMaxLines; i++)
            mUILines[i]->RenderSelf(destination);
    }


}

bool UIScrollText::NextPage()
{

    int size = mStringLines.size();

    if (size>(mCurStartIndex + mMaxLines))
    {
        // is possible to advance

        mCurStartIndex += mMaxLines;
        int curStringIndex = 0;

        for (int i=0; i<mMaxLines; i++)
        {
            curStringIndex = mCurStartIndex + i;
            if (curStringIndex<size)
            {
                mUILines[i]->ChangeText( mStringLines[ curStringIndex ] );
            }
            else
            {
                mUILines[i]->ChangeText(" ");
            }
        }

        return true;
    }
    else
    {
        return false;
    }



}

//============================= ACCESS     ===================================

void UIScrollText::SetPos( const Point & nPos )
{
    UIElement::SetPos(nPos);


    Point curPos = mPos + mStartPoint;

    for (int i=0; i<mMaxLines; i++)
    {
        mUILines[i]->SetPos( curPos );
        curPos = curPos + mLineOffest;
    }


}

void UIScrollText::AddLine(string oneLine)
{
    //string temp
    mStringLines.push_back( oneLine );

    // Initializes first three lines of text (into respective UIText elements)
    int size = mStringLines.size();
    if (size<=mMaxLines)
    {
        size = size - 1;
        mUILines[size]->ChangeText(mStringLines[size]);
    }
}

void UIScrollText::ClearText()
{
    mStringLines.clear();
    mCurStartIndex = 0;
}


//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
