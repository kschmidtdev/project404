/**
 * File: Knight.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Mike Malyuk, February 7 2007 | Initial design
 * Mike Malyuk, February 11 2007 | Made CalcAction return non-pointer Point vector
 */

#include "Knight.h"                                // class implemented


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
    mAttributes[AGI] = 3;
}// Knight

Knight::Knight(string name, int level, WeaponItem* weapon, ArmorItem* armor)
{
    mName = name;
    mLevel = level;
    mWeapon = weapon;
    mArmor = armor;
    mMaxHP = 20;
    mCurHP = 20;
    mExp = 0;
    mMaxActRange = 1;
    mCurPos = Point(0,0);
    mAttributes[POW] = 3;
    mAttributes[AGI] = 3;
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
    mAttributes[POW] = mAttributes[POW]+2;
    mAttributes[AGI] = mAttributes[AGI]+2;
    mMaxHP = mMaxHP + 5;
    mLevel++;
}
vector<Point> Knight::CalcAction()
{
    vector<Point> points;
    points.push_back(Point(mCurPos.GetX()-1, mCurPos.GetY()));
    points.push_back(Point(mCurPos.GetX()+1, mCurPos.GetY()));
    points.push_back(Point(mCurPos.GetX(), mCurPos.GetY()-1));
    points.push_back(Point(mCurPos.GetX(), mCurPos.GetY()+1));
    return points;
}
//============================= ACCESS     ===================================
//============================= INQUIRY    ===================================
    string Knight::GetClassName()
    {
        return "Knight";
    }
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////