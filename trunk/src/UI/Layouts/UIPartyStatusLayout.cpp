/**
 * File: UIPartyStatusLayout.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, March 18 2007 | Initial Creation (Empty)
 * Karl Schmidt, March 22 2007    | Correcting include orders and paths
 * Andrew Osborne, March 25 2007 | Implemented proper UI functionality
 * Karl Schmidt, March 27 2007   | Fixed memory leak (mPartyWindow never deletes what is in it)
 * Andrew Osborne, March 29 2007 | Removed "Select Party" button, corrected "Equip Weapon" button so it actually moves you to the
 *                                  weapon selection menu, however, commented out both "Equip Weapon" and "Equip Armor" because
 *                                  at present time they are not fully implemented.
 *                                  Properly installed character windows.  Created (and properly deleted) mPartyList variable.
 *                                  Properly create weapon and armor lists from pary inventory.  Overwrote OnClose method.
 * Andrew Osborne, March 29 2007 | Enabled Equiping of Armor and Weapons (also fixed memory leak)
 * Andrew Osborne, April 1 2007 | Made it so then equip functions are ghosted when you are in battle.  Also made it so no menu
 *                                  appears when there are no items to equip and feedback is given.  That feedback is not visible
 *                                  when screen is loaded.
 * Andrew Osborne, April 1 2007 | Made it so when you equip something it is taken out of the inventory and what you equipment you
 *                                  disengaged is put 'into' the inventory.  Also added attribute detail to armor/weapon selection
 * Andrew Osborne, April 2 2007 | Fixed so that when you equip item that you have multiple of, the second (or third or...) item is not
 *                                  lost.
 *
 */


#include "UIPartyStatusLayout.h"                                // class implemented

#include <util.h>

#include <Database/DBEngine.h>
#include <UI/UIManager.h>
#include <UI/UIImage.h>
#include <UI/UIMenu.h>
#include <UI/UIText.h>

#include <UI/FuncObj.h>

#include <GameEngine/Character.h>

class SwitchToFunction2 : public FuncObj
{
public:
    SwitchToFunction2(UILayout *layout, UIMenu* newListener, UIText* feedback, string message)
    : mLayout(layout), mNewListener( newListener ), mFeedback(feedback), mType(message)
    {
    }

    void operator()(void)
    {
        if ( (mLayout) && (mNewListener) )
            if (!mNewListener->Empty())
            {
                mFeedback->SetVisible(false);
                mLayout->SetEventHandler(mNewListener);
            }
            else
            {
                mFeedback->SetVisible(true);
                mFeedback->ChangeText("You have no " + mType + " to equip");
            }

    }


protected:
    UILayout* mLayout;
    UIMenu* mNewListener;
    UIText* mFeedback;
    string mType;

};

class SelectMemberFunction : public FuncObj
{

public:
    SelectMemberFunction(Character *c, UIPartyStatusLayout* parent, UIEventListener* next)
    : mChar(c), mParent(parent), mNext(next)
    {
    }

    virtual void operator()(void)
    {
        Item* newItem = mParent->GetEquipItem();
        Item* oldItem = NULL;
        if (newItem->GetType()==Item::ARMOR)
        {
            oldItem = mChar->GetArmor();
            mChar->SetArmor( dynamic_cast<ArmorItem*>( newItem ) );
        }
        else if (newItem->GetType()==Item::WEAPON)
        {
            oldItem = mChar->GetWeapon();
            mChar->SetWeapon( dynamic_cast<WeaponItem*>( newItem ) );
        }
        mParent->SetEventHandler(mNext);


        // Add item (that was just unequiped) to inventory
        // And remove item from inventory that had just been equipped.
        vector<Item*>* inventory = GameEngine::GetInstance()->GetItems();
        for (vector<Item*>::iterator iter = inventory->begin(); iter!= inventory->end(); ++iter)
        {
            if ((*iter)==newItem)
            {
                (*iter) = oldItem;
                iter = inventory->end();
                iter--;
            }
        }

        mParent->UpdateInfo();

    }

protected:
    Character* mChar;
    UIPartyStatusLayout* mParent;
    UIEventListener* mNext;

};


class EquipArmorFunction : public FuncObj
{
public:
    EquipArmorFunction(Item *i, UIPartyStatusLayout* parent, UIEventListener* partyMenu)
    : mItem(i), mParent(parent), mNext(partyMenu)
    {
    }

    virtual void operator()(void)
    {
        mParent->SetEquipItem(mItem);
        mParent->SetEventHandler(mNext);
    }

protected:
    Item* mItem;
    UIPartyStatusLayout* mParent;
    UIEventListener* mNext;

};


