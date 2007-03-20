/**
 * File: UICreditsLayout.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Name, Date | Work Done
 */
#include "UICreditsLayout.h"                                // class implemented
#include "UIManager.h"

#include <UI/UIText.h>

/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

UICreditsLayout::UICreditsLayout()
{
    UIText* temp = new UIText("Credits Layout", 20, 255, 0, 0);

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
