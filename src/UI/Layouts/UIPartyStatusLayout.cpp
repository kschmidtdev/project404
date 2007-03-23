/**
 * File: UIPartyStatusLayout.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, March 18 2007 | Initial Creation (Empty)
 * Karl Schmidt, March 22 2007    | Correcting include orders and paths
 */
#include "UIPartyStatusLayout.h"                                // class implemented

#include <util.h>

#include <UI/UIManager.h>
#include <UI/UIText.h>

/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

UIPartyStatusLayout::UIPartyStatusLayout()
{

    UIText* temp = new UIText("Party Status Layout", 20, 255, 0, 0);

    mElements.push_back(temp);

    mName = "PartyStatus";

}// UIPartyStatusLayout



UIPartyStatusLayout::~UIPartyStatusLayout()
{
}// ~UIPartyStatusLayout


//============================= OPERATORS ====================================



//============================= OPERATIONS ===================================


void UIPartyStatusLayout::ProcessEvent( const InputManager::INPUTKEYS evt )
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
