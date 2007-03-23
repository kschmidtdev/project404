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
*/

#include "UITitleScreenLayout.h"                                // class implemented

#include <util.h>

#include <UI/UIImage.h>
#include <UI/UIManager.h>
#include <UI/UIText.h>


/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

UITitleScreenLayout::UITitleScreenLayout()
{
    mName = "TitleScreen";

    UIImage *temp = new UIImage("castle_title.png");
    mElements.push_back(temp);

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
            UIManager::GetInstance()->PushLayout("MainMenu");
            break;
        default:
            break;
    }

}

//============================= ACCESS     ===================================
//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
