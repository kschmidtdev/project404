/**
 * File: UIBattleScreenLayout.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Name, Date | Work Done
 */
#include "UIBattleScreenLayout.h"                                // class implemented

#include "UIMenu.h"

/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

UIBattleScreenLayout::UIBattleScreenLayout()
{
    // Add components
    UIElement *temp = new UIMenu();
    temp->setPos( Point(350, 150) );
    elements.push_back( temp );

}// UIBattleScreenLayout

UIBattleScreenLayout::~UIBattleScreenLayout()
{
}// ~UIBattleScreenLayout


//============================= OPERATORS ====================================

/*UIBattleScreenLayout&
UIBattleScreenLayout::operator=(UIBattleScreenLayout&);
{
   return *this;

}// =*/

//============================= OPERATIONS ===================================
//============================= ACCESS     ===================================
//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
