/**
 * File: UIUnitTestHelp.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, March 13 2007 | Initial creation, Fleshed out methods
 */
#include "UIUnitTestHelp.h"                                // class implemented
#include "util.h"

/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

UIUnitTestHelp::UIUnitTestHelp()
{
}// UIUnitTestHelp

UIUnitTestHelp::UIUnitTestHelp(UIElement* newElement, string className)
: mFontSize( 28 ), mFontRed ( 0 ), mFontGreen ( 0 ), mFontBlue ( 255 ),
mElementInfoOffset( 0 ), mTestNumOffset ( 0 ), mTestNumNum( 1 ), mDelayTime ( 1000 ),
mSRend( NULL ), mInitialized( false )
{
    mTestElement = newElement;

    mInfoText.ChangeText( " ", mFontSize, mFontRed, mFontGreen, mFontBlue);
    mElementTypeText.ChangeText( "(" + className + ")", mFontSize, mFontRed, mFontGreen, mFontBlue);
    mTestNumText.ChangeText("Test #", mFontSize, mFontRed, mFontGreen, mFontBlue);
    mTestNum.ChangeText( "0", mFontSize, mFontRed, mFontGreen, mFontBlue);

    int lineSpacing = 7;

    mInfoStart.Set(5, 5);
    mElementInfoOffset = mFontSize + lineSpacing;
    mTestNumOffset = 2 * mElementInfoOffset;

    // Define new texture for elementImage
    mElementImage = ResourceManager::GetInstance()->LoadTexture("UITest.png");

    mSRend = SDLRenderer::GetInstance();
    //tacAssert(mSRend);

    Initialize();

}// UIUnitTestHelp




UIUnitTestHelp::~UIUnitTestHelp()
{
}// ~UIUnitTestHelp


//============================= OPERATORS ====================================



//============================= OPERATIONS ===================================


void UIUnitTestHelp::RenderSelf(SDL_Surface* destination)
{
    UIElement::RenderSelf(destination);

    mInfoText.RenderSelf(destination);
    mElementTypeText.RenderSelf(destination);
    mTestNumText.RenderSelf(destination);
    mTestNum.RenderSelf(destination);
}


void UIUnitTestHelp::RunBasicTest(void)
{


    // Making sure testElement has been intialized
    if (mTestElement) {

        if (!mInitialized)
            Initialize();


        int width;
        int height;
        Point origin;
        if (mTestElement->GetElement()==NULL)
        {
            width = 0;
            height = 0;
            mInfoText.ChangeText("NULL");
            this->SetPos( origin + Point(width, 0) );
            // I think i have to insert draw here....
            mSRend->Draw();
            Delay();

            mTestNumNum++;
        }
        else
        {
            // Check for visibility
            mTestElement->SetVisible(true);
            mInfoText.ChangeText("YES - (0,0)");
            MoveToRight();
            mSRend->Draw();
            Delay();

            // Check for invisibility
            mTestElement->SetVisible(false);
            mInfoText.ChangeText("NO");
            mSRend->Draw();
            Delay();

            // Move position
            mTestElement->SetPos( Point(30,30) );
            mTestElement->SetVisible(true);
            MoveToRight();
            mInfoText.ChangeText("(30,30)");
            mSRend->Draw();
            Delay();


        }
    }

}

// Need to add "initialized" boolean value, so I don't have to keep adding/removing
// this and element to render Queue

void UIUnitTestHelp::RunNewTest(string message)
{

    if (mInitialized) {

        SDLRenderer *SRend = SDLRenderer::GetInstance();

        int width;
        int height;
        Point origin;
        SDL_Surface* element = mTestElement->GetElement();
        width = element->w;
        height = element->h;
        mInfoText.ChangeText("NULL");
        this->SetPos( origin + Point(width, 0) );
        // I think i have to insert draw here....
        SRend->Draw();
        Delay();

        mTestNumNum++;

    }


}

//============================= ACCESS     ===================================




void UIUnitTestHelp::SetPos( const Point & nPos)
{

    UIElement::SetPos(nPos);

    mInfoText.SetPos( mPos + mInfoStart );
    mElementTypeText.SetPos( mPos + mInfoStart + Point( 0, mElementInfoOffset) );
    mTestNumText.SetPos( mPos + mInfoStart + Point( 0, mTestNumOffset) );
    mTestNum.SetPos( mPos + mInfoStart + Point( mTestNumText.GetElement()->w + 5, mTestNumOffset) );

}

void UIUnitTestHelp::SetNewElement( UIElement* nElement )
{

    if (nElement) {

        mSRend->RemoveFromRenderQueue( mTestElement );
        mTestElement = nElement;
        mSRend->AddToRenderQueue( mTestElement );

    }

}


//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////



void UIUnitTestHelp::Delay(void)
{
    SDL_Delay(mDelayTime);
}

void UIUnitTestHelp::Initialize(void)
{
    mSRend->AddToRenderQueue( this );
    mSRend->AddToRenderQueue( mTestElement );
    mInitialized = true;
}

void UIUnitTestHelp::MoveToRight(void)
{
    if (mTestElement)
        SetPos( mTestElement->GetPos() + Point( mTestElement->GetElement()->w + 5, 0) );

}

/////////////////////////////// PRIVATE    ///////////////////////////////////