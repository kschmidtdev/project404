/**
 * File: UIWinLayout.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, February 15 2007 | Initial Creation
 * Karl Schmidt, March 9 2007	 	| Changed textures to png
 * Karl Schmidt, March 12 2007		| Cleaned up ProcessEvent so it goes to the Overmap correctly
 * Karl Schmidt, March 14 2007		| Force the current turn to the player's when the game is over
 * 									  so the AI doesn't try to do something and then crash the game
 * Karl Schmidt, March 15 2007      | Moved that hack elsewhere so it happens earlier
 * Karl Schmidt, March 22 2007      | Correcting include orders and paths
 * Andrew Osborne, April 4 2007 | Made it a little more visually clear that you won.
 */

#include "UIWinLayout.h"                                // class implemented

#include <util.h>

#include <UI/UIManager.h>
#include <UI/UIImage.h>
#include <UI/UIText.h>

#include <GameEngine/GameEngine.h>


/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

UIWinLayout::UIWinLayout()
{
    //UIImage *temp = new UIImage("screen_win.png");
    UIImage *temp = new UIImage("castleplain_darkened.png");
    mElements.push_back(temp);

    UIText *tempText = new UIText("Congradulations", 60, 255, 255, 255);
    tempText->SetPos( Point(81,60) );
    mElements.push_back(tempText);

    tempText = new UIText("YOU WON", 50, 255, 255, 255);
    tempText->SetPos( Point(195,175) );
    mElements.push_back(tempText);


    tempText = new UIText("Press CONFIRM to return to Over-Map", 24, 255, 255, 255);
    tempText->SetPos( Point(94, 390) );
    mElements.push_back(tempText);

    mName = "Win";

}// UIWinLayout


UIWinLayout::~UIWinLayout()
{
}// ~UIWinLayout


//============================= OPERATORS ====================================


void UIWinLayout::ProcessEvent( const InputManager::INPUTKEYS evt )
{
    if (evt==InputManager::CONFIRM)
    {
        GameEngine::GetInstance()->CityDefeated();

        UIManager *uim = UIManager::GetInstance();
        uim->PopAllLayouts();  // automatically adds titlescreen
        uim->PushLayout("OverMap");

        GameEngine::GetInstance()->BattleOver();
    }

}

//============================= OPERATIONS ===================================
//============================= ACCESS     ===================================
//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
