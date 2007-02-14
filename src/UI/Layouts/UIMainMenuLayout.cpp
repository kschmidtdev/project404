/**
 * File: UIMainMenuLayout.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Name, Date | Work Done
 */
#include "UIMainMenuLayout.h"                                // class implemented
#include "UIMenu.h"


/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

UIMainMenuLayout::UIMainMenuLayout()
{
    mName = "MainMenu";

    UIMenu *temp = new UIMenu();
    temp->SetPos( Point(100,100) );
    mDefaultEventListener = temp;
    mElements.push_back(temp);

}// UIMainMenuLayout



UIMainMenuLayout::~UIMainMenuLayout()
{
}// ~UIMainMenuLayout


//============================= OPERATORS ====================================


//============================= OPERATIONS ===================================
//============================= ACCESS     ===================================
//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
