/**
 * File: UILayoutTestHelp.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, March 14 2007 | Initial Creation
 */
#include "UILayoutTestHelp.h"                                // class implemented

#include "UIText.h"

/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

UILayoutTestHelp::UILayoutTestHelp(UILayout* test)
: mTestLayout(NULL), mMessage( NULL ), mDelay( 350 ), mSR( NULL )
{
    mTestLayout = test;
    mMessage = new UIText(" ", 18, 0, 0, 0);
    mElementImage = ResourceManager::GetInstance()->LoadTexture("LayoutBackdrop.png");
    mSR = SDLRenderer::GetInstance();
}// UILayoutTestHelp


UILayoutTestHelp::~UILayoutTestHelp()
{
    mSR->RemoveFromRenderQueue(this);
    delete mMessage;
    mSR = NULL;
}// ~UILayoutTestHelp


//============================= OPERATORS ====================================


/*void UILayoutTestHelp::RunNewInputTest(void)
{

}*/





//============================= OPERATIONS ===================================

void UILayoutTestHelp::RunBasicTest(void)
{

    // OnLoad
    mTestLayout->OnLoad();

    // Add elements to RenderQueue
    //SDLRenderer *SRend = SDLRenderer::GetInstance();
    mSR->AddToRenderQueue(this);
    mMessage->ChangeText(mTestLayout->GetName() + " Loaded");
    CenterText();
    mSR->Draw();
    SDL_Delay( mDelay );

    // OnClose
    mTestLayout->OnClose();
    mMessage->ChangeText("Clear");
    CenterText();
    mSR->Draw();
    SDL_Delay( mDelay );


}


void UILayoutTestHelp::RenderSelf(SDL_Surface* destination)
{
    UIElement::RenderSelf(destination);
    if (mVisible)
    {
        mMessage->RenderSelf(destination);
    }
}

void UILayoutTestHelp::CenterText(void)
{

    // Find Text width
    SDL_Surface *textSurface = mMessage->GetElement();
    int textWidth, textHeight;
    if( textSurface )
    {
        textWidth = textSurface->w;
        textHeight = textSurface->h;
    }
    else
    {
        textWidth = textHeight = 0;
    }

    // Find Image Width
    int imageWidth, imageHeight;
    if (mElementImage)
    {
        imageWidth = mElementImage->w;
        imageHeight = mElementImage->h;
    }
    else
    {
        imageWidth = imageHeight = 0;
    }

    // Find Offset Point
    Point offset;
    offset.Set( (int) (imageWidth - textWidth) / 2, (int) (imageHeight - textHeight) / 2);

    // Move to position
    mMessage->SetPos( mPos + offset );

}

//============================= ACCESS     ===================================

void UILayoutTestHelp::SetPos( const Point & nPos )
{
    mPos = nPos;

    CenterText();


}

//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
