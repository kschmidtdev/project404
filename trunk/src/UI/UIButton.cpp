/**
 * File: UIButton.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Name, Date | Work Done
 */
#include "UIButton.h"                                // class implemented


/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

UIButton::UIButton()
{
}// UIButton

// constructor that will
UIButton::UIButton(const string ButtonMessage )
:elementImage( ResourceManager::GetInstance()->LoadTexture("testButton") )
{
    // Code to put text on screen
}

UIButton::~UIButton()
{
}// ~UIButton


//============================= OPERATORS ====================================


//============================= OPERATIONS ===================================


//============================= ACCESS     ===================================

//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
