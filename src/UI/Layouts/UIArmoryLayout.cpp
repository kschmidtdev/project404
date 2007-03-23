/**
 * File: UIArmoryLayout.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, March 18 2007 | Initial Creation
 * Karl Schmidt, March 22 2007    | Correcting include orders and paths
 */
#include "UIArmoryLayout.h"                                // class implemented

#include <util.h>

#include <UI/UIManager.h>
#include <UI/UIText.h>

/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

UIArmoryLayout::UIArmoryLayout()
{
    UIText* temp = new UIText("Armory Layout", 20, 255, 0, 0);

    mElements.push_back(temp);

    mName = "Armory";
}// UIArmoryLayout


UIArmoryLayout::~UIArmoryLayout()
{
}// ~UIArmoryLayout


//============================= OPERATORS ====================================



//============================= OPERATIONS ===================================

void UIArmoryLayout::ProcessEvent( const InputManager::INPUTKEYS evt )
{
    switch (evt)
    {
        case InputManager::CONFIRM:
            // Need to add code here about loading the game
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
