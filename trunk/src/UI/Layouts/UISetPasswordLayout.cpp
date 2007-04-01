/**
 * File: UISetPasswordLayout.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, February 15 2007 | Initial Creation
 * Karl Schmidt, March 22 2007      | Correcting include orders and paths
 * Karl Schmidt, March 23 2007      | Got rid of more using namespace std; usage
 * Karl Schmidt, March 31 2007      | Added Reset() to reset the screen, it now checks/sets the currently
                                      logged-on user, also can be used to set a password for the first time
 * Karl Schmidt, April 1 2007       | Fixed a bug where a blank password was allowed to be set
 */

#include "UISetPasswordLayout.h"                                // class implemented

#include <util.h>

#include <UI/UIManager.h>
#include <SecurityManager.h>
#include <Database/DBEngine.h>

/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

UISetPasswordLayout::UISetPasswordLayout()
: mPasswordEntryState( 0 ), mOldStarString ("Old Pwd:"), mNewStarString ( "New Pwd:"), mConfirmStarString( "Confirm Pwd:"),
mOldPwdUIText(NULL), mNewPwdUIText(NULL), mConfirmPwdUIText(NULL), mOldPwd(""), mNewPwd(""), mConfirmPwd(""),
  mCreatingPassword( false )
{
    mName = "SetPassword";

    // Old Password
    mOldPwdUIText = new UIText(mOldStarString, 30, 255, 0, 0);
    mOldPwdUIText->SetPos( Point(175, 145) );
    mElements.push_back(mOldPwdUIText);

    // New Password
    mNewPwdUIText = new UIText(mNewStarString, 30, 255, 0, 0);
    mNewPwdUIText->SetPos( Point(175, 185) );
    mNewPwdUIText->SetVisible( false );
    mElements.push_back(mNewPwdUIText);

    // Confirm Password
    mConfirmPwdUIText = new UIText(mConfirmStarString, 30, 255, 0, 0);
    mConfirmPwdUIText->SetPos( Point(175, 225) );
    mConfirmPwdUIText->SetVisible(false);
    mElements.push_back(mConfirmPwdUIText);

    UIText *tempText = new UIText("Set Password", 40, 255, 0, 0);
    tempText->SetPos( Point(98,50) );
    mElements.push_back(tempText);

    tempText = new UIText("Press CONFIRM to advance", 24, 255, 0, 0);
    tempText->SetPos( Point(115, 390) );
    mElements.push_back(tempText);



}// UISetPasswordLayout


UISetPasswordLayout::~UISetPasswordLayout()
{
}// ~UISetPasswordLayout


//============================= OPERATORS ====================================

void UISetPasswordLayout::OnLoad()
{
    UILayout::OnLoad();

    ResetScreen();
}

void UISetPasswordLayout::ResetScreen()
{
    mNewPwd = "";
    mNewStarString = "New Pwd:";
    mNewPwdUIText->ChangeText(mNewStarString);
    mConfirmPwd = "";
    mConfirmStarString = "Confirm Pwd:";
    mConfirmPwdUIText->SetVisible(false);
    mConfirmPwdUIText->ChangeText(mConfirmStarString);

    // If the user we are changing a password for exists already,
    // we are changing the password.
    if( SecurityManager::GetInstance()->GetUserHash( DBEngine::GetInstance()->GetCurrentProfileName() ) != "" )
    {
        mOldPwd = "";
        mOldStarString = "Old Pwd:";
        mOldPwdUIText->ChangeText(mOldStarString);
        mOldPwdUIText->SetVisible( true );
        mPasswordEntryState = 0;
        mCreatingPassword = false;

        mNewPwdUIText->SetVisible( false );
    }
    else
    {
        mOldPwdUIText->SetVisible( false );
        mNewPwdUIText->SetVisible( true );
        mPasswordEntryState = 1;
        mCreatingPassword = true;
    }
}

