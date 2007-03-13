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
    mMenu->AddButton("Quit", new QuitFunction() );
    mMenu->SetPos( Point(460, 140) );
    mMenu->SetPos( Point(460, 140) );
    mElements.push_back( mMenu );

    // Create Scroll Box
    mScrollBox = new UIScrollText();
    mScrollBox->SetVisible( false );
    mScrollBox->SetPos( Point(10, 350) );

    // Debug
    mScrollBox->AddLine("Line of Text 1");
    mScrollBox->AddLine("Line of Text 2");
    mScrollBox->AddLine("Line of Text 3");
    mScrollBox->AddLine("Line of Text 4");
    mScrollBox->AddLine("Line of Text 5");
    mScrollBox->SetVisible(true);
    mScrollBoxEnabled = true;

    mElements.push_back( mScrollBox );


    // *** Don't forget to fix SetPos on Scroll Text


    mDefaultEventListener = mOverMap;

}// UIOverMapLayout


UIOverMapLayout::~UIOverMapLayout()
{

}// ~UIOverMapLayout


//============================= OPERATORS ====================================



//============================= OPERATIONS ===================================


void UIOverMapLayout::OnLoad( void )
{

    UILayout::OnLoad();

    if (mOverMap)
        mOverMap->UpdateMap();

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
        mDefaultEventListener = mMenu;
    }
    else if ( (mDefaultEventListener==mMenu) && (evt==InputManager::CANCEL) )
    {
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
