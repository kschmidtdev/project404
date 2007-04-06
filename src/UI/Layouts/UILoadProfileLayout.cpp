/**
 * File: UILoadProfileLayout.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, March 18 2007 | Initial Creation
 * Karl Schmidt, March 22 2007    | Correcting include orders and paths
 * Andrew Osborne, March 24 2007, Proper UI Implementation
 * Karl Schmidt, March 25 2007   | Added functionality for loading profiles, and also going back to the previous menu
 * Andrew Osborne, March 29 2007 | Fixed missing code that calls the password verification screen
 * Karl Schmidt, April 5 2007    | Added code to not use display user1 in the list of profiles
 */
#include "UILoadProfileLayout.h"                                // class implemented

#include <util.h>

#include <UI/UIImage.h>
#include <UI/UIMenu.h>
#include <UI/UIManager.h>
#include <UI/FuncObj.h>
#include <Database/DBEngine.h>
#include <SecurityManager.h>

class LoadProfileMenuFunction : public FuncObj
{
public:
    LoadProfileMenuFunction( const std::string & name)
    : mUserName(name)
    {
    }

    void operator()(void)
    {
        DBEngine::GetInstance()->SetCurrentProfileName( mUserName );
        UIManager::GetInstance()->PopLayout();
        UIManager::GetInstance()->PushLayout("PasswordVer");
    }


protected:
    std::string mUserName;

};

class LoadProfileBackFunction : public FuncObj
{
    virtual void operator()(void)
    {
        UIManager::GetInstance()->PopLayout();
    }
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

    const std::vector<std::string> profileNames = SecurityManager::GetInstance()->GetListOfLoadedUsernames();

    mMenu->ClearButtons();
    for ( std::vector<std::string>::const_iterator i = profileNames.begin(); i != profileNames.end(); ++i )
    {
        // Internally-used profile name for encrypting/decrypting database.xml
        if( *i != "user1" )
        {
            mMenu->AddButton( *i, new LoadProfileMenuFunction( *i ) );
        }
    }

    if( !mMenu->Empty() )
    {
        mMenu->AddBlankRow();
    }
    mMenu->AddButton( "Back", new LoadProfileBackFunction() );
}

//============================= ACCESS     ===================================
//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
