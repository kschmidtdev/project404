/**
 * File: UILoadGameLayout.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, March 18 2007 | Initial Creation
 * Karl Schmidt, March 22 2007    | Correcting include orders and paths
 * Andrew Osborne, March 23 2007 | Added proper UI functionality (Menu with options)
 */
#include "UILoadGameLayout.h"                                // class implemented

#include <util.h>

#include <UI/UIManager.h>
#include <UI/UIImage.h>
#include <UI/UIMenu.h>
#include <UI/FuncObj.h>

class LoadLayoutLoadGameFunction : public FuncObj
{
public:
    LoadLayoutLoadGameFunction( const std::string & fileName)
    : mFileName(fileName)
    {
    }

    void operator()(void)
    {
        //GameEngine::GetInstance()->LoadGame(mFileName);
        UIManager::GetInstance()->PopLayout();
        UIManager::GetInstance()->PushLayout("OverMap");
    }


protected:
    std::string mFileName;

};



/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

UILoadGameLayout::UILoadGameLayout()
: mMenu( NULL )
{
    // Background Image
    UIImage* back = new UIImage("castle_main.png");
    mElements.push_back(back);

    // Main menu (Save game selection)
    mMenu = new UIMenu();
    mMenu->SetPos( Point(245,255) );
    mElements.push_back(mMenu);
    mDefaultEventListener = mMenu;

    // Title of layout
    mName = "LoadGame";

}// UILoadGameLayout


UILoadGameLayout::~UILoadGameLayout()
{
}// ~UILoadGameLayout


//============================= OPERATORS ====================================

//============================= OPERATIONS ===================================


/*void UILoadGameLayout::ProcessEvent( const InputManager::INPUTKEYS evt )
{
    switch (evt)
    {
        case InputManager::CONFIRM:
            // Need to add code here about loading the game
            UIManager::GetInstance()->PushLayout("OverMap");
            break;
        default:
            break;
    }

}*/

void UILoadGameLayout::OnLoad(void)
{

    UILayout::OnLoad();

    // Grab vector string of save files from GameEngine
    /*
    vector<string>* saveFiles = GameEngine::GetInstance()->GetSaveFiles();

    mMenu->ClearButtons();
    for (vector<string>::iterator iter = saveFiles.begin(); iter != saveFiles.end(); ++iter)
    {
        mMenu->AddButton( (*iter), new LoadGameFunction( (*iter) ) );
    }

    */

    // Temp Debug
    mMenu->ClearButtons();

    mMenu->AddButton( "Save1" , new LoadLayoutLoadGameFunction( "Save1" ) );
    mMenu->AddButton( "Save2" , new LoadLayoutLoadGameFunction( "Save2" ) );
    mMenu->AddButton( "Save3" , new LoadLayoutLoadGameFunction( "Save3" ) );

}


//============================= ACCESS     ===================================
//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
