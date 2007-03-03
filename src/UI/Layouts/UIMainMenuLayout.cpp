/**
 * File: UIMainMenuLayout.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, February 10 2007 | Initial Creation - stub
 * Andrew Osborne, February 14 2007 | Refined/Finish design, added button/menu functionality
 * Andrew Osborne, February 14 2007 | Made it pretty
 * Karl Schmidt, February 14 2007 | Moved the image to the upper left corner
 * Andrew Osborne, February 14 2007 | Added "Set Password" operation - finalized implementation
 */

#include <util.h>


#include "UIMainMenuLayout.h"                                // class implemented
#include "UIMenu.h"
#include "UIManager.h"
#include "UIText.h"
#include "UIImage.h"

#include <GameEngine/GameEngine.h>


class NewGameFunction : public FuncObj
{
    virtual void operator()(void)
    {
        // Temporarily hardcoding this initialization (until the UI has the overmap that does this)
        vector<Character*> partyTemp;
        GameEngine::GetInstance()->BattleInit( partyTemp, GameEngine::CITYA, UIManager::GetInstance()->GetLayout("BattleScreen")->GetGrid()->MaxXY() );

        UIManager::GetInstance()->PushLayout("BattleScreen");
    }
};

class SetPasswordFunction : public FuncObj
{
    virtual void operator()(void)
    {
        UIManager::GetInstance()->PushLayout("SetPassword");
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

    UIImage *tempImg = new UIImage("castle_main.bmp");
    mElements.push_back(tempImg);

    //UIText *tempText = new UIText("SymTac", 100, 255, 0, 0);
    //tempText->SetPos( Point(120,50) );
    //mElements.push_back(tempText);


    UIMenu *tempMenu = new UIMenu();

    tempMenu->AddButton("New Game", new NewGameFunction() );
    tempMenu->AddButton("Set Password", new SetPasswordFunction() );
    tempMenu->AddButton("Quit", new QuitFuntion() );

    tempMenu->SetPos( Point(245,255) );
    mDefaultEventListener = tempMenu;
    mElements.push_back(tempMenu);

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
