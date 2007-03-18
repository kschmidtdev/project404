/**
 * File: UIBattleScreenLayout.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, February 10 2007 | Initial Creation
 * Andrew Osborne, February 11 2007 | Added Event Listening
 * Andrew Osborne, February 11 2007 | Added functionality to switch between menu/grid
 * Karl Schmidt,   February 14 2007 | Updated function capitalization, block style, typedefs
 * Andrew Osborne, February 14 2007 | Added button-function-objects and proper menu declaration
 * Karl Schmidt,   February 15 2007 | Removed creating the level in here, added some error checking
 * Mike Malyuk,    February 15 2007 | Added get for grid;
 * Karl Schmidt,   February 15 2007 | Added End Turn functionality to side menu
 * Karl Schmidt,   February 15 2007 | Added initialize function, destroys everything between displaying (onload/onclose)
 * Karl Schmidt,   February 15 2007 | Added change focus to grid when you press end turn
 * Mike Malyuk,    March 4 2007     | Changed method QuitFuntion to QuitFunction
 * Karl Schmidt,   March 9 2007	 	| Changed textures to png
 * Andrew Osborne, March 12 2007    | Added Chuck-Norris and "Easy Win" option to Battle Layout for debug purposes
 * Karl Schmidt,   March 12 2007 	| Made the QuitFunction quit to the Main Menu, also made the Easy win function
 *  								  act correctly and not leak memory
 * Mike Malyuk,    March 14 2007    | Added intializers for Grid
 * Karl Schmidt,   March 14 2007	| Disabled "Easy Win" button in release mode
 */


#include <util.h>

#include "UIBattleScreenLayout.h"                                // class implemented
#include "UIMenu.h"
#include "UIGrid.h"
#include "Logger.h"
#include "GameEngine/GameEngine.h"
#include "UIManager.h"
#include "UICharWindow.h"
#include "GameEngine/Knight.h"

// Defining Function Objects for Button Operations

class BattleScreenQuitFunction : public FuncObj
{
    virtual void operator()(void)
    {
        UIManager::GetInstance()->PopAllLayouts();  // automatically adds titlescreen
        UIManager::GetInstance()->PushLayout("MainMenu");

        GameEngine::GetInstance()->BattleOver();
    }
};


class StatusFunction : public FuncObj
{
    virtual void operator()(void)
    {
        // To be implemented later
    }
};


class EndTurnFunction : public FuncObj
{
    virtual void operator()(void)
    {
        Level * curLevel = GameEngine::GetInstance()->GetLevel();
        if( curLevel )
        {
            vector<Character*> party = curLevel->GetParty();
            for_each( party.begin(), party.end(), mem_fun( &Character::Exhaust ) );
            curLevel->SetState(Level::AIFREE);

            // Repeated code, should be put into one function someday
            vector<Character*> revigorate = curLevel->GetParty();
            UIGrid* grid = UIManager::GetInstance()->GetLayout("BattleScreen")->GetGrid();
            if( grid )
            {
                for(vector<Character*>::iterator citer = revigorate.begin(); citer != revigorate.end(); ++citer)
                {
                    grid->RemoveCharacter((*citer)->GetPoint());
                    grid->AddPartyCharacter((*citer));
                }
            }
            curLevel->AllExhaustedParty();
        }
        // Hack to switch back to the grid for input focus after ending the current turn
        UIManager::GetInstance()->GetLayout("BattleScreen")->ProcessEvent( InputManager::CANCEL );
    }
};


class EasyWinFunction : public FuncObj
{
    virtual void operator()(void)
    {
        Level* mLevel = GameEngine::GetInstance()->GetLevel();

        if (mLevel)
        {
            // Chuck Norris don't need no armour....  or weapons....
            Character* ChuckNorris = new Knight("ChuckNorris", 0, NULL, NULL);
            for (int i=0; i<30; i++)
                ChuckNorris->LevelUp();

            vector<Character*> enemies = mLevel->GetEnemies();
            vector<Character*>::iterator iter;

            for (iter = enemies.begin(); iter!=enemies.end(); ++iter)
            {
                cout << "The chief export of Chuck Norris is pain.";
                ChuckNorris->Attack((*iter));
            }

            if (mLevel->GetWinCondition())
            {
                UIManager::GetInstance()->PushLayout("Win");
            }

            delete ChuckNorris;
        }

    }
};