class EquipWeaponFunction : public FuncObj
{
public:
    EquipWeaponFunction(Item *i, UIPartyStatusLayout* parent, UIEventListener* partyMenu)
    : mItem(i), mParent(parent), mNext(partyMenu)
    {
    }

    virtual void operator()(void)
    {
        mParent->SetEquipItem(mItem);
        mParent->SetEventHandler(mNext);
    }

protected:
    Item* mItem;
    UIPartyStatusLayout* mParent;
    UIEventListener* mNext;

};


class PopLayoutFunction5 : public FuncObj
{
    virtual void operator()(void)
    {
        UIManager::GetInstance()->PopLayout();
    }

};

/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

UIPartyStatusLayout::UIPartyStatusLayout()
: mFeedback( NULL ), mPartyList( NULL )
{
    // Background
    UIImage* back = new UIImage("castle_main.png");
    mElements.push_back(back);

    int standardMenuSpacing = 5;
    Point secondaryMenuPoint( 450, 40 );

    // Main Menu Initial declaration
    mMenu = new UIMenu();

    // Armory menu
    mArmorMenu = new UIMenu();
    mArmorMenu->SetBackground("menu_back_large.png");
    mArmorMenu->SetSpacing(standardMenuSpacing);
    mArmorMenu->SetPos(secondaryMenuPoint);
    mArmorMenu->SetParent(this);
    mArmorMenu->SetCancel(mMenu);
    mArmorMenu->SetVisibleWhenDisabled(false);
    mArmorMenu->Disable();
    mElements.push_back(mArmorMenu);

    // Weapon menu
    mWeaponMenu = new UIMenu();
    mWeaponMenu->SetBackground("menu_back_large.png");
    mWeaponMenu->SetSpacing(standardMenuSpacing);
    mWeaponMenu->SetPos(secondaryMenuPoint);
    mWeaponMenu->SetParent(this);
    mWeaponMenu->SetCancel(mMenu);
    mWeaponMenu->SetVisibleWhenDisabled(false);
    mWeaponMenu->Disable();
    mElements.push_back(mWeaponMenu);

    // Weapon menu
    mMasterPartyMenu = new UIMenu();
    mMasterPartyMenu->SetBackground("menu_back_large.png");
    mMasterPartyMenu->SetSpacing(standardMenuSpacing);
    mMasterPartyMenu->SetPos(secondaryMenuPoint);
    mMasterPartyMenu->SetParent(this);
    mMasterPartyMenu->SetCancel(mMenu);
    mMasterPartyMenu->SetVisibleWhenDisabled(false);
    mMasterPartyMenu->Disable();
    mElements.push_back(mMasterPartyMenu);

    // Fleshing out Main menu

    mFeedback = new UIText(" ", 18, 255, 255, 0);
    mFeedback->SetPos( Point(190, 20) );
    mElements.push_back(mFeedback);

    mMenu->SetPos( Point(20, 20) );
    mMenu->SetBackground("menu_back_small.png");
    //mMenu->AddButton( "Select New Party", new SwitchToFunction2( this, mMasterPartyMenu ) );
    mMenu->AddButton( "Equip Armor", new SwitchToFunction2( this, mArmorMenu, mFeedback, "Armor" ) );
    mMenu->AddButton( "Equip Weapon", new SwitchToFunction2( this, mWeaponMenu, mFeedback, "Weapons" ) );
    mMenu->AddButton( "Back", new PopLayoutFunction5() );
    mElements.push_back(mMenu);
    mDefaultEventListener = mMenu;


    // Initialize Character windows


    UICharWindow *tempWin = NULL;
    int x1 = 20;
    int y1 = 150;
    int x2 = x1 + 210;
    int y2 = y1 + 150;


    for (int i= 0; i<4; i++)
    {

        tempWin = new UICharWindow();
        //tempWin->SetPos( Point(200, 30) );
        tempWin->ClearCharacter();
        mPartyWindow.push_back(tempWin);
        mElements.push_back(tempWin);

        // Set posiiton (only different parameter)
        switch (i)
        {
            case 0:
                tempWin->SetPos( Point(x1, y1) );
                break;
            case 1:
                tempWin->SetPos( Point(x2,y1) );
                break;
            case 2:
                tempWin->SetPos( Point(x1,y2) );
                break;
            case 3:
                tempWin->SetPos( Point(x2,y2) );
                break;
            default:
                break;
        }

        tempWin = NULL;
    }


    mName = "PartyStatus";

}// UIPartyStatusLayout



