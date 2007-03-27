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
 */
#include "UIPartyStatusLayout.h"                                // class implemented

#include <util.h>

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

    mMenu->SetPos( Point(30, 30) );
    mMenu->AddButton( "Select New Party", new SwitchToFunction2( this, mMasterPartyMenu ) );
    mMenu->AddButton( "Equip Armor", new SwitchToFunction2( this, mArmorMenu ) );
    mMenu->AddButton( "Equip Weapon", new SwitchToFunction2( this, mArmorMenu ) );
    mMenu->AddButton( "Done", new PopLayoutFunction5() );
    mElements.push_back(mMenu);
    mDefaultEventListener = mMenu;


    // Initialize Character windows


    UICharWindow *tempWin;
    int x1 = 30;
    int y1 = 150;
    int x2 = 180;
    int y2 = 300;

    // Window 1
    tempWin = new UICharWindow();
    tempWin->SetPos( Point(200, 30) );
    tempWin->ClearCharacter();
    mPartyWindow.push_back(tempWin);
    mElements.push_back(tempWin);
    tempWin = NULL;

    // Window 2
    tempWin = new UICharWindow();
    tempWin->SetPos( Point(x2,y1) );
    tempWin->ClearCharacter();
    mPartyWindow.push_back(tempWin);
    //mElements.push_back(tempWin);
    tempWin = NULL;

    // Window 3
    tempWin = new UICharWindow();
    tempWin->SetPos( Point(x1,y2) );
    tempWin->ClearCharacter();
    mPartyWindow.push_back(tempWin);
    //mElements.push_back(tempWin);
    tempWin = NULL;


    // Window 4
    tempWin = new UICharWindow();
    tempWin->SetPos( Point(x2,y2) );
    tempWin->ClearCharacter();
    mPartyWindow.push_back(tempWin);
    //mElements.push_back(tempWin);
    tempWin = NULL;



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


/*void UIPartyStatusLayout::ProcessEvent( const InputManager::INPUTKEYS evt )
{

    switch (evt)
    {
        case InputManager::CONFIRM:
            UIManager::GetInstance()->PopLayout();
            break;
        default:
            break;
    }

}*/

void UIPartyStatusLayout::OnLoad(void)
{

    UILayout::OnLoad();


    // Load current party members
    //----------------------------------------------

    std::vector<Character*> partyMembers; // = GameEngine::GetInstance()->GetParty();

    // Debug
    partyMembers.clear();

    //mMenu->ClearButtons();
    int partyIndex = 0;
    for (std::vector<Character*>::iterator iter = partyMembers.begin(); iter != partyMembers.end(); ++iter)
    {
        mPartyWindow[partyIndex]->SetCharacter( (*iter) );
    }


    // Load All Party members
    //----------------------------------------------
    std::vector<Character*> allPartyMembers;

    allPartyMembers.clear();

    mMasterPartyMenu->ClearButtons();
    for (std::vector<Character*>::iterator iter = allPartyMembers.begin(); iter != allPartyMembers.end(); ++iter)
    {
        mMasterPartyMenu->AddButton( (*iter)->GetName(), new SelectNewMemberFunction( (*iter) ) );
    }

    // Load Armour Inventory
    // ----------------------------------------------------------
    std::vector<Item*> armorInventory; // = GameEngine::GetInstance()->GetArmourInventory();

    // Debug
    armorInventory.clear();

    mArmorMenu->ClearButtons();
    for (std::vector<Item*>::iterator iter2 = armorInventory.begin(); iter2 != armorInventory.end(); ++iter2)
    {
        mArmorMenu->AddButton( (*iter2)->GetName(), new EquipArmorFunction( (*iter2) ) );
    }



    // Load Weapon Inventory
    // ----------------------------------------------------------
    std::vector<Item*> weaponInventory; // = GameEngine::GetInstance()->GetArmourInventory();

    // Debug
    weaponInventory.clear();

    mWeaponMenu->ClearButtons();
    for (std::vector<Item*>::iterator iter3 = weaponInventory.begin(); iter3 != weaponInventory.end(); ++iter3)
    {
        mWeaponMenu->AddButton( (*iter3)->GetName(), new EquipWeaponFunction( (*iter3) ) );
    }



    // Temp Debug

    /*mMenu->ClearButtons();
    Item* tempItem = new Item();

    mMenu->AddButton( "Item1" , new PurchaseItemFunction2( tempItem, mFeedback ) );
    mMenu->AddButton( "Item2" , new PurchaseItemFunction2( tempItem, mFeedback ) );
    mMenu->AddButton( "Item3" , new PurchaseItemFunction2( tempItem, mFeedback ) );

    mMenu->AddButton( "Done", new PopLayoutFunction4() );

    */
}


//============================= ACCESS     ===================================
//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
