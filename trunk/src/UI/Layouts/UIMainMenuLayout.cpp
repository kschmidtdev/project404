/**
 * File: UIMainMenuLayout.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, February 10 2007 | Initial Creation - stub
 * Andrew Osborne, February 14 2007 | Refined/Finish design, added button/menu functionality
 */
#include "UIMainMenuLayout.h"                                // class implemented
#include "UIMenu.h"
#include "UIManager.h"


class NewGameFunction : public FuncObj
{
    virtual void operator()(void)
    {
        UIManager::GetInstance()->PushLayout("BattleScreen");
    }
};

class SetPasswordFunction : public FuncObj
{
    virtual void operator()(void)
    {
        //UIManager::GetInstance()->PushLayout("SetPasswordScreen");
    }
};

class QuitFuntion : public FuncObj
{
    virtual void operator()(void)
    {
        UIManager::GetInstance()->SetEndGameState( true );
    }
};



/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

UIMainMenuLayout::UIMainMenuLayout()
{
    mName = "MainMenu";

    UIMenu *temp = new UIMenu();

    temp->AddButton("New Game", new NewGameFunction() );
    temp->AddButton("Set Password", new SetPasswordFunction() );
    temp->AddButton("Quit", new QuitFuntion() );

    temp->SetPos( Point(150,150) );
    mDefaultEventListener = temp;
    mElements.push_back(temp);

}// UIMainMenuLayout



UIMainMenuLayout::~UIMainMenuLayout()
{
    //mElements[0]->deleteFunctions();
}// ~UIMainMenuLayout


//============================= OPERATORS ====================================


//============================= OPERATIONS ===================================
//============================= ACCESS     ===================================
//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
