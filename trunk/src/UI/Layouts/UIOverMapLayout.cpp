/**
 * File: UIOverMapLayout.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, March 4, 2007 | Initial creation
 */
#include "UIOverMapLayout.h"                                // class implemented
#include "FuncObj.h"
#include "UIManager.h"

class SaveFunction : public FuncObj
{
    virtual void operator()(void)
    {
        //UIManager::GetInstance()->SetEndGameState( true );
        //GameEngine::GetInstance()->SaveGame();
    }

};

class QuitFunction : public FuncObj
{
    virtual void operator()(void)
    {
        UIManager::GetInstance()->SetEndGameState( true );
    }
};

/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

UIOverMapLayout::UIOverMapLayout()
: mOverMap( NULL ), mMenu( NULL )
{

    mName = "OverMap";

    mOverMap = new UIOverMap();
    mOverMap->SetPos( Point(10,10) );
    mElements.push_back( mOverMap );

    mMenu = new UIMenu();
    mMenu->AddButton("Save Game", new SaveFunction() );
    mMenu->AddButton("Quit", new QuitFunction() );
    mMenu->SetPos( Point(460, 140) );
    mMenu->SetPos( Point(460, 140) );
    mElements.push_back( mMenu );

    mDefaultEventListener = mOverMap;

}// UIOverMapLayout


UIOverMapLayout::~UIOverMapLayout()
{

}// ~UIOverMapLayout


//============================= OPERATORS ====================================



//============================= OPERATIONS ===================================
//============================= ACCESS     ===================================
//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
