/**
 * File: UISetPasswordLayout.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, February 15 2007 | Initial Creation
 */
#include "UISetPasswordLayout.h"                                // class implemented
#include "UIManager.h"
#include "SecurityManager.h"

/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================


    int mPasswordEntryState;
    string mOldStarString;
    string mNewStarString;
    string mConfirmStarString;
    UIText *mOldPwdUIText;
    UIText *mNewPwdUIText;
    UIText *mConfirmPwdUIText;
    string mOldPwd;
    string mNewPwd;
    string mConfirmPwd;

UISetPasswordLayout::UISetPasswordLayout()
: mPasswordEntryState( 0 ), mOldStarString ("Old Pwd:"), mNewStarString ( "New Pwd:"), mConfirmStarString( "Confirm Pwd:"),
mOldPwdUIText(NULL), mNewPwdUIText(NULL), mConfirmPwdUIText(NULL), mOldPwd(""), mNewPwd(""), mConfirmPwd("")
{
    mName = "SetPassword";

    // Assume only one user - needs to be changed for V2
    //string user = "user1";

    // Old Password
    mOldPwdUIText = new UIText(mOldStarString, 30, 255, 0, 0);
    mOldPwdUIText->SetPos( Point(175, 145) );
    mElements.push_back(mOldPwdUIText);

    // New Password
    mNewPwdUIText = new UIText(mNewStarString, 30, 255, 0, 0);
    mNewPwdUIText->SetPos( Point(175, 185) );
    mNewPwdUIText->SetVisible(false);
    mElements.push_back(mNewPwdUIText);

    // Confirm Password
    mConfirmPwdUIText = new UIText(mConfirmStarString, 30, 255, 0, 0);
    mConfirmPwdUIText->SetPos( Point(175, 225) );
    mConfirmPwdUIText->SetVisible(false);
    mElements.push_back(mConfirmPwdUIText);

    UIText *tempText = new UIText("Set Password", 40, 255, 0, 0);
    //SDL_Surface *tempSur = tempText->GetElement();
    //printf("set title: width: %d, height:%d\n", tempSur->w, tempSur->h);
    tempText->SetPos( Point(98,50) );
    mElements.push_back(tempText);

    tempText = new UIText("Press CONFIRM to advance", 24, 255, 0, 0);
    //tempSur = tempText->GetElement();
    //printf("confirm: width: %d, height:%d\n", tempSur->w, tempSur->h);
    tempText->SetPos( Point(115, 390) );
    mElements.push_back(tempText);



}// UISetPasswordLayout


UISetPasswordLayout::~UISetPasswordLayout()
{
}// ~UISetPasswordLayout


//============================= OPERATORS ====================================


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
                    if (SecurityManager::GetInstance()->VerifyPassword("user1", mOldPwd))
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
                    if (mConfirmPwd==mNewPwd)
                    {
                        SecurityManager::GetInstance()->DeleteUser("user1");
                        SecurityManager::GetInstance()->AddUser("user1", mConfirmPwd);
                        UIManager::GetInstance()->PopLayout();
                    }
                    //else
                    //{
                    mOldPwd = "";
                    mOldStarString = "Old Pwd:";
                    mOldPwdUIText->ChangeText(mOldStarString);
                    mNewPwd = "";
                    mNewStarString = "New Pwd:";
                    mNewPwdUIText->SetVisible(false);
                    mNewPwdUIText->ChangeText(mNewStarString);
                    mConfirmPwd = "";
                    mConfirmStarString = "Confirm Pwd:";
                    mConfirmPwdUIText->SetVisible(false);
                    mConfirmPwdUIText->ChangeText(mConfirmStarString);
                    mPasswordEntryState = 0;
                    //}
                    break;
            }
            break;
        case InputManager::CANCEL:
            mOldPwd = "";
            mOldStarString = "Old Pwd:";
            mOldPwdUIText->ChangeText(mOldStarString);
            mNewPwd = "";
            mNewStarString = "New Pwd:";
            mNewPwdUIText->SetVisible(false);
            mNewPwdUIText->ChangeText(mNewStarString);
            mConfirmPwd = "";
            mConfirmStarString = "Confirm Pwd:";
            mConfirmPwdUIText->SetVisible(false);
            mConfirmPwdUIText->ChangeText(mConfirmStarString);
            mPasswordEntryState = 0;
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