/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

UIBattleScreenLayout::UIBattleScreenLayout()
{
    Initialize();
    mName = "BattleScreen";

}// UIBattleScreenLayout

UIBattleScreenLayout::~UIBattleScreenLayout()
{
}// ~UIBattleScreenLayout

void UIBattleScreenLayout::Initialize()
{


    // Add Grid
    // --------------------------------
    mGrid = new UIGrid();
    mGrid->Initialize();
    mDefaultEventListener = mGrid;
    mElements.push_back( mGrid );



    // Add Character Window
    // -----------------------------------
    UICharWindow *charWindow = new UICharWindow();
    charWindow->SetPos( Point(420, 10) );
    mElements.push_back( charWindow );
    mGrid->SetCharWindow( charWindow );


    // Add Menu
    // -----------------------------------
    mMenu = new UIMenu();
    mMenu->SetPos( Point(450, 180) );
    mMenu->AddButton("End Turn", new EndTurnFunction() );
    mMenu->AddButton("Quit", new BattleScreenQuitFunction() );

    #ifdef _DEBUG
    mMenu->AddButton("Easy Win", new EasyWinFunction() );
    #endif

    mMenu->Disable();

    mElements.push_back( mMenu );



}

//============================= OPERATORS ====================================

//============================= OPERATIONS ===================================

void UIBattleScreenLayout::OnLoad( void )
{
    UILayout::OnLoad();

    if( mElements.empty() )
    {
        Initialize();
    }

    // doing other initialization

    Level* mLevel = GameEngine::GetInstance()->GetLevel();

    tacAssert( mLevel != NULL );
    if( mLevel == NULL )
    {
        LogError( "Level was not set up before the UI battle screen was loaded\n" );
        return;
    }

    mGrid->SetLevel(mLevel);
    mGrid->Initialize();
    // Put the characters on the screen
    CharacterPtrVec party = mLevel->GetParty();
    CharacterPtrVec enemies = mLevel->GetEnemies();
    CharacterPtrItr piter;
    CharacterPtrItr eiter;

    piter = party.begin();
    eiter = enemies.begin();
    SDL_Surface *tempIcon = ResourceManager::GetInstance()->LoadTexture("charTile.png");

    if (tempIcon!=NULL)
    {
        while(piter != party.end() )
        {
            mGrid->AddPartyCharacter( (*piter) );
            piter++;

        }
        while(eiter != enemies.end() )
        {
            mGrid->AddEnemyCharacter( (*eiter) );
            eiter++;
        }
    }
    else
    {
    }

    // Load in map textures

    // Load in character textures

    // UpdateCursor
    mGrid->UpdateCursor();

    // Make Menu disabled
    mMenu->Disable();

}

void UIBattleScreenLayout::OnClose(void)
{
    UILayout::OnClose();

    for( UIElementPtrItr i = mElements.begin(); i != mElements.end(); ++i )
    {
        if( *i )
        {
            delete *i;
        }
    }
    mElements.clear();

    // Other parts of the code need access to some sort of working UIGrid...
    Initialize();
}


void UIBattleScreenLayout::ProcessEvent( const InputManager::INPUTKEYS evt )
{
    if ( (mDefaultEventListener==mGrid) && (evt==InputManager::MENU) )
    {
        mMenu->Enable();
        mDefaultEventListener = mMenu;
    }
    else if ( (mDefaultEventListener==mMenu) && (evt==InputManager::CANCEL) )
    {
        mMenu->Disable();
        mDefaultEventListener = mGrid;
    }
    else
    {
        mDefaultEventListener->ProcessEvent(evt);
    }
}
//============================= ACCESS     ===================================


//============================= INQUIRY    ===================================

UIGrid* UIBattleScreenLayout::GetGrid(void)
{
    return mGrid;
}
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
