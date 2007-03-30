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
        default:
            break;
    }




}

//============================= OPERATIONS ===================================
//============================= ACCESS     ===================================
//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
