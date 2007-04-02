/**
 * File: UIPasswordVerificationLayout.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, February 15 2007 | Initial Creation
 * Karl Schmidt, March 9 2007	 	| Changed textures to png
 * Karl Schmidt, March 22 2007      | Correcting include orders and paths
 * Karl Schmidt, March 29 2007      | Password checking against is the selected profile
 * Andrew Osborne, April 1 2007 | Added notification and ability to go back to profile menu screen.
 */

#include "UIPasswordVerificationLayout.h"                                // class implemented

#include <util.h>

#include <UI/UIManager.h>
#include <SecurityManager.h>
#include <UI/UIImage.h>
#include <Database/DBEngine.h>

/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

UIPasswordVerificationLayout::UIPasswordVerificationLayout()
{
    // Create default Password
    SecurityManager::GetInstance()->AddUser( "user1", "rrrr" );

    UIImage *temp = new UIImage( "menu_password.png" );
    mElements.push_back(temp);

    mStarString = " ";
    mPasswordText = new UIText( mStarString, 30, 255, 0, 0 );

    mPasswordText->SetPos( Point(285,195) );
    mElements.push_back(mPasswordText);

    UIText* backMessage = new UIText("Press CANCEL to Go Back to Profile Selection", 18, 255, 0, 0);
    backMessage->SetPos( Point(120, 380) );
    mElements.push_back(backMessage);



    mName = "PasswordVer";

}// UIPasswordVerificationLayout



UIPasswordVerificationLayout::~UIPasswordVerificationLayout()
{
}// ~UIPasswordVerificationLayout


//============================= OPERATORS ====================================

void UIPasswordVerificationLayout::ProcessEvent( const InputManager::INPUTKEYS evt )
{
    switch(evt)
    {
        case InputManager::UP:
            mPwdString += "u";
            mStarString += "*";
            mPasswordText->ChangeText(mStarString);
            break;
        case InputManager::DOWN:
            mPwdString += "d";
            mStarString += "*";
            mPasswordText->ChangeText(mStarString);
            break;
        case InputManager::LEFT:
            mPwdString += "l";
            mStarString += "*";
            mPasswordText->ChangeText(mStarString);
            break;
        case InputManager::RIGHT:
            mPwdString += "r";
            mStarString += "*";
            mPasswordText->ChangeText(mStarString);
            break;
        case InputManager::CONFIRM:
            if (SecurityManager::GetInstance()->VerifyPassword( DBEngine::GetInstance()->GetCurrentProfileName() , mPwdString))
            {
                UIManager::GetInstance()->PushLayout("MainMenu");
            }
            else
            {
                mStarString = " ";
                mPwdString = "";
                mPasswordText->ChangeText(mStarString);
            }
            break;
        case InputManager::CANCEL:
            UIManager::GetInstance()->PopLayout();
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
