/**
 * File: UISaveGameLayout.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, March 18 2007 | Initial creation
 * Karl Schmidt, March 22 2007   | Correcting include orders and paths
 * Andrew Osborne, March 22 2007 | Added proper UI functionality (Menu with options)
 * Karl Schmidt, March 25 2007   | Added saving the game to a particular slot functionality, loading of games that have been saved as well,
 								   also now able to go back to the previous menu
 * Andrew Osborne, April 5 2007 | Noticed menu said "back to Main Menu" instead of "Back to OverMap"
 */


#include "UISaveGameLayout.h"                                // class implemented

#include <util.h>

#include <UI/UIManager.h>

#include <UI/UIImage.h>
#include <UI/UIMenu.h>
#include <UI/FuncObj.h>
#include <Database/DBEngine.h>

class LayoutSaveGameFunction : public FuncObj
{
public:
    LayoutSaveGameFunction( const int saveFileNum )
    : mSaveFileNum( saveFileNum )
    {
    }

    void operator()(void)
    {
        DBEngine::GetInstance()->SetSaveFileNum( mSaveFileNum );
        DBEngine::GetInstance()->SaveGame();
        UIManager::GetInstance()->PopLayout();
    }


protected:
    int mSaveFileNum;
};

class SaveGameMenuBackFunction : public FuncObj
{
    virtual void operator()(void)
    {
        UIManager::GetInstance()->PopLayout();
    }
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

    const std::vector<std::string> saveFiles = DBEngine::GetInstance()->GetSaveFiles();

    mMenu->ClearButtons();
    for ( unsigned int i = 0; i < saveFiles.size(); ++i )
    {
        mMenu->AddButton( saveFiles[i], new LayoutSaveGameFunction( i+1 ) );
    }

    mMenu->AddBlankRow();
    mMenu->AddButton( "Back to OverMap", new SaveGameMenuBackFunction() );

}
//============================= ACCESS     ===================================
//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
