/**
 * File: UILoadProfileLayout.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, March 18 2007 | Initial Creation
 */
#include "UILoadProfileLayout.h"                                // class implemented
#include "UIText.h"
#include "UIManager.h"

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
