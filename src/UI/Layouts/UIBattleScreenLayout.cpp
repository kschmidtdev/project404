/**
 * File: UIBattleScreenLayout.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, February 10 2007 | Initial Creation
 * Andrew Osborne, February 11 2007 | Added Event Listening
 * Andrew Osborne, February 11 2007 | Added functionality to switch between menu/grid
 * Karl Schmidt, February 14 2007 | Updated function capitalization, block style, typedefs
 * Andrew Osborne, February 14 2007 | Added button-function-objects and proper menu declaration
 * Karl Schmidt, February 15 2007 | Removed creating the level in here, added some error checking
 * Mike Malyuk,  February 15 2007 | Added get for grid;
 */

#include "UIBattleScreenLayout.h"                                // class implemented
#include "UIMenu.h"
#include "UIGrid.h"
#include "Logger.h"
#include "GameEngine/Level.h"
#include "UIManager.h"

#include <util.h>


// Defining Function Objects for Button Operations

class QuitFuntion : public FuncObj
{
    virtual void operator()(void)
    {
        UIManager::GetInstance()->SetEndGameState( true );
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

    }
};


/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

UIBattleScreenLayout::UIBattleScreenLayout()
{
    // Add Menu
    // -----------------------------------
    mMenu = new UIMenu();
    mMenu->SetPos( Point(470, 150) );

    mMenu->AddButton("Status", new StatusFunction() );
    mMenu->AddButton("End Turn", new EndTurnFunction() );
    mMenu->AddButton("Quit", new QuitFuntion() );

    mElements.push_back( mMenu );

    //UIElement *tempButton;




    mGrid = new UIGrid();
    mDefaultEventListener = mGrid;
    //mGrid->setParent(this);
    mElements.push_back( mGrid );

    mName = "BattleScreen";

}// UIBattleScreenLayout

UIBattleScreenLayout::~UIBattleScreenLayout()
{
}// ~UIBattleScreenLayout


//============================= OPERATORS ====================================

//============================= OPERATIONS ===================================

void UIBattleScreenLayout::OnLoad( void )
{
    UILayout::OnLoad();

    // doing other initialization

    Level* mLevel = GameEngine::GetInstance()->GetLevel();

    tacAssert( mLevel != NULL );
    if( mLevel == NULL )
    {
        LogError( "Level was not set up before the UI battle screen was loaded\n" );
        return;
    }

    mGrid->SetLevel(mLevel);

    // Put the characters on the screen
    CharacterPtrVec party = mLevel->GetParty();
    CharacterPtrVec enemies = mLevel->GetEnemies();
    CharacterPtrItr piter;
    CharacterPtrItr eiter;

    piter = party.begin();
    eiter = enemies.begin();
    SDL_Surface *tempIcon = ResourceManager::GetInstance()->LoadTexture("charTile.bmp");

    if (tempIcon!=NULL)
    {
        //LogInfo("Character Icon loaded successfully");
        while(piter != party.end() )
        {
            //(*iter)->Move((*piter));
            //mGrid->addCharacter( (*iter)->getTexture(), (*iter)->GetPoint() );
            mGrid->AddPartyCharacter( (*piter) );
            piter++;

        }
        while(eiter != enemies.end() )
        {
            //(*iter)->Move((*piter));
            //mGrid->addCharacter( (*iter)->getTexture(), (*iter)->GetPoint() );
            mGrid->AddEnemyCharacter( (*eiter) );
            eiter++;
        }
    }
    else
    {
        //LogInfo("Character Icon load failed");
    }

    // Load in map textures

    // Load in character textures

}


void UIBattleScreenLayout::ProcessEvent( const InputManager::INPUTKEYS evt )
{
    if ( (mDefaultEventListener==mGrid) && (evt==InputManager::MENU) )
    {
        mDefaultEventListener = mMenu;
    }
    else if ( (mDefaultEventListener==mMenu) && (evt==InputManager::CANCEL) )
    {
        mDefaultEventListener = mGrid;
    }
    else
    {
        mDefaultEventListener->ProcessEvent(evt);
    }

}
//============================= ACCESS     ===================================



/*void UIBattleScreenLayout::switchToMenu(void)
{
    mDefaultEventListener = mMenu;
}


void UIBattleScreenLayout::switchToGrid(void)
{
    mDefaultEventListener = mGrid;
}*/


//============================= INQUIRY    ===================================

/*Level* UIBattleScreenLayout::getLevel(void)
{
    return mLevel;
}*/
UIGrid* UIBattleScreenLayout::GetGrid(void)
{
    return mGrid;
}
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
