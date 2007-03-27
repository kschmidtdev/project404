/**
 * File: UIOverMapLayout.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, March 4, 2007 | Initial creation
 * Seung Woo Han, March 14, 2007 | Added feature that loads dialogs from the database.
 * Seung Woo Han, March 15, 2007 | Saving function works now. ( by pressing Save button in the overmap screen )
 * Karl Schmidt, March 15 2007   | Made savegame work, also loading dialog now happens when the screen is shown (db isn't loaded when this object is constructed)
 * Karl Schmidt, March 15 2007   | Quit now goes to main menu, loads city info from db
 * Karl Schmidt, March 22 2007   | Correcting include orders and paths
 * Andrew Osborne, March 25 2007  | Added very small correction
 */
#include "UIOverMapLayout.h"                                // class implemented

#include <util.h>

#include <UI/FuncObj.h>
#include <UI/UIManager.h>
#include <Database/DBEngine.h>

class SaveFunction : public FuncObj
{
    virtual void operator()(void)
    {
        DBEngine::GetInstance()->SaveGame();
        UIOverMapLayout* thisOverMapLayout = dynamic_cast<UIOverMapLayout*>( UIManager::GetInstance()->GetLayout( "OverMap" ) );
        UIScrollText* thisScrollText = thisOverMapLayout->GetUIScrollBox();

        thisScrollText->ClearText(); // Clear previous texts.
        thisScrollText->AddLine( "Your game has been saved successfully." );
        thisScrollText->AddLine( " " );
        thisScrollText->AddLine( " " );
        thisScrollText->AddLine( " " );

        thisScrollText->SetVisible( true ); // Display Scroll Box.

        thisOverMapLayout->SetScrollBoxEnabled( true ); // Remove Scroll Box.

        // After all that.. pop the layout that will later due what this already does (except more)
        UIManager::GetInstance()->PushLayout("SaveGame");

    }
};


class OverMapPartyStatusFunction : public FuncObj
{
    virtual void operator()(void)
    {
        UIManager::GetInstance()->PushLayout("PartyStatus");
    }
};

class ArmoryFunction : public FuncObj
{
    virtual void operator()(void)
    {
        UIManager::GetInstance()->PushLayout("Armory");
    }
};

class MarketFunction : public FuncObj
{
    virtual void operator()(void)
    {
        UIManager::GetInstance()->PushLayout("Market");
    }
};



class QuitFunction : public FuncObj
{
    virtual void operator()(void)
    {
        UIManager::GetInstance()->PopAllLayouts();  // automatically adds titlescreen
        UIManager::GetInstance()->PushLayout("MainMenu");
    }
};

/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

UIOverMapLayout::UIOverMapLayout()
: mOverMap( NULL ), mMenu( NULL ), mScrollBox( NULL ), mScrollBoxEnabled( false )
{
    // Define Name
    mName = "OverMap";

    // Create Overmap
    mOverMap = new UIOverMap();
    mOverMap->SetPos( Point(10,10) );
    mElements.push_back( mOverMap );

    // Create Menu
    mMenu = new UIMenu();
    mMenu->AddButton("Save Game", new SaveFunction() );
    mMenu->AddButton("Party Status", new OverMapPartyStatusFunction() );
    mMenu->AddButton("Market", new MarketFunction() );
    mMenu->AddButton("Armory", new ArmoryFunction() );
    mMenu->AddButton("Quit", new QuitFunction() );
    mMenu->SetPos( Point(460, 140) );
    //mMenu->SetPos( Point(460, 140) );
    mMenu->Disable();
    mElements.push_back( mMenu );

    // Debug
    //mMenu->SetGhost(3, true);

    // Create Scroll Box
    mScrollBox = new UIScrollText();
    mScrollBox->SetPos( Point(10, 350) );

    mScrollBox->SetVisible(true);
    mScrollBoxEnabled = true;
    mElements.push_back( mScrollBox );

    mDefaultEventListener = mOverMap;

    mOverMap->UpdateMap();

}// UIOverMapLayout


UIOverMapLayout::~UIOverMapLayout()
{

}// ~UIOverMapLayout


//============================= OPERATORS ====================================



//============================= OPERATIONS ===================================


void UIOverMapLayout::OnLoad( void )
{

    UILayout::OnLoad();

    mScrollBox->ClearText();
    //Text can go no further than the end of this line============
    DBNode* Dialog001 = DatabaseManager::GetInstance()->Search( "D001" );

    DBString* thisLine = dynamic_cast<DBString*>( Dialog001->GetFirstAttribute() );
    while ( thisLine != NULL )
    {
        mScrollBox->AddLine( thisLine->GetData() );
        thisLine = dynamic_cast<DBString*>( Dialog001->GetNextAttribute() );
    }

    mScrollBox->SetVisible(true);
    mScrollBoxEnabled = true;

    GameEngine::GetInstance()->UpdateCitiesFromDB();

    if (mOverMap)
        mOverMap->UpdateMap();

    mMenu->Disable();

}

void UIOverMapLayout::ProcessEvent( const InputManager::INPUTKEYS evt )
{

    if (mScrollBoxEnabled)
    {
        if (evt==InputManager::CONFIRM)
        {
            if (!mScrollBox->NextPage())
            {
                mDefaultEventListener = mOverMap;
                mScrollBox->SetVisible(false);
                mScrollBoxEnabled = false;
            }
        }
    }

    else if ( (mDefaultEventListener==mOverMap) && (evt==InputManager::MENU) )
    {
        mMenu->Enable();
        mDefaultEventListener = mMenu;
    }
    else if ( (mDefaultEventListener==mMenu) && (evt==InputManager::CANCEL) )
    {
        mMenu->Disable();
        mDefaultEventListener = mOverMap;
    }
    else
    {
        mDefaultEventListener->ProcessEvent(evt);
    }
}

//============================= ACCESS     ===================================
//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
