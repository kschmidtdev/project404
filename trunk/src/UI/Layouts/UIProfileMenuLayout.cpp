/**
 * File: UIProfileMenuLayout.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, March 18 2007 | Initial Creation
 */
#include "UIProfileMenuLayout.h"                                // class implemented
#include "UIMenu.h"
#include "UIManager.h"

class NewProfileFunction : public FuncObj
{
    virtual void operator()(void)
    {
        UIManager::GetInstance()->PushLayout("NewProfile");
        //UIManager::GetInstance()->PushLayout("MainMenu");
    }
};


class LoadProfileFunction : public FuncObj
{
    virtual void operator()(void)
    {
        UIManager::GetInstance()->PushLayout("LoadProfile");
        //UIManager::GetInstance()->PushLayout("MainMenu");
    }
};

class ProfileQuitFunction : public FuncObj
{
    virtual void operator()(void)
    {
        UIManager::GetInstance()->SetEndGameState(true);
    }
};


/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

UIProfileMenuLayout::UIProfileMenuLayout()
{

    mName = "ProfileMenu";

    UIImage *backImage = new UIImage("castle_main.png");
    mElements.push_back(backImage);

    UIMenu *tempMenu = new UIMenu();

    tempMenu->AddButton("New Profile", new NewProfileFunction() );
    tempMenu->AddButton("Load Profile", new LoadProfileFunction() );
    tempMenu->AddButton("Quit", new ProfileQuitFunction() );

    mElements.push_back(tempMenu);
    mDefaultEventListener = tempMenu;
    tempMenu->SetPos( Point(245,255) );


}// UIProfileMenuLayout



UIProfileMenuLayout::~UIProfileMenuLayout()
{
}// ~UIProfileMenuLayout


//============================= OPERATORS ====================================


//============================= OPERATIONS ===================================




//============================= ACCESS     ===================================
//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
