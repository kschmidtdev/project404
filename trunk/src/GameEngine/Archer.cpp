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
 */

#include <util.h>


#include "Archer.h"                                // class implemented


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
    mAttributes[AGI] = 5;
    mAttributes[DEF] = 2;
    mExhausted = false;
    mIsDead = false;
    mTarget = NULL;
}// Archer

Archer::Archer(string name, int level, WeaponItem* weapon, ArmorItem* armor)
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
    mAttributes[AGI] = 5;
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
    mAttributes[POW] = mAttributes[POW]+1;
    mAttributes[AGI] = mAttributes[AGI]+3;
    mAttributes[DEF] = mAttributes[DEF]+2;
    mMaxHP = mMaxHP + 3;
    mCurHP = mMaxHP;
    mLevel++;
    cout << "Archer (" << mName << ") has levelled up to level " << mLevel << endl;
}
vector<Point> Archer::CalcAction()
{
    vector<Point> points;
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
    string Archer::GetClassName()
    {
        return "Archer";
    }
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
