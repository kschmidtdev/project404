/**
 * File: UISaveGameLayout.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, March 18 2007 | Initial creation
 */
#include "UISaveGameLayout.h"                                // class implemented
#include "UIManager.h"

#include <UI/UIText.h>

/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

UISaveGameLayout::UISaveGameLayout()
{
     UIText* temp = new UIText("Save Game Layout", 20, 255, 0, 0);

    mElements.push_back(temp);

    mName = "SaveGame";
}// UISaveGameLayout


UISaveGameLayout::~UISaveGameLayout()
{
}// ~UISaveGameLayout


//============================= OPERATORS ====================================

//============================= OPERATIONS ===================================

void UISaveGameLayout::ProcessEvent( const InputManager::INPUTKEYS evt )
{
    switch (evt)
    {
        case InputManager::CONFIRM:
            // Currently relying on code before this layout was 'pushed' to actually save the game
            UIManager::GetInstance()->PopLayout();
            break;
        default:
            break;
    }

}

//============================= ACCESS     ===================================
//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
