/**
 * File: UIMarketLayout.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, March 18 2007 | Initial Creation
 */
#include "UIMarketLayout.h"                                // class implemented
#include "UIManager.h"

#include <UI/UIText.h>

/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

UIMarketLayout::UIMarketLayout()
{
    UIText* temp = new UIText("Market Layout", 20, 255, 0, 0);

    mElements.push_back(temp);

    mName = "Market";
}// UIMarketLayout


UIMarketLayout::~UIMarketLayout()
{
}// ~UIMarketLayout


//============================= OPERATORS ====================================


//============================= OPERATIONS ===================================

void UIMarketLayout::ProcessEvent( const InputManager::INPUTKEYS evt )
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