void UISetPasswordLayout::ProcessEvent( const InputManager::INPUTKEYS evt )
{
    switch(evt)
    {
        case InputManager::UP:
            switch (mPasswordEntryState)
            {
                case 0:
                    mOldPwd += "u";
                    mOldStarString += "*";
                    mOldPwdUIText->ChangeText(mOldStarString);
                    break;
                case 1:
                    mNewPwd += "u";
                    mNewStarString += "*";
                    mNewPwdUIText->ChangeText(mNewStarString);
                    break;
                case 2:
                    mConfirmPwd += "u";
                    mConfirmStarString += "*";
                    mConfirmPwdUIText->ChangeText(mConfirmStarString);
                    break;
            }
            break;
        case InputManager::DOWN:
            switch (mPasswordEntryState)
            {
                case 0:
                    mOldPwd += "d";
                    mOldStarString += "*";
                    mOldPwdUIText->ChangeText(mOldStarString);
                    break;
                case 1:
                    mNewPwd += "d";
                    mNewStarString += "*";
                    mNewPwdUIText->ChangeText(mNewStarString);
                    break;
                case 2:
                    mConfirmPwd += "d";
                    mConfirmStarString += "*";
                    mConfirmPwdUIText->ChangeText(mConfirmStarString);
                    break;
            }
            break;
        case InputManager::LEFT:
            switch (mPasswordEntryState)
            {
                case 0:
                    mOldPwd += "l";
                    mOldStarString += "*";
                    mOldPwdUIText->ChangeText(mOldStarString);
                    break;
                case 1:
                    mNewPwd += "l";
                    mNewStarString += "*";
                    mNewPwdUIText->ChangeText(mNewStarString);
                    break;
                case 2:
                    mConfirmPwd += "l";
                    mConfirmStarString += "*";
                    mConfirmPwdUIText->ChangeText(mConfirmStarString);
                    break;
            }
            break;
        case InputManager::RIGHT:
            switch (mPasswordEntryState)
            {
                case 0:
                    mOldPwd += "r";
                    mOldStarString += "*";
                    mOldPwdUIText->ChangeText(mOldStarString);
                    break;
                case 1:
                    mNewPwd += "r";
                    mNewStarString += "*";
                    mNewPwdUIText->ChangeText(mNewStarString);
                    break;
                case 2:
                    mConfirmPwd += "r";
                    mConfirmStarString += "*";
                    mConfirmPwdUIText->ChangeText(mConfirmStarString);
                    break;
            }
            break;
        case InputManager::CONFIRM:
            switch (mPasswordEntryState)
            {
                case 0:
                    if (SecurityManager::GetInstance()->VerifyPassword( DBEngine::GetInstance()->GetCurrentProfileName(), mOldPwd))
                    {
                        mPasswordEntryState++;
                        mNewPwdUIText->SetVisible(true);
                    }
                    else
                    {
                        mOldPwd = "";
                        mOldStarString = "Old Pwd:";
                        mOldPwdUIText->ChangeText(mOldStarString);
                    }
                    break;
                case 1:
                    mPasswordEntryState++;
                    mConfirmPwdUIText->SetVisible(true);
                    break;
                case 2:
                    if( mConfirmPwd != "" && mConfirmPwd == mNewPwd )
                    {
                        if( mCreatingPassword )
                        {
                            SecurityManager::GetInstance()->AddUser( DBEngine::GetInstance()->GetCurrentProfileName(), mConfirmPwd );
                        }
                        else
                        {
                            SecurityManager::GetInstance()->DeleteUser( DBEngine::GetInstance()->GetCurrentProfileName() );
                            SecurityManager::GetInstance()->AddUser( DBEngine::GetInstance()->GetCurrentProfileName(), mConfirmPwd);
                        }
                        UIManager::GetInstance()->PopLayout();
                        if( mCreatingPassword )
                        {
                            UIManager::GetInstance()->PushLayout("MainMenu");
                        }
                    }
                    else
                    {
                        ResetScreen();
                    }
                    break;
            }
            break;
        case InputManager::CANCEL:
        {
            if( !mCreatingPassword )
            {
                mOldPwd = "";
                mOldStarString = "Old Pwd:";
                mOldPwdUIText->ChangeText(mOldStarString);
            }
            mNewPwd = "";
            mNewStarString = "New Pwd:";
            mNewPwdUIText->SetVisible(false);
            mNewPwdUIText->ChangeText(mNewStarString);
            mConfirmPwd = "";
            mConfirmStarString = "Confirm Pwd:";
            mConfirmPwdUIText->SetVisible(false);
            mConfirmPwdUIText->ChangeText(mConfirmStarString);
            if( !mCreatingPassword )
            {
                mPasswordEntryState = 0;
            }
            else
            {
                mPasswordEntryState = 1;
            }
            UIManager::GetInstance()->PopLayout();
        }
        break;

        default:
            break;
    }


}

//============================= OPERATIONS ===================================
//============================= ACCESS     ===================================
//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
