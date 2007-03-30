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
    SwitchToFunction2(UILayout *layout, UIEventListener* newListener)
    : mLayout(layout), mNewListener( newListener )
    {
    }

    void operator()(void)
    {
        if ( (mLayout) && (mNewListener) )
            mLayout->SetEventHandler(mNewListener);
    }


protected:
    UILayout* mLayout;
    UIEventListener* mNewListener;

};

class SelectNewMemberFunction : public FuncObj
{

public:
    SelectNewMemberFunction(Character *c)
    {
    }

    virtual void operator()(void)
    {
        //UIManager::GetInstance()->PopLayout();
    }

};


class EquipArmorFunction : public FuncObj
{
public:
    EquipArmorFunction(Item *i)
    {
    }

    virtual void operator()(void)
    {
        //UIManager::GetInstance()->PopLayout();
    }

};


class EquipWeaponFunction : public FuncObj
{
public:
    EquipWeaponFunction(Item *i)
    {
    }

    virtual void operator()(void)
    {
        //UIManager::GetInstance()->PopLayout();
    }

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
: mPartyList( NULL )
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

    mMenu->SetPos( Point(20, 20) );
    mMenu->SetBackground("menu_back_small.png");
    //mMenu->AddButton( "Select New Party", new SwitchToFunction2( this, mMasterPartyMenu ) );
    //mMenu->AddButton( "Equip Armor", new SwitchToFunction2( this, mArmorMenu ) );
    //mMenu->AddButton( "Equip Weapon", new SwitchToFunction2( this, mWeaponMenu ) );
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

}// ~UIPartyStatusLayout


//============================= OPERATORS ====================================



//============================= OPERATIONS ===================================




void UIPartyStatusLayout::OnLoad(void)
{

    UILayout::OnLoad();


    // Load current party members
    //----------------------------------------------

    mPartyList = DBEngine::GetInstance()->LoadParty(1);

    // Debug
    //partyMembers.clear();

    //mMenu->ClearButtons();
    int partyIndex = 0;
    for (std::vector<Character*>::iterator iter = mPartyList->begin(); iter != mPartyList->end(); ++iter)
    {
        mPartyWindow[partyIndex]->SetCharacter( (*iter) );
        partyIndex++;
    }




    // Load All Party members
    //----------------------------------------------
    /*std::vector<Character*> allPartyMembers;

    allPartyMembers.clear();

    mMasterPartyMenu->ClearButtons();
    for (std::vector<Character*>::iterator iter = allPartyMembers.begin(); iter != allPartyMembers.end(); ++iter)
    {
        mMasterPartyMenu->AddButton( (*iter)->GetName(), new SelectNewMemberFunction( (*iter) ) );
    }*/



    // Load Univeral Inventory
    // ----------------------------------------------------------
    std::vector<Item*>* itemInventory = GameEngine::GetInstance()->GetItems();


    // Create Armour Menu
    // ----------------------------------------------------------
    mArmorMenu->ClearButtons();
    for (std::vector<Item*>::iterator iter2 = itemInventory->begin(); iter2 != itemInventory->end(); ++iter2)
    {
        if ((*iter2)->GetType()==Item::ARMOR)
            mArmorMenu->AddButton( (*iter2)->GetName(), new EquipArmorFunction( (*iter2) ) );
    }


    // Create Weapon Menu
    // ----------------------------------------------------------

    mWeaponMenu->ClearButtons();
    for (std::vector<Item*>::iterator iter3 = itemInventory->begin(); iter3 != itemInventory->end(); ++iter3)
    {
        if ((*iter3)->GetType()==Item::WEAPON)
            mWeaponMenu->AddButton( (*iter3)->GetName(), new EquipWeaponFunction( (*iter3) ) );
    }


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

//============================= ACCESS     ===================================
//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
