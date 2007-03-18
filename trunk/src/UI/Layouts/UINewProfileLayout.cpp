/**
 * File: UINewProfileLayout.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, March 18 2007 | Initial Creation
 */
#include "UINewProfileLayout.h"                                // class implemented
#include "UIText.h"
#include "UIManager.h"

/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

UINewProfileLayout::UINewProfileLayout()
{
    UIText* temp = new UIText("New Profile Layout", 20, 255, 0, 0);

    mElements.push_back(temp);

    mName = "NewProfile";
}// UINewProfileLayout



UINewProfileLayout::~UINewProfileLayout()
{
}// ~UINewProfileLayout


//============================= OPERATORS ====================================
//============================= OPERATIONS ===================================

void UINewProfileLayout::ProcessEvent( const InputManager::INPUTKEYS evt )
{

    switch (evt)
    {
        case InputManager::CONFIRM:
            UIManager::GetInstance()->PopLayout();
            UIManager::GetInstance()->PushLayout("MainMenu");
            // Eventually should also push the SetPassword Layout, to update/set password
            break;
    }

}

//============================= ACCESS     ===================================
//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
