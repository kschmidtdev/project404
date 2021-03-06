/**
 * File: UIMainMenuLayout.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, February 10 2007 | Initial Creation - stub
 * Andrew Osborne, February 14 2007 | Refined/Finish design, added button/menu functionality
 * Andrew Osborne, February 14 2007 | Made it pretty
 * Karl Schmidt,   February 14 2007 | Moved the image to the upper left corner
 * Andrew Osborne, February 14 2007 | Added "Set Password" operation - finalized implementation
 * Mike Malyuk,    March 4 2007     | Changed method QuitFuntion to QuitFunction
 * Karl Schmidt, March 9 2007	 	| Changed textures to png
 * Mike Malyuk, March 10, 2007      | Changed battleinit init to be compatible with map
 * Karl Schmidt, March 12 2007		| Cleaned up the NewGameFunction because the OverMap does what it was doing now
 * Karl Schmidt, March 15 2007      | Removed commented code, made newgame and loadgame work
 * Karl Schmidt, March 22 2007      | Correcting include orders and paths
 * Karl Schmidt, March 25 2007      | Removed database loading on load game button press since that happens after we've selected a save game
 * Karl Schmidt, March 29 2007      | Calls GameEngine's NewGame on new game
 * Andrew Osborne, March 29 2007    | added new background to menu so that all the options fit.
 */

#include "UIMainMenuLayout.h"                                // class implemented

#include <util.h>

#include <UI/UIMenu.h>
#include <UI/UIManager.h>
#include <UI/UIText.h>
#include <UI/UIImage.h>
#include <UI/FuncObj.h>

#include <Database/DBEngine.h>
#include <GameEngine/GameEngine.h>

class NewGameFunction : public FuncObj
{
    virtual void operator()(void)
    {
        DBEngine::GetInstance()->Initialize( false );
        GameEngine::GetInstance()->NewGame();
        UIManager::GetInstance()->PushLayout("TutorialMenu");
    }
};

class LoadGameFunction : public FuncObj
{
    virtual void operator()(void)
    {
        UIManager::GetInstance()->PushLayout("LoadGame");
    }
};

class SetPasswordFunction : public FuncObj
{
    virtual void operator()(void)
    {
        UIManager::GetInstance()->PushLayout("SetPassword");
    }
};

class OptionsFunction : public FuncObj
{
    virtual void operator()(void)
    {
        UIManager::GetInstance()->PushLayout("Options");
    }
};

class CreditsFunction : public FuncObj
{
    virtual void operator()(void)
    {
        UIManager::GetInstance()->PushLayout("Credits");
    }
};


class MainMenuQuitFunction : public FuncObj
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

    UIImage *tempImg = new UIImage("castle_main.png");
    mElements.push_back(tempImg);

    UIMenu *tempMenu = new UIMenu();

    tempMenu->AddButton("New Game", new NewGameFunction() );
    tempMenu->AddButton("Load Game", new LoadGameFunction()  );
    tempMenu->AddButton("Options", new OptionsFunction() );
    tempMenu->AddButton("Credits", new CreditsFunction() );
    // This option should be moved withing options??
    tempMenu->AddButton("Set Password", new SetPasswordFunction() );
    tempMenu->AddButton("Quit", new MainMenuQuitFunction() );
    tempMenu->SetBackground("menu_back_main.png");

    tempMenu->SetPos( Point(245,225) );
    mDefaultEventListener = tempMenu;
    mElements.push_back(tempMenu);

}// UIMainMenuLayout



UIMainMenuLayout::~UIMainMenuLayout()
{
}// ~UIMainMenuLayout


//============================= OPERATORS ====================================


//============================= OPERATIONS ===================================
//============================= ACCESS     ===================================
//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
