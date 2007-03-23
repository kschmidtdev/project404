/**
 * File: UINewProfileLayout.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, March 18 2007 | Initial Creation
 * Andrew Osborne, March 21 2007 | Added AlhpabetGrid to screen
 * Karl Schmidt, March 22 2007    | Correcting include orders and paths
 */
#include "UINewProfileLayout.h"                                // class implemented

#include <util.h>

#include <UI/UIText.h>
#include <UI/UIManager.h>
#include <UI/UIAlphabetGrid.h>

/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

UINewProfileLayout::UINewProfileLayout()
{
    UIElement* temp = new UIText("New Profile Layout", 20, 255, 0, 0);

    mElements.push_back(temp);

    UIAlphabetGrid *newAlpha = new UIAlphabetGrid();
    newAlpha->SetPos( Point(0, 100) );
    mDefaultEventListener = newAlpha;

    mElements.push_back(newAlpha);

    mName = "NewProfile";

}// UINewProfileLayout



UINewProfileLayout::~UINewProfileLayout()
{
}// ~UINewProfileLayout


//============================= OPERATORS ====================================
//============================= OPERATIONS ===================================

/*void UINewProfileLayout::ProcessEvent( const InputManager::INPUTKEYS evt )
{

    switch (evt)
    {
        case InputManager::CONFIRM:
            UIManager::GetInstance()->PopLayout();
            UIManager::GetInstance()->PushLayout("MainMenu");
            // Eventually should also push the SetPassword Layout, to update/set password
            break;
        default:
            break;
    }

}*/

//============================= ACCESS     ===================================
//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
