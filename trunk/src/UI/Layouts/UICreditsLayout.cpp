/**
 * File: UICreditsLayout.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, March 18 2007 | Initial creation
 * Karl Schmidt, March 22 2007    | Correcting include orders and paths
 * Andrew Osborne, March 24 2007 | Created proper UI Implementation
 */
#include "UICreditsLayout.h"                                // class implemented

#include <util.h>

#include <UI/UIManager.h>
#include <UI/UIImage.h>

/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

UICreditsLayout::UICreditsLayout()
{
    UIImage* temp = new UIImage("credits.png");

    mElements.push_back(temp);

    mName = "Credits";
}// UICreditsLayout


UICreditsLayout::~UICreditsLayout()
{
}// ~UICreditsLayout


//============================= OPERATORS ====================================

//============================= OPERATIONS ===================================

void UICreditsLayout::ProcessEvent( const InputManager::INPUTKEYS evt )
{
    switch (evt)
    {
        case InputManager::CONFIRM:
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
