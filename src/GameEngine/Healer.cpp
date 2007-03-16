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
 */

#include <util.h>


#include "Healer.h"                                // class implemented


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

Healer::Healer(string name, int level, WeaponItem* weapon, ArmorItem* armor)
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
    mCurHP = mMaxHP;
    mLevel++;
    cout << "Healer (" << mName << ") has levelled up to level " << mLevel << endl;
}
vector<Point> Healer::CalcAction()
{
    vector<Point> points;
    points.push_back(Point(mCurPos.GetX()-1, mCurPos.GetY()));
    points.push_back(Point(mCurPos.GetX()+1, mCurPos.GetY()));
    points.push_back(Point(mCurPos.GetX(), mCurPos.GetY()-1));
    points.push_back(Point(mCurPos.GetX(), mCurPos.GetY()+1));
    return points;
}

void Healer::Heal(Character* buddy)
{
    if(buddy->GetMaxHP() < (buddy->GetHP() + mAttributes[POW]))
    {
        cout << "Healer (" << mName << ") heals " << buddy->GetClassName() << " (" << buddy->GetName() << ") for " << buddy->GetMaxHP() - buddy->GetHP() << " HP." << endl;
        buddy->SetHP(buddy->GetMaxHP());
    }
    else
    {
                cout << "Healer (" << mName << ") heals " << buddy->GetClassName() << " (" << buddy->GetName() << ") for " << mAttributes[POW] << " HP." << endl;
        buddy->SetHP(buddy->GetHP() + mAttributes[POW]);
    }
    mExhausted = true;
}
//============================= ACCESS     ===================================
//============================= INQUIRY    ===================================
    string Healer::GetClassName()
    {
        return "Healer";
    }
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
