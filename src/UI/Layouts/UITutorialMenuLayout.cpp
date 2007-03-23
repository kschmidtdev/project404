/**
 * File: UITutorialMenuLayout.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, March 18 2007 | Initial Creation
 * Karl Schmidt, March 22 2007      | Correcting include orders and paths
 */
#include "UITutorialMenuLayout.h"                                // class implemented

#include <util.h>

#include <UI/UIMenu.h>
#include <UI/UIManager.h>
#include <UI/FuncObj.h>
#include <UI/UIImage.h>

class ViewTutorialFunction : public FuncObj
{
    virtual void operator()(void)
    {
        // Add code to create new game???
        UIManager::GetInstance()->PopLayout();
        UIManager::GetInstance()->PushLayout("Tutorial");
    }
};

class SkipTutorialFunction : public FuncObj
{
    virtual void operator()(void)
    {
        // Add code to create new game????
        UIManager::GetInstance()->PopLayout();
        UIManager::GetInstance()->PushLayout("OverMap");
    }
};

/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

UITutorialMenuLayout::UITutorialMenuLayout()
{
    UIImage *tempBack = new UIImage("castle_main.png");
    mElements.push_back(tempBack);

    UIMenu *tempMenu = new UIMenu();
    tempMenu->SetPos( Point(245,255) );
    tempMenu->AddButton( "View Tutorial", new ViewTutorialFunction() );
    tempMenu->AddButton( "Skip Tutorial", new SkipTutorialFunction() );
    mDefaultEventListener = tempMenu;
    mElements.push_back(tempMenu);

    mName = "TutorialMenu";

}// UITutorialMenuLayout


UITutorialMenuLayout::~UITutorialMenuLayout()
{
}// ~UITutorialMenuLayout


//============================= OPERATORS ====================================

//============================= OPERATIONS ===================================



//============================= ACCESS     ===================================
//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
