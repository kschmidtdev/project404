/**
 * File: UILoadGameLayout.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, March 18 2007 | Initial Creation
 * Karl Schmidt, March 22 2007   | Correcting include orders and paths
 * Andrew Osborne, March 23 2007 | Added proper UI functionality (Menu with options)
 * Karl Schmidt, March 25 2007   | Added functionality for loading savegames, and also going back to the previous menu
 */
#include "UILoadGameLayout.h"                                // class implemented

#include <util.h>

#include <UI/UIManager.h>
#include <UI/UIImage.h>
#include <UI/UIMenu.h>
#include <UI/FuncObj.h>
#include <Database/DBEngine.h>

class LoadLayoutLoadGameFunction : public FuncObj
{
public:
    LoadLayoutLoadGameFunction( const int saveFileNum )
    : mSaveFileNum( saveFileNum )
    {
    }

    void operator()(void)
    {
        if( DBEngine::GetInstance()->IsValidSaveGame( mSaveFileNum ) )
        {
            DBEngine::GetInstance()->SetSaveFileNum( mSaveFileNum );
            DBEngine::GetInstance()->Initialize( true );
            UIManager::GetInstance()->PopLayout();
            UIManager::GetInstance()->PushLayout("OverMap");
        }
    }


protected:
    int mSaveFileNum;

};

class LoadGameMenuBackFunction : public FuncObj
{
    virtual void operator()(void)
    {
        UIManager::GetInstance()->PopLayout();
    }
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

void UILoadGameLayout::OnLoad(void)
{

    UILayout::OnLoad();

    // Grab vector string of save files from GameEngine

    const std::vector<std::string> saveFiles = DBEngine::GetInstance()->GetSaveFiles();

    mMenu->ClearButtons();
    for ( unsigned int i = 0; i < saveFiles.size(); ++i )
    {
        mMenu->AddButton( saveFiles[i], new LoadLayoutLoadGameFunction( i+1 ) );
    }

    mMenu->AddBlankRow();
    mMenu->AddButton( "Back to Main Menu", new LoadGameMenuBackFunction() );
}


//============================= ACCESS     ===================================
//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
