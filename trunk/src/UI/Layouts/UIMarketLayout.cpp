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
 * Andrew Osborne, March 29 2007 | Finish Implementation:  Added call to city to create dynamic list of armor items
 *                                   Implemented ItemWindow, added purchasing functionality, commented out debug code
 * Karl Schmidt, March 29 2007   | Added cash text update on layout load (so you see updates after winning a battle)
 */
#include "UIMarketLayout.h"                                // class implemented

#include <util.h>

#include <GameEngine/Item.h>

#include <UI/UIManager.h>
#include <GameEngine/GameEngine.h>
#include <Database/DBEngine.h>

#include <UI/UIImage.h>
#include <UI/UIText.h>
#include <UI/UIMenu.h>
#include <UI/UIItemWindow.h>
#include <UI/FuncObj.h>

// This is temporary, needs to be removed once real item fetching from somewhere is completed
/*namespace
{
    static Item* tempItem = NULL;
}*/


// Function for "purchasing" the item - adding it to the party's inventory
// =========================================
class PurchaseItemFunction : public FuncObj
{
public:
    PurchaseItemFunction( Item* i, UIText* feedback, UIText* moneyText)
    : mItem(i), mText(feedback), mMoneyText(moneyText)
    {
    }

    void operator()(void)
    {

        // Create check to see if there is sufficient funds
        GameEngine *ge = GameEngine::GetInstance();
        int money = ge->GetCash();
        int cost = mItem->GetCost();


        if (money>=cost)
        {

            // There is sufficient cash
            money -= cost;
            ge->SetCash(money);
            vector<Item*>* itemList = GameEngine::GetInstance()->GetItems();
            itemList->push_back(mItem);

            std::ostringstream oss;
            oss << money;
            mMoneyText->ChangeText(oss.str());
            mText->ChangeText(mItem->GetName() + " purchased successfully");

        }
        else
        {
            mText->ChangeText("Not enough money to purchase this item");
        }

    }


protected:
    Item* mItem;
    UIText* mText;
    UIText* mMoneyText;

};

// Pops layout - goes to previous screen (OverMap)
class PopLayoutFunction3 : public FuncObj
{
    virtual void operator()(void)
    {
        UIManager::GetInstance()->PopLayout();
    }

};


// Function that is called as you move on the menu...
// Updates the Item Window.
//=======================================
class MarketMenuCursorFunction : public FuncObj
{

public:
    MarketMenuCursorFunction(UIMenu* menu, vector<Item*>* itemList, UIItemWindow* window)
    : mMenu( menu ), mItemList( itemList ), mWindow( window )
    {
    }

    virtual void operator()(void)
    {

        unsigned int index = mMenu->GetCursorPos();
        if (index<mItemList->size())
        {

            Item* tempItem = (*mItemList)[index];
            mWindow->SetItem(tempItem);

        }
        else
        {
            mWindow->ClearItem();
        }

    }

protected:
    UIMenu* mMenu;
    vector<Item*>* mItemList;
    UIItemWindow* mWindow;
};


/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

UIMarketLayout::UIMarketLayout()
: mMenu( NULL ), mFeedback( NULL ), mMoney( NULL ), mItemWindow( NULL )
{
    UIImage* back = new UIImage("castle_main.png");
    mElements.push_back(back);

    // Font parameters
    int fontSize = 24;
    int fontRed = 255;
    int fontGreen = 255;
    int fontBlue = 0;
    Point feedbackPoint( 30, 400);
    Point textOffset( 0, -(fontSize + 8) );
    Point partyMoneyPoint = feedbackPoint + textOffset;
    Point itemCostPoint = partyMoneyPoint + textOffset;
    Point numberOffset( 200, 0 );

    // Create feedback text
    mFeedback = new UIText(" ", fontSize, fontRed, fontGreen, fontBlue);
    mFeedback->SetPos( feedbackPoint );
    mElements.push_back(mFeedback);

    // Add:  "Party's Funds, $:"
    UIText* partyMoneyDesc = new UIText("Party's Funds, $: ", fontSize, fontRed, fontGreen, fontBlue);
    partyMoneyDesc->SetPos( partyMoneyPoint );
    mElements.push_back(partyMoneyDesc);

    // Add:  $ amount
    int money = GameEngine::GetInstance()->GetCash();
    std::ostringstream oss;
    oss << money;
    mMoney = new UIText(oss.str(), fontSize, fontRed, fontGreen, fontBlue);
    mMoney->SetPos( partyMoneyPoint + numberOffset );
    mElements.push_back(mMoney);

    // Create main menu
    mMenu = new UIMenu();
    mMenu->SetBackground("menu_back_large.png");
    mMenu->SetSpacing(5);
    mMenu->SetPos( Point(450, 40) );
    //mMenu->SetCursorFunc( new MarketMenuCursorFunction(
    mElements.push_back(mMenu);
    mDefaultEventListener = mMenu;

    // Creates Item Window
    mItemWindow = new UIItemWindow();
    mItemWindow->SetDisplayCost(true);
    mItemWindow->SetPos( Point( 30, 30) );
    mElements.push_back(mItemWindow);

    mName = "Market";

}// UIMarketLayout


UIMarketLayout::~UIMarketLayout()
{
}// ~UIMarketLayout


//============================= OPERATORS ====================================


//============================= OPERATIONS ===================================



void UIMarketLayout::OnLoad(void)
{

    UILayout::OnLoad();

    // Setup List of possible items menu
    // ======================================

    // Grab vector of item pointers for market
    vector<Item*>* mMarketItem = GameEngine::GetInstance()->GetCurCity()->GetMarket();

    // Clear buttons,
    // then add each button, which represents an item to purchase
    mMenu->ClearButtons();
    for (vector<Item*>::iterator iter = mMarketItem->begin(); iter != mMarketItem->end(); ++iter)
    {
        mMenu->AddButton( (*iter)->GetName() , new PurchaseItemFunction( (*iter), mFeedback, mMoney ) );
    }

    // Add Done Button - go back to previous screen
    mMenu->AddButton( "Done", new PopLayoutFunction3() );

    // Adding Cursor Function - to allow the mItemWindow to be updated
    mMenu->SetCursorFunc( new MarketMenuCursorFunction( mMenu, mMarketItem, mItemWindow) );


    // Initializing 'ItemWindow' (with first value in list)
    if (!mMarketItem->empty())
    {
        Item* tempItem = (*mMarketItem)[0];
        mItemWindow->SetItem(tempItem);
    }

    mMoney->ChangeText( toString( GameEngine::GetInstance()->GetCash() ) );
}
//============================= ACCESS     ===================================
//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
