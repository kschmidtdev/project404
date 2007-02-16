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
 * Karl Schmidt, February 15 2007 | Added End Turn functionality to side menu
 * Karl Schmidt, February 15 2007 | Added initialize function, destroys everything between displaying (onload/onclose)
 */

#include "UIBattleScreenLayout.h"                                // class implemented
#include "UIMenu.h"
#include "UIGrid.h"
#include "Logger.h"
#include "GameEngine/GameEngine.h"
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
    // Add Menu
    // -----------------------------------
    mMenu = new UIMenu();
    mMenu->SetPos( Point(460, 140) );

    mMenu->AddButton("Status", new StatusFunction() );
    mMenu->AddButton("End Turn", new EndTurnFunction() );
    mMenu->AddButton("Quit", new QuitFuntion() );

    mElements.push_back( mMenu );

    //UIElement *tempButton;

    mGrid = new UIGrid();
    mDefaultEventListener = mGrid;
    //mGrid->setParent(this);
    mElements.push_back( mGrid );
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
