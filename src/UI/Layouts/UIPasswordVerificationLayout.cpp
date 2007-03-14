/**
 * File: UIPasswordVerificationLayout.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, February 15 2007 | Initial Creation
 * Karl Schmidt, March 9 2007	 	| Changed textures to png
 */

#include <util.h>


#include "UIPasswordVerificationLayout.h"                                // class implemented
#include "UIManager.h"
#include "SecurityManager.h"

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
            if (SecurityManager::GetInstance()->VerifyPassword("user1", mPwdString))
            {
                UIManager::GetInstance()->PopAllLayouts();
            }
            else
            {
                mStarString = "Pwd:";
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
