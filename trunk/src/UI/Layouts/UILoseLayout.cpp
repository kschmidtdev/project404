/**
 * File: UILoseLayout.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, February 15 2007 | Initial Creation
 */
#include "UILoseLayout.h"                                // class implemented
#include "UIText.h"
#include "UIImage.h"
#include "UIManager.h"

/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

UILoseLayout::UILoseLayout()
{
    UIImage *temp = new UIImage("castle.bmp");
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
        uim->PopAllLayouts();  // automatcially adds titlescreen
        uim->PushLayout("MainMenu");
    }

}



//============================= OPERATIONS ===================================
//============================= ACCESS     ===================================
//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
