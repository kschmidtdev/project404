/**
 * File: UIWinLayout.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, February 15 2007 | Initial Creation
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
    UIImage *temp = new UIImage("screen_win.bmp");
    mElements.push_back(temp);

    //UIText *tempText = new UIText("Congratulations", 70, 255, 0, 0);
    //tempText->SetPos( Point(33,50) );
    //mElements.push_back(tempText);

    //tempText = new UIText("YOU WON!!", 50, 255, 0, 0);
    //tempText->SetPos( Point(175,145) );
    //mElements.push_back(tempText);


    //tempText = new UIText("Press CONFIRM to return to Main Menu", 24, 255, 0, 0);
    //tempText->SetPos( Point(94, 390) );
    //mElements.push_back(tempText);

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
        UIManager *uim = UIManager::GetInstance();
        uim->PopAllLayouts();  // automatcially adds titlescreen
        uim->PushLayout("MainMenu");
        GameEngine::GetInstance()->BattleOver();
    }

}

//============================= OPERATIONS ===================================
//============================= ACCESS     ===================================
//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
