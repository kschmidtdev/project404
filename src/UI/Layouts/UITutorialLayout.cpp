/**
 * File: UITutorialLayout.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, March 18 2007 | Initial Creation (stub)
 */
#include "UITutorialLayout.h"                                // class implemented
#include "UIManager.h"

/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

UITutorialLayout::UITutorialLayout()
{
    mElements.push_back( new UIText("Tutorial Layout", 20, 255, 0, 0) );

    mName = "Tutorial";

}// UITutorialLayout


UITutorialLayout::~UITutorialLayout()
{
}// ~UITutorialLayout


//============================= OPERATORS ====================================

//============================= OPERATIONS ===================================

void UITutorialLayout::ProcessEvent( const InputManager::INPUTKEYS evt )
{
    switch (evt)
    {
        case InputManager::CONFIRM:
            UIManager::GetInstance()->PopLayout();
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