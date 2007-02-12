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

/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

UIBattleScreenLayout::UIBattleScreenLayout()
{
    // Add components
    mMenu = new UIMenu();
    mMenu->setPos( Point(470, 150) );
    elements.push_back( mMenu );

    mGrid = new UIGrid();
    defaultEventListener = mGrid;
    elements.push_back( mGrid );



}// UIBattleScreenLayout

UIBattleScreenLayout::~UIBattleScreenLayout()
{
}// ~UIBattleScreenLayout


//============================= OPERATORS ====================================

//============================= OPERATIONS ===================================




//============================= ACCESS     ===================================



void UIBattleScreenLayout::switchToMenu(void)
{
    defaultEventListener = mMenu;
}


void UIBattleScreenLayout::switchToGrid(void)
{
    defaultEventListener = mGrid;
}


//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
