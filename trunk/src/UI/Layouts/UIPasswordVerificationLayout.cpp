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
 * Karl Schmidt, April 1 2007       | Added more notification, new backdrop texture
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

    UIImage *temp = new UIImage( "castleplain_darkened.png" );
    mElements.push_back(temp);

    mStarString = "Enter password:";
    mPasswordText = new UIText( mStarString, 30, 255, 255, 255 );

    mPasswordText->SetPos( Point(115,170) );
    mElements.push_back(mPasswordText);

    UIText* inputMessage = new UIText("Press Direction Keys to Enter Password", 18, 255, 255, 255);
    inputMessage->SetPos( Point(140, 340) );
    mElements.push_back(inputMessage);

    UIText* backMessage = new UIText("Press CANCEL to Go Back to Profile Selection", 18, 255, 255, 255);
    backMessage->SetPos( Point(120, 380) );
    mElements.push_back(backMessage);

    UIText* tempText = new UIText("Press CONFIRM to advance", 18, 255, 255, 255);
    tempText->SetPos( Point(200, 420) );
    mElements.push_back(tempText);

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
                mStarString = "Enter password:";
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
