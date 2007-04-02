/**
 * File: Archer.cpp
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
 * Karl Schmidt, March 22 2007   | Changed name of GetClassName
 * Mike Malyuk,  March 26 2007   | Balance change, Levelling up now only adds new HP to curHP instead of max
 */

#include "Archer.h"                                // class implemented

#include <util.h>

namespace
{
    const std::string characterClassName = "Archer";
}

/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

Archer::Archer()
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
    mAttributes[POW] = 2;
    mAttributes[AGI] = 6;
    mAttributes[DEF] = 2;
    mExhausted = false;
    mIsDead = false;
    mTarget = NULL;
}// Archer

Archer::Archer( const string & name, const int level, WeaponItem* weapon, ArmorItem* armor)
{
    mName = name;
    mLevel = 1;
    mWeapon = weapon;
    mArmor = armor;
    mMaxHP = 15;
    mCurHP = 15;
    mExp = 0;
    mMaxActRange = 2;
    mCurPos = Point(0,0);
    mAttributes[POW] = 2;
    mAttributes[AGI] = 6;
    mAttributes[DEF] = 2;
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

Archer::~Archer()
{
}// ~Archer



//============================= OPERATIONS ===================================
void Archer::LevelUp()
{
    mAttributes[POW] = mAttributes[POW]+2;
    mAttributes[AGI] = mAttributes[AGI]+2;
    mAttributes[DEF] = mAttributes[DEF]+1;
    mMaxHP = mMaxHP + 3;
    mCurHP = mCurHP+3;
    mLevel++;
    cout << "Archer (" << mName << ") has levelled up to level " << mLevel << endl;
}
const PointVec Archer::CalcAction()
{
    PointVec points;
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
const inline std::string & Archer::GetCharacterClassName() const
{
    return characterClassName;
}
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
