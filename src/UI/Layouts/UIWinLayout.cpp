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
 */

#include <util.h>


#include "UIWinLayout.h"                                // class implemented
#include "UIManager.h"
#include "UIImage.h"
#include "UIText.h"

#include <GameEngine/GameEngine.h>


/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

UIWinLayout::UIWinLayout()
{
    UIImage *temp = new UIImage("screen_win.png");
    mElements.push_back(temp);

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
