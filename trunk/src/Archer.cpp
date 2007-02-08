/**
 * File: Archer.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Mike Malyuk, February 7 2007 | Initial design
 */

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
}// Archer

Archer::Archer(string name, int level, WeaponItem* weapon, ArmorItem* armor)
{
    mName = name;
    mLevel = level;
    mWeapon = weapon;
    mArmor = armor;
    mMaxHP = 15;
    mCurHP = 15;
    mExp = 0;
    mMaxActRange = 2;
    mCurPos = Point(0,0);
    mAttributes[POW] = 2;
    mAttributes[AGI] = 5;
    for(int i = 0; i < level; i++)
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
    mMaxHP = mMaxHP + 3;
    mLevel++;
}
vector<Point*> Archer::CalcAction()
{
    vector<Point*> points;
    points.push_back(new Point(mCurPos.GetX()-1, mCurPos.GetY()-1));
    points.push_back(new Point(mCurPos.GetX()+1, mCurPos.GetY()+1));
    points.push_back(new Point(mCurPos.GetX()+1, mCurPos.GetY()-1));
    points.push_back(new Point(mCurPos.GetX()-1, mCurPos.GetY()+1));
    points.push_back(new Point(mCurPos.GetX()-2, mCurPos.GetY()));
    points.push_back(new Point(mCurPos.GetX()+2, mCurPos.GetY()));
    points.push_back(new Point(mCurPos.GetX(), mCurPos.GetY()-2));
    points.push_back(new Point(mCurPos.GetX(), mCurPos.GetY()+2));
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
