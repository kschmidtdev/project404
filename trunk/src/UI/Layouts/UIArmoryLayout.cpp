/**
 * File: UIArmoryLayout.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, March 18 2007 | Initial Creation
 * Karl Schmidt, March 22 2007    | Correcting include orders and paths
 * Andrew Osborne, March 25 2007 | Implemented proper functionality
 */


#include "UIArmoryLayout.h"                                // class implemented

#include <util.h>

#include <GameEngine/Item.h>

#include <UI/UIManager.h>

#include <UI/UIImage.h>
#include <UI/UIText.h>
#include <UI/UIMenu.h>
#include <UI/FuncObj.h>


class PurchaseItemFunction2 : public FuncObj
{
public:
    PurchaseItemFunction2( Item* i, UIText* t)
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

class PopLayoutFunction4 : public FuncObj
{
    virtual void operator()(void)
    {
        UIManager::GetInstance()->PopLayout();
    }

};


/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

UIArmoryLayout::UIArmoryLayout()
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

    mName = "Armory";
}// UIArmoryLayout


UIArmoryLayout::~UIArmoryLayout()
{
}// ~UIArmoryLayout


//============================= OPERATORS ====================================



//============================= OPERATIONS ===================================

/*void UIArmoryLayout::ProcessEvent( const InputManager::INPUTKEYS evt )
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

void UIArmoryLayout::OnLoad(void)
{

    UILayout::OnLoad();

    // Grab vector string of save files from GameEngine
    /*
    vector<Item*>* armoryItem = GameEngine::GetInstance()->GetCurCity()->GetArmory();

    mMenu->ClearButtons();
    for (vector<Item*>::iterator iter = armoryItem.begin(); iter != armoryItem.end(); ++iter)
    {
        mMenu->AddButton( (*iter)->GetName() , new PurchaseItemFunction( (*iter), mFeedback ) );
    }

    */

    // Temp Debug
    mMenu->ClearButtons();
    Item* tempItem = new Item();

    mMenu->AddButton( "Item1" , new PurchaseItemFunction2( tempItem, mFeedback ) );
    mMenu->AddButton( "Item2" , new PurchaseItemFunction2( tempItem, mFeedback ) );
    mMenu->AddButton( "Item3" , new PurchaseItemFunction2( tempItem, mFeedback ) );

    mMenu->AddButton( "Done", new PopLayoutFunction4() );


}
//============================= ACCESS     ===================================
//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
