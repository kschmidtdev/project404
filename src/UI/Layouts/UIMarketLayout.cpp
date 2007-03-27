/**
 * File: UIMarketLayout.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, March 18 2007 | Initial Creation
 * Karl Schmidt, March 22 2007   | Correcting include orders and paths
 * Andrew Osborne, March 25 2007 | Implemented proper functionality
 * Karl Schmidt, March 27 2007   | Fixed memory leaks, labelled temporary code accordingly
 */
#include "UIMarketLayout.h"                                // class implemented

#include <util.h>

#include <GameEngine/Item.h>

#include <UI/UIManager.h>

#include <UI/UIImage.h>
#include <UI/UIText.h>
#include <UI/UIMenu.h>
#include <UI/FuncObj.h>

// This is temporary, needs to be removed once real item fetching from somewhere is completed
namespace
{
    static Item* tempItem = NULL;
}

/*

There needs to be
*/
class PurchaseItemFunction : public FuncObj
{
public:
    PurchaseItemFunction( Item* i, UIText* t)
    : mItem(i), mText(t)
    {
    }

    void operator()(void)
    {

        /*bool success = GameEngine::GetInstance()->AttemptToPurchaseItem(mItem);
        if (success)
        {
            mText->ChangeText( mItem->GetName() + " purchased successfully");
        }
        else
        {
            mText->ChangeText("Not enough money to purchase this item");
        }*/

        mText->ChangeText("It sorta works");
    }


protected:
    Item* mItem;
    UIText* mText;

};

class PopLayoutFunction3 : public FuncObj
{
    virtual void operator()(void)
    {
        UIManager::GetInstance()->PopLayout();
    }

};




/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

UIMarketLayout::UIMarketLayout()
: mMenu( NULL ), mFeedback( NULL )
{
    UIImage* back = new UIImage("castle_main.png");
    mElements.push_back(back);

    // Create feedback text
    mFeedback = new UIText(" ", 24, 255, 255, 0);
    mFeedback->SetPos( Point( 30, 400) );
    mElements.push_back(mFeedback);

    // Create main menu
    mMenu = new UIMenu();
    mMenu->SetBackground("menu_back_large.png");
    mMenu->SetSpacing(5);
    mMenu->SetPos( Point(450, 40) );
    mElements.push_back(mMenu);
    mDefaultEventListener = mMenu;


    mName = "Market";
}// UIMarketLayout


UIMarketLayout::~UIMarketLayout()
{
    // This is temporary, needs to be removed once real item fetching from somewhere is completed
    if( tempItem )
    {
        delete tempItem;
        tempItem = NULL;
    }
}// ~UIMarketLayout


//============================= OPERATORS ====================================


//============================= OPERATIONS ===================================

/*void UIMarketLayout::ProcessEvent( const InputManager::INPUTKEYS evt )
{
    switch (evt)
    {
        case InputManager::CONFIRM:
            // Need to add code here about loading the game
            UIManager::GetInstance()->PopLayout();
            break;
        default:
            break;
    }
}*/


void UIMarketLayout::OnLoad(void)
{

    UILayout::OnLoad();

    // Grab vector string of save files from GameEngine
    /*
    vector<Item*>* marketItem = GameEngine::GetInstance()->GetCurCity()->GetMarket();

    mMenu->ClearButtons();
    for (vector<Item*>::iterator iter = marketItem.begin(); iter != marketItem.end(); ++iter)
    {
        mMenu->AddButton( (*iter)->GetName() , new PurchaseItemFunction( (*iter), mFeedback ) );
    }

    */

    // Temp Debug
    mMenu->ClearButtons();

    // This is temporary, needs to be removed once real item fetching from somewhere is completed
    if( tempItem == NULL )
    {
        tempItem = new Item();
    }

    mMenu->AddButton( "Item1" , new PurchaseItemFunction( tempItem, mFeedback ) );
    mMenu->AddButton( "Item2" , new PurchaseItemFunction( tempItem, mFeedback ) );
    mMenu->AddButton( "Item3" , new PurchaseItemFunction( tempItem, mFeedback ) );

    mMenu->AddButton( "Done", new PopLayoutFunction3() );


}
//============================= ACCESS     ===================================
//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
