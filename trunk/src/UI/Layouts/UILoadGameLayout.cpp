/**
 * File: UILoadGameLayout.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, March 18 2007 | Initial Creation
 */
#include "UILoadGameLayout.h"                                // class implemented
#include "UIManager.h"

#include <UI/UIText.h>

/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

UILoadGameLayout::UILoadGameLayout()
{
    UIText* temp = new UIText("Load Game Layout", 20, 255, 0, 0);

    mElements.push_back(temp);

    mName = "LoadGame";

}// UILoadGameLayout


UILoadGameLayout::~UILoadGameLayout()
{
}// ~UILoadGameLayout


//============================= OPERATORS ====================================

//============================= OPERATIONS ===================================


void UILoadGameLayout::ProcessEvent( const InputManager::INPUTKEYS evt )
{
    switch (evt)
    {
        case InputManager::CONFIRM:
            // Need to add code here about loading the game
            UIManager::GetInstance()->PushLayout("OverMap");
            break;
        default:
            break;
    }

}
//============================= ACCESS     ===================================
//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
