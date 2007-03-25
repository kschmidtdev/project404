/**
 * File: UILoadProfileLayout.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, March 18 2007 | Initial Creation
 * Karl Schmidt, March 22 2007    | Correcting include orders and paths
 * Andrew Osborne, March 24 2007, Proper UI Implementation
 */
#include "UILoadProfileLayout.h"                                // class implemented

#include <util.h>

#include <UI/UIImage.h>
#include <UI/UIMenu.h>
#include <UI/UIManager.h>
#include <UI/FuncObj.h>



class LoadProfileFunction2 : public FuncObj
{
public:
    LoadProfileFunction2( const std::string & name)
    : mUserName(name)
    {
    }

    void operator()(void)
    {
        //GameEngine::GetInstance()->LoadProfile(mUserName);
        UIManager::GetInstance()->PopLayout();
        UIManager::GetInstance()->PushLayout("MainMenu");
    }


protected:
    std::string mUserName;

};




/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

UILoadProfileLayout::UILoadProfileLayout()
: mMenu( NULL )
{

    // Background
    UIImage* back = new UIImage("castle_main.png");
    mElements.push_back(back);

    // Menu
    mMenu = new UIMenu();
    mMenu->SetPos( Point(245,255) );
    mElements.push_back(mMenu);
    mDefaultEventListener = mMenu;

    // Name
    mName = "LoadProfile";
}// UILoadProfileLayout

UILoadProfileLayout::~UILoadProfileLayout()
{
}// ~UILoadProfileLayout


//============================= OPERATORS ====================================

//============================= OPERATIONS ===================================

/*void UILoadProfileLayout::ProcessEvent( const InputManager::INPUTKEYS evt )
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

}*/


void UILoadProfileLayout::OnLoad(void)
{

    UILayout::OnLoad();

    // Grab vector string of save files from GameEngine
    /*
    vector<string>* saveFiles = GameEngine::GetInstance()->GetSaveFiles();

    mMenu->ClearButtons();
    for (vector<string>::iterator iter = saveFiles.begin(); iter != saveFiles.end(); ++iter)
    {
        mMenu->AddButton( (*iter), new LoadGameFunction( (*iter) ) );
    }

    */

    // Temp Debug
    mMenu->ClearButtons();

    mMenu->AddButton( "User1" , new LoadProfileFunction2( "User1" ) );
    mMenu->AddButton( "User2" , new LoadProfileFunction2( "User2" ) );
    mMenu->AddButton( "User3" , new LoadProfileFunction2( "User3" ) );

}

//============================= ACCESS     ===================================
//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
