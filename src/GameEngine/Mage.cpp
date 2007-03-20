/**
 * File: Mage.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Mike Malyuk, February 7 2007  | Initial design
 * Mike Malyuk, February 11 2007 | Made CalcAction return non-pointer Point vector
 *                                 Added variables for mIsDead, mExhausted and new attr DEF
 * Mike Malyuk, February 14 2007 | On level up, curHP renewed.
 * Mike Malyuk, February 14 2007 | Levelling up is couted
 * Karl Schmidt, March 20 2007   | Major adding of consts and reference usage, rearranging includes
 */

#include <util.h>


#include "Mage.h"                                // class implemented


/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

Mage::Mage()
{
    mName = "Bob";
    mLevel = 1;
    mMaxHP = 1;
    mCurHP = 1;
    mExp = 0;
    mMaxActRange = 2;
    mCurPos = Point(0,0);
    mArmor = NULL;
    mWeapon = NULL;
    mAttributes[POW] = 5;
    mAttributes[AGI] = 4;
    mAttributes[DEF] = 1;
    mExhausted = false;
    mIsDead = false;
    mTarget = NULL;
}// Mage

Mage::Mage(const string & name, const int level, WeaponItem* weapon, ArmorItem* armor)
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
    mAttributes[POW] = 5;
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

Mage::~Mage()
{
}// ~Mage



//============================= OPERATIONS ===================================
void Mage::LevelUp()
{
    mAttributes[POW] = mAttributes[POW]+2;
    mAttributes[AGI] = mAttributes[AGI]+1;
    mAttributes[DEF] = mAttributes[DEF]+1;
    mMaxHP = mMaxHP + 1;
    mCurHP = mMaxHP;
    mLevel++;
    cout << "Mage (" << mName << ") has levelled up to level " << mLevel << endl;
}
const PointVec Mage::CalcAction()
{
    PointVec points;
    points.push_back(Point(mCurPos.GetX()-1, mCurPos.GetY()));
    points.push_back(Point(mCurPos.GetX()+1, mCurPos.GetY()));
    points.push_back(Point(mCurPos.GetX(), mCurPos.GetY()-1));
    points.push_back(Point(mCurPos.GetX(), mCurPos.GetY()+1));
    points.push_back(Point(mCurPos.GetX()-1, mCurPos.GetY()-1));
    points.push_back(Point(mCurPos.GetX()+1, mCurPos.GetY()+1));
    points.push_back(Point(mCurPos.GetX()+1, mCurPos.GetY()-1));
    points.push_back(Point(mCurPos.GetX()-1, mCurPos.GetY()+1));
    points.push_back(Point(mCurPos.GetX()-2, mCurPos.GetY()));
    points.push_back(Point(mCurPos.GetX()+2, mCurPos.GetY()));
    points.push_back(Point(mCurPos.GetX(), mCurPos.GetY()-2));
    points.push_back(Point(mCurPos.GetX(), mCurPos.GetY()+2));
    return points;
}
//============================= ACCESS     ===================================
//============================= INQUIRY    ===================================
const string Mage::GetClassName() const
{
    return "Mage";
}
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
