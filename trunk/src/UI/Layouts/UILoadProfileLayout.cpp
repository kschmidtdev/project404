/**
 * File: UILoadProfileLayout.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, March 18 2007 | Initial Creation
 * Karl Schmidt, March 22 2007    | Correcting include orders and paths
 */
#include "UILoadProfileLayout.h"                                // class implemented

#include <util.h>

#include <UI/UIText.h>
#include <UI/UIManager.h>

/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

UILoadProfileLayout::UILoadProfileLayout()
{
    UIText* temp = new UIText("New Profile Layout", 20, 255, 0, 0);

    mElements.push_back(temp);

    mName = "LoadProfile";
}// UILoadProfileLayout

UILoadProfileLayout::~UILoadProfileLayout()
{
}// ~UILoadProfileLayout


//============================= OPERATORS ====================================

//============================= OPERATIONS ===================================

void UILoadProfileLayout::ProcessEvent( const InputManager::INPUTKEYS evt )
{

    switch (evt)
    {
        case InputManager::CONFIRM:
            UIManager::GetInstance()->PopLayout();
            UIManager::GetInstance()->PushLayout("PasswordVer");
            // Eventually should also push the SetPassword Layout, to update/set password
            break;
        default:
            break;
    }

}
//============================= ACCESS     ===================================
//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
