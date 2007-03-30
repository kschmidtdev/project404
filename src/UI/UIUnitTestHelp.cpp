/**
 * File: UIUnitTestHelp.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, March 13 2007 | Initial creation, Fleshed out methods
 * Karl Schmidt, March 22 2007   | Correcting include orders and paths
 * Karl Schmidt, March 23 2007   | Got rid of more using namespace std; usage
 * Karl Schmidt, March 29 2007   | Added correct superclass constructor calling, turfed an unused default constructor
 */

#include "UIUnitTestHelp.h"                                // class implemented

#include <util.h>

#include <ResourceManager/ResourceManager.h>
#include <Renderer/SDLRenderer.h>

/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

UIUnitTestHelp::UIUnitTestHelp(UIElement* newElement, const std::string & className)
: UIElement(), mFontSize( 28 ), mFontRed ( 0 ), mFontGreen ( 0 ), mFontBlue ( 255 ),
mElementInfoOffset( 0 ), mTestNumOffset ( 0 ), mTestNumNum( 1 ), mDelayTime ( 500 ),
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

    Initialize();

}// UIUnitTestHelp




UIUnitTestHelp::~UIUnitTestHelp()
{
    // must ensure elements are out of RenderQueue
    if (mTestElement)
        mSRend->RemoveFromRenderQueue(mTestElement);

    mSRend->RemoveFromRenderQueue(this);

    mSRend = NULL;

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
    if (mTestElement)
    {
        if( !mInitialized )
        {
            Initialize();
        }

        std::ostringstream oss;

        int width;
        int height;
        Point origin;
        if (mTestElement->GetElement()==NULL)
        {
            width = 0;
            height = 0;
            mInfoText.ChangeText("NULL");
            oss << mTestNumNum;
            mTestNum.ChangeText( oss.str() );
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
            oss << mTestNumNum;
            mTestNum.ChangeText( oss.str() );
            MoveToRight();
            mSRend->Draw();
            Delay();
            mTestNumNum++;

            // Check for invisibility
            mTestElement->SetVisible(false);
            mInfoText.ChangeText("NO");
            oss.str("");
            oss << mTestNumNum;
            mTestNum.ChangeText( oss.str() );
            mSRend->Draw();
            Delay();
            mTestNumNum++;

            // Move position
            mTestElement->SetPos( Point(30,30) );
            mTestElement->SetVisible(true);
            MoveToRight();
            mInfoText.ChangeText("(30,30)");
            oss.str("");
            oss << mTestNumNum;
            mTestNum.ChangeText( oss.str() );
            mSRend->Draw();
            Delay();
            mTestNumNum++;
        }
    }

}

// Need to add "initialized" boolean value, so I don't have to keep adding/removing
// this and element to render Queue

void UIUnitTestHelp::RunNewTest( const std::string & message )
{
    if (mInitialized)
    {
        SDLRenderer *SRend = SDLRenderer::GetInstance();
        std::ostringstream oss;

        mInfoText.ChangeText(message);
        oss << mTestNumNum;
        mTestNum.ChangeText( oss.str() );
        MoveToRight();
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


void UIUnitTestHelp::SetDelay(int n)
{
    mDelayTime = n;
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
