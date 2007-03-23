/**
 * File: UIOptionsLayout.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, March 18 2007 | Initial Creation
 * Karl Schmidt, March 22 2007    | Correcting include orders and paths
 */
#include "UIOptionsLayout.h"                                // class implemented

#include <util.h>

#include <UI/UIManager.h>

#include <UI/UIText.h>

/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

UIOptionsLayout::UIOptionsLayout()
{
    UIText* temp = new UIText("Options Layout", 20, 255, 0, 0);

    mElements.push_back(temp);

    mName = "Options";

}// UIOptionsLayout


UIOptionsLayout::~UIOptionsLayout()
{
}// ~UIOptionsLayout


//============================= OPERATORS ====================================

//============================= OPERATIONS ===================================


void UIOptionsLayout::ProcessEvent( const InputManager::INPUTKEYS evt )
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
