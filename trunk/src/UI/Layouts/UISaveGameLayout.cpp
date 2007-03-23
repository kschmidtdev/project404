/**
 * File: UISaveGameLayout.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, March 18 2007 | Initial creation
 * Karl Schmidt, March 22 2007   | Correcting include orders and paths
 * Andrew Osborne, March 22 2007 | Added proper UI functionality (Menu with options)
 */


#include "UISaveGameLayout.h"                                // class implemented

#include <util.h>

#include <UI/UIManager.h>

#include <UI/UIImage.h>
#include <UI/UIMenu.h>
#include <UI/FuncObj.h>

class SaveGameFunction : public FuncObj {

    public:
    SaveGameFunction(string fileName)
    : mFileName(fileName)
    {
    }

    virtual void operator()(void)
    {
        //GameEngine::GetInstance()->SaveGame(mFileName);
        UIManager::GetInstance()->PopLayout();
    }


    protected:
    string mFileName;

};

/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

UISaveGameLayout::UISaveGameLayout()
: mMenu ( NULL )
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
    mName = "SaveGame";

}// UISaveGameLayout


UISaveGameLayout::~UISaveGameLayout()
{
}// ~UISaveGameLayout


//============================= OPERATORS ====================================

//============================= OPERATIONS ===================================

/*void UISaveGameLayout::ProcessEvent( const InputManager::INPUTKEYS evt )
{
    switch (evt)
    {
        case InputManager::CONFIRM:
            // Currently relying on code before this layout was 'pushed' to actually save the game
            UIManager::GetInstance()->PopLayout();
            break;
        default:
            break;
    }

}*/

void UISaveGameLayout::OnLoad(void)
{

    UILayout::OnLoad();

    // Grab vector string of save files from GameEngine
    /*
    vector<string>* saveFiles = GameEngine::GetInstance()->GetSaveFiles();

    mMenu->ClearButtons();
    for (vector<string>::iterator iter = saveFiles.begin(); iter != saveFiles.end(); ++iter)
    {
        mMenu->AddButton( (*iter), new SaveGameFunction( (*iter) ) );
    }

    */

    // Temp Debug
    mMenu->ClearButtons();

    mMenu->AddButton( "Save1" , new SaveGameFunction( "Save1" ) );
    mMenu->AddButton( "Save2" , new SaveGameFunction( "Save2" ) );
    mMenu->AddButton( "Save3" , new SaveGameFunction( "Save3" ) );

}
//============================= ACCESS     ===================================
//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
