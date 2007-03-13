/**
 * File: UILoseLayout.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, February 15 2007 | Initial Creation
 * Karl Schmidt, March 9 2007	 	| Changed textures to png
 */

#include <util.h>


#include "UILoseLayout.h"                                // class implemented
#include "UIText.h"
#include "UIImage.h"
#include "UIManager.h"

#include <GameEngine/GameEngine.h>

/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

UILoseLayout::UILoseLayout()
{
    UIImage *temp = new UIImage("castle.png");
    mElements.push_back(temp);

    UIText *tempText = new UIText("Game Over", 70, 255, 0, 0);
    tempText->SetPos( Point(124,50) );
    mElements.push_back(tempText);

    tempText = new UIText("YOU LOST...", 50, 255, 0, 0);
    tempText->SetPos( Point(175,145) );
    mElements.push_back(tempText);


    tempText = new UIText("Press CONFIRM to return to Main Menu", 24, 255, 0, 0);
    tempText->SetPos( Point(94, 390) );
    mElements.push_back(tempText);

    mName = "Lose";

}// UILoseLayout



UILoseLayout::~UILoseLayout()
{
}// ~UILoseLayout


//============================= OPERATORS ====================================

void UILoseLayout::ProcessEvent( const InputManager::INPUTKEYS evt )
{
    if (evt==InputManager::CONFIRM)
    {


        UIManager *uim = UIManager::GetInstance();
        // Pop the battle layout and this win layout
        //uim->PopLayout();
        //uim->PopLayout();
        uim->PopAllLayouts();  // automatcially adds titlescreen
        uim->PushLayout("MainMenu");
        //uim->PushLayout("OverMap");

        GameEngine::GetInstance()->BattleOver();
    }

}



//============================= OPERATIONS ===================================
//============================= ACCESS     ===================================
//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
