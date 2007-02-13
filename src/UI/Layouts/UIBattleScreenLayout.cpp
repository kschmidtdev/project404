/**
 * File: UIBattleScreenLayout.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, February 10 2007 | Initial Creation
 * Andrew Osborne, February 11 2007 | Added Event Listening
 * Andrew Osborne, February 11 2007 | Added functionality to switch between menu/grid
 */

#include "UIBattleScreenLayout.h"                                // class implemented
#include "UIMenu.h"
#include "UIGrid.h"
#include "Logger.h"
#include "GameEngine/Level.h"

/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

UIBattleScreenLayout::UIBattleScreenLayout()
{
    // Add components
    mMenu = new UIMenu();
    mMenu->setPos( Point(470, 150) );
    mElements.push_back( mMenu );

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

void UIBattleScreenLayout::onLoad( void )
{
    UILayout::onLoad();

    // doing other initialization

    //mLevel = GameEngine::GetInstance()->battleInitializer();
    mLevel = new Level();

    // Put the characters on the screen
    vector<Character*> everyoneList = mLevel->GetEveryone();
    vector<Character*>::iterator iter;

    iter = everyoneList.begin();

    SDL_Surface *tempIcon = ResourceManager::GetInstance()->LoadTexture("charTile.bmp");

    if (tempIcon!=NULL) {

        //LogInfo("Character Icon loaded successfully");
        while(iter != everyoneList.end() )
        {
            //(*iter)->Move((*piter));
            //mGrid->addCharacter( (*iter)->getTexture(), (*iter)->GetPoint() );
            mGrid->addCharacter( (*iter) );
            iter++;

        }
    } else {
        //LogInfo("Character Icon load failed");
    }

    // Load in map textures

    // Load in character textures

}



//============================= ACCESS     ===================================



void UIBattleScreenLayout::switchToMenu(void)
{
    mDefaultEventListener = mMenu;
}


void UIBattleScreenLayout::switchToGrid(void)
{
    mDefaultEventListener = mGrid;
}


//============================= INQUIRY    ===================================

Level* UIBattleScreenLayout::getLevel(void)
{
    return mLevel;
}
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
