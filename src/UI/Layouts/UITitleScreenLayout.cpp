/**
 * File: UITitleScreenLayout.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, February 10 2007 | Initial Creation
 * Andrew Osborne, February 10 2007 | Documentation
 * Andrew Osborne, February 14 2007 | Added ProcessEvent method
 * Andrew Osborne, February 14 2007 | Made final version for title screen
 * Karl Schmidt, February 14 2007 	| Moved the background image to the upper left corner, deleted commented code
 * Karl Schmidt, March 9 2007	 	| Changed textures to png
 * Karl Schmidt, March 22 2007      | Correcting include orders and paths
 * Karl Schmidt, March 29 2007      | Added title image fading
*/

#include "UITitleScreenLayout.h"                                // class implemented

#include <util.h>

#include <UI/UIImage.h>
#include <UI/UIManager.h>
#include <UI/UIText.h>


/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

UITitleScreenLayout::UITitleScreenLayout()
: mTeamTitle( NULL ),
  mCastleTitle( NULL ),
  mFadeState( TEAMTITLE_IN )
{
    mName = "TitleScreen";

    mTeamTitle = new UIImage("team404Presents.png");
    mCastleTitle = new UIImage("castle_title.png");
    mElements.push_back( mCastleTitle );
    mElements.push_back( mTeamTitle );

    mTeamTitle->SetAlpha( 0 );
    mCastleTitle->SetAlpha( 0 );
}// UITitleScreenLayout

UITitleScreenLayout::~UITitleScreenLayout()
{
}// ~UITitleScreenLayout


//============================= OPERATORS ====================================
//============================= OPERATIONS ===================================

void UITitleScreenLayout::ProcessEvent( const InputManager::INPUTKEYS evt )
{
    switch (evt)
    {
        case InputManager::CONFIRM:
        {
            if( mFadeState != CASTLETITLE_DONE )
            {
                mFadeState = CASTLETITLE_DONE;
                mTeamTitle->SetAlpha( 0 );
                mCastleTitle->SetAlpha( 255 );
            }
            else
            {
                UIManager::GetInstance()->PushLayout("ProfileMenu");
            }

            break;
        }
        default:
            break;
    }

}

void UITitleScreenLayout::Update()
{
    static Uint32 nextIncrement = 0;

    if( mFadeState == TEAMTITLE_IN )
    {
        if( mTeamTitle->GetAlpha() < 255 )
        {
            if( nextIncrement < SDL_GetTicks() )
            {
                mTeamTitle->SetAlpha( mTeamTitle->GetAlpha() + 5 );
                nextIncrement = SDL_GetTicks() + 20;
            }
        }
        else
        {
            mFadeState = TEAMTITLE_WAIT;
            nextIncrement = SDL_GetTicks() + 2000;
        }
    }
    else if( mFadeState == TEAMTITLE_WAIT )
    {
        if( nextIncrement < SDL_GetTicks() )
        {
            mFadeState = TEAMTITLE_OUT;
        }
    }
    else if( mFadeState == TEAMTITLE_OUT )
    {
        if( mTeamTitle->GetAlpha() > 0 )
        {
            if( nextIncrement < SDL_GetTicks() )
            {
                mTeamTitle->SetAlpha( mTeamTitle->GetAlpha() - 5 );
                if( mTeamTitle->GetAlpha() < 0 )
                {
                    mTeamTitle->SetAlpha( 0 );
                }
                nextIncrement = SDL_GetTicks() + 20;
            }
        }
        else
        {
            mFadeState = CASTLETITLE_IN;
        }
    }
    else if( mFadeState == CASTLETITLE_IN )
    {
        if( mCastleTitle->GetAlpha() < 255 )
        {
            if( nextIncrement < SDL_GetTicks() )
            {
                mCastleTitle->SetAlpha( mCastleTitle->GetAlpha() + 5 );
                nextIncrement = SDL_GetTicks() + 20;
            }
        }
        else
        {
            mFadeState = CASTLETITLE_DONE;
        }
    }
}

//============================= ACCESS     ===================================
//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
