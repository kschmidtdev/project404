/**
 * File: Knight.cpp
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

#include "Knight.h"                                // class implemented

#include <util.h>

namespace
{
    const std::string characterClassName = "Knight";
}

/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

Knight::Knight()
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
    mAttributes[POW] = 3;
    mAttributes[AGI] = 5;
    mAttributes[DEF] = 4;
    mExhausted = false;
    mIsDead = false;
    mTarget = NULL;
}// Knight

Knight::Knight( const string & name, const int level, WeaponItem* weapon, ArmorItem* armor)
{
    mName = name;
    mLevel = 1;
    mWeapon = weapon;
    mArmor = armor;
    mMaxHP = 20;
    mCurHP = 20;
    mExp = 0;
    mMaxActRange = 1;
    mCurPos = Point(0,0);
    mAttributes[POW] = 3;
    mAttributes[AGI] = 5;
    mAttributes[DEF] = 5;
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

Knight::~Knight()
{
}// ~Knight



//============================= OPERATIONS ===================================
void Knight::LevelUp()
{
    mAttributes[POW] = mAttributes[POW]+1;
    mAttributes[AGI] = mAttributes[AGI]+1;
    mAttributes[DEF] = mAttributes[DEF]+4;
    mMaxHP = mMaxHP + 5;
    mCurHP = mCurHP + 5;
    mLevel++;
    cout << "Knight (" << mName << ") has levelled up to level " << mLevel << endl;
}
const PointVec Knight::CalcAction()
{
    PointVec points;
    points.push_back(Point(mCurPos.GetX()-1, mCurPos.GetY()));
    points.push_back(Point(mCurPos.GetX()+1, mCurPos.GetY()));
    points.push_back(Point(mCurPos.GetX(), mCurPos.GetY()-1));
    points.push_back(Point(mCurPos.GetX(), mCurPos.GetY()+1));
    return points;
}
//============================= ACCESS     ===================================
//============================= INQUIRY    ===================================
const inline std::string & Knight::GetCharacterClassName() const
{
    return characterClassName;
}

/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
