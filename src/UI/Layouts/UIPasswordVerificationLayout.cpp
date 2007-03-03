/**
 * File: UIPasswordVerificationLayout.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, February 15 2007 | Initial Creation
 */

#include <util.h>


#include "UIPasswordVerificationLayout.h"                                // class implemented
#include "UIManager.h"
#include "SecurityManager.h"

/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

UIPasswordVerificationLayout::UIPasswordVerificationLayout()
{
    //UIImage *temp = new UIImage("castle.bmp");
    //mElements.push_back(temp);

    // Create default Password
    SecurityManager::GetInstance()->AddUser("user1", "rrrr");

    UIText *tempText = new UIText("Please Enter Password", 40, 255, 0, 0);
    //SDL_Surface *tempSur = tempText->GetElement();
    //printf("width: %d, height:%d\n", tempSur->w, tempSur->h);
    tempText->SetPos( Point(98,50) );
    mElements.push_back(tempText);

    mStarString = "Pwd:";
    mPasswordText = new UIText(mStarString, 30, 255, 0, 0);
    //tempSur = mPasswordText->GetElement();
    //printf("width: %d, height:%d\n", tempSur->w, tempSur->h);
    mPasswordText->SetPos( Point(175,145) );
    mElements.push_back(mPasswordText);

    tempText = new UIText("Press CONFIRM to finish PWD entry", 24, 255, 0, 0);
    //tempSur = tempText->GetElement();
    //printf("width: %d, height:%d\n", tempSur->w, tempSur->h);
    tempText->SetPos( Point(115, 390) );
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
