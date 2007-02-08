/**
 * File: Healer.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Mike Malyuk, February 7 2007 | Initial design
 */

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
    mAttributes[AGI] = 2;
}// Healer

Healer::Healer(string name, int level, WeaponItem* weapon, ArmorItem* armor)
{
    mName = name;
    mLevel = level;
    mWeapon = weapon;
    mArmor = armor;
    mMaxHP = 10;
    mCurHP = 10;
    mExp = 0;
    mMaxActRange = 2;
    mCurPos = Point(0,0);
    mAttributes[POW] = 2;
    mAttributes[AGI] = 2;
    for(int i = 0; i < level; i++)
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
    mAttributes[POW] = mAttributes[POW]+1;
    mAttributes[AGI] = mAttributes[AGI]+1;
    mMaxHP = mMaxHP + 2;
    mLevel++;
}
vector<Point*> Healer::CalcAction()
{
    vector<Point*> points;
    points.push_back(new Point(mCurPos.GetX()-1, mCurPos.GetY()));
    points.push_back(new Point(mCurPos.GetX()+1, mCurPos.GetY()));
    points.push_back(new Point(mCurPos.GetX(), mCurPos.GetY()-1));
    points.push_back(new Point(mCurPos.GetX(), mCurPos.GetY()+1));
    return points;
}
//============================= ACCESS     ===================================
//============================= INQUIRY    ===================================
    string Healer::GetClassName()
    {
        return "Healer";
    }
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