UIPartyStatusLayout::~UIPartyStatusLayout()
{
    for( UICharWindowPtrItr i = mPartyWindow.begin(); i != mPartyWindow.end(); ++i )
    {
        // If it's not stored in mElements, kill it
        if( find( mElements.begin(), mElements.end(), *i ) == mElements.end() )
        {
            delete *i;
        }
    }
    mPartyWindow.clear();

    if (mPartyList)
    {
        delete mPartyList;
        mPartyList = NULL;
    }

}// ~UIPartyStatusLayout


//============================= OPERATORS ====================================



//============================= OPERATIONS ===================================




void UIPartyStatusLayout::OnLoad(void)
{

    UILayout::OnLoad();

    // Set feedback invisible
    mFeedback->SetVisible(false);

    // Load current party members
    //----------------------------------------------

    mPartyList = DBEngine::GetInstance()->LoadParty(1);


    //mMenu->ClearButtons();
    int partyIndex = 0;
    mMasterPartyMenu->ClearButtons();
    for (std::vector<Character*>::iterator iter = mPartyList->begin(); iter != mPartyList->end(); ++iter)
    {
        mPartyWindow[partyIndex]->SetCharacter( (*iter) );
        partyIndex++;

        mMasterPartyMenu->AddButton( (*iter)->GetName(), new SelectMemberFunction( (*iter), this, mMenu ) );
    }




    // Load Univeral Inventory
    // ----------------------------------------------------------
    /*std::vector<Item*>* itemInventory = GameEngine::GetInstance()->GetItems();


    // Create Armour Menu
    // ----------------------------------------------------------
    mArmorMenu->ClearButtons();
    for (std::vector<Item*>::iterator iter2 = itemInventory->begin(); iter2 != itemInventory->end(); ++iter2)
    {
        if ((*iter2)->GetType()==Item::ARMOR)
            mArmorMenu->AddButton( (*iter2)->GetName(), new EquipArmorFunction( (*iter2), this, mMasterPartyMenu ) );
    }


    // Create Weapon Menu
    // ----------------------------------------------------------

    mWeaponMenu->ClearButtons();
    for (std::vector<Item*>::iterator iter3 = itemInventory->begin(); iter3 != itemInventory->end(); ++iter3)
    {
        if ((*iter3)->GetType()==Item::WEAPON)
            mWeaponMenu->AddButton( (*iter3)->GetName(), new EquipWeaponFunction( (*iter3), this, mMasterPartyMenu ) );
    }*/

    UpdateInfo();


    // Ghost or un-Ghost eqiuping options
    Level* tempLevel = GameEngine::GetInstance()->GetLevel();
    if (tempLevel)
    {
        // Battle is currently in progress
        mMenu->SetGhost(0,true);
        mMenu->SetGhost(1,true);
    }
    else
    {
        // Battle is not in progress
        mMenu->SetGhost(0,false);
        mMenu->SetGhost(1,false);
    }
    tempLevel = NULL;

}

void UIPartyStatusLayout::OnClose(void)
{
    UILayout::OnClose();

    if (mPartyList)
    {
        delete mPartyList;
        mPartyList = NULL;
    }
}
//Update();

void UIPartyStatusLayout::UpdateInfo(void)
{
    for (std::vector<UICharWindow*>::iterator iter = mPartyWindow.begin(); iter != mPartyWindow.end(); ++iter)
    {
        (*iter)->Update();
    }

    // Load Univeral Inventory
    // ----------------------------------------------------------
    std::vector<Item*>* itemInventory = GameEngine::GetInstance()->GetItems();


    // Create Armour Menu
    // ----------------------------------------------------------
    mArmorMenu->ClearButtons();
    for (std::vector<Item*>::iterator iter2 = itemInventory->begin(); iter2 != itemInventory->end(); ++iter2)
    {
        if ((*iter2)->GetType()==Item::ARMOR)
            mArmorMenu->AddButton( (*iter2)->GetName() + " (" + toString((*iter2)->GetAttr()) + ")", new EquipArmorFunction( (*iter2), this, mMasterPartyMenu ) );
    }


    // Create Weapon Menu
    // ----------------------------------------------------------

    mWeaponMenu->ClearButtons();
    string tempStr;
    for (std::vector<Item*>::iterator iter3 = itemInventory->begin(); iter3 != itemInventory->end(); ++iter3)
    {
        if ((*iter3)->GetType()==Item::WEAPON)
        {
            tempStr = (*iter3)->GetName() + " (" + toString((*iter3)->GetAttr()) + ")";
            mWeaponMenu->AddButton( tempStr, new EquipWeaponFunction( (*iter3), this, mMasterPartyMenu ) );
        }
    }


}
//============================= ACCESS     ===================================
//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
