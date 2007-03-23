/**
 * File: UIProfileMenuLayout.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, March 18 2007 | Initial Creation
 * Karl Schmidt, March 22 2007    | Correcting include orders and paths
 */
#include "UIProfileMenuLayout.h"                                // class implemented

#include <util.h>

#include <UI/UIMenu.h>
#include <UI/UIManager.h>
#include <UI/FuncObj.h>
#include <UI/UIImage.h>

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
