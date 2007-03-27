/**
 * File: Healer.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Mike Malyuk, February 7 2007 | Initial design
 * Mike Malyuk, February 11 2007 | Made CalcAction return non-pointer Point vector
 *                                 Added variables for mIsDead, mExhausted and new attr DEF
 * Mike Malyuk, February 14 2007 | On level up, curHP renewed.
 * Mike Malyuk, February 14 2007 | On level up more verbose, also added "Heal" method.
 * Mike Malyuk, March 16 2007    | Be nice if you leveled up eh!
 * Mike Malyuk, March 16 2007    | Healer may now heal self. Go healer! Couple other fixes for goodness
 * Karl Schmidt, March 20 2007   | Major adding of consts and reference usage, rearranging includes
 * Karl Schmidt, March 22 2007   | Changed name of GetClassName
 * Mike Malyuk,  March 26 2007   | Balance change, Levelling up now only adds new HP to curHP instead of max
 */

#include "Healer.h"                                // class implemented

#include <util.h>

namespace
{
    const std::string characterClassName = "Healer";
}

/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

Healer::Healer()
{
    mName = "Bob";
    mLevel = 1;
    mMaxHP = 1;
    mCurHP = 1;
    mExp = 0;
    mMaxActRange = 1;
    mCurPos = Point(0,0);
    mArmor = NULL;
    mWeapon = NULL;
    mAttributes[POW] = 2;
    mAttributes[AGI] = 4;
    mAttributes[DEF] = 1;
    mExhausted = false;
    mIsDead = false;
    mTarget = NULL;
}// Healer

Healer::Healer(const string & name, const int level, WeaponItem* weapon, ArmorItem* armor)
{
    mName = name;
    mLevel = 1;
    mWeapon = weapon;
    mArmor = armor;
    mMaxHP = 10;
    mCurHP = 10;
    mExp = 0;
    mMaxActRange = 2;
    mCurPos = Point(0,0);
    mAttributes[POW] = 2;
    mAttributes[AGI] = 4;
    mAttributes[DEF] = 1;
    mExhausted = false;
    mIsDead = false;
    mTarget = NULL;
    if(weapon != NULL)
    {
        mAttributes[POW] = mAttributes[POW] + weapon->GetAttr();
    }
    if(armor != NULL)
    {
        mAttributes[DEF] = mAttributes[DEF] + armor->GetAttr();
    }
    for(int i = 1; i < level; i++)
    {
        LevelUp();
    }
}

Healer::~Healer()
{
}// ~Healer



//============================= OPERATIONS ===================================
void Healer::LevelUp()
{
    mAttributes[POW] = mAttributes[POW]+2;
    mAttributes[AGI] = mAttributes[AGI]+1;
    mAttributes[DEF] = mAttributes[DEF]+1;
    mMaxHP = mMaxHP + 2;
    mCurHP = mCurHP + 2;
    mLevel++;
    cout << "Healer (" << mName << ") has levelled up to level " << mLevel << endl;
}
const PointVec Healer::CalcAction()
{
    PointVec points;
    points.push_back(Point(mCurPos.GetX()-1, mCurPos.GetY()));
    points.push_back(Point(mCurPos.GetX()+1, mCurPos.GetY()));
    points.push_back(Point(mCurPos.GetX(), mCurPos.GetY()-1));
    points.push_back(Point(mCurPos.GetX(), mCurPos.GetY()+1));
    if(mCurHP < mMaxHP)
    {
        points.push_back(Point(mCurPos.GetX(), mCurPos.GetY()));
    }
    return points;
}

void Healer::Heal(Character* buddy)
{
    if(buddy->GetMaxHP() == buddy->GetHP())
    {
        mExhausted = true;
        return;
    }
    else if(buddy->GetMaxHP() < (buddy->GetHP() + mAttributes[POW]))
    {
        cout << "Healer (" << mName << ") heals " << buddy->GetCharacterClassName() << " (" << buddy->GetName() << ") for " << buddy->GetMaxHP() - buddy->GetHP() << " HP." << endl;
        buddy->SetHP(buddy->GetMaxHP());
    }
    else
    {
        cout << "Healer (" << mName << ") heals " << buddy->GetCharacterClassName() << " (" << buddy->GetName() << ") for " << mAttributes[POW] << " HP." << endl;
        buddy->SetHP(buddy->GetHP() + mAttributes[POW]);
    }
    mExp = mExp+20;
    if(mExp == 100)
    {
        LevelUp();
        mExp = 0;
    }
    mExhausted = true;
}
//============================= ACCESS     ===================================
//============================= INQUIRY    ===================================
const inline std::string & Healer::GetCharacterClassName() const
{
    return characterClassName;
}
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
