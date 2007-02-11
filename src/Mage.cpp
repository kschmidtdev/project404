/**
 * File: Mage.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Mike Malyuk, February 7 2007 | Initial design
 * Mike Malyuk, February 11 2007 | Made CalcAction return non-pointer Point vector
 */

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
    mAttributes[AGI] = 2;
}// Mage

Mage::Mage(string name, int level, WeaponItem* weapon, ArmorItem* armor)
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
    mAttributes[POW] = 5;
    mAttributes[AGI] = 2;
    for(int i = 0; i < level; i++)
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
    mAttributes[POW] = mAttributes[POW]+3;
    mAttributes[AGI] = mAttributes[AGI]+1;
    mMaxHP = mMaxHP + 1;
    mLevel++;
}
vector<Point> Mage::CalcAction()
{
    vector<Point> points;
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
    string Mage::GetClassName()
    {
        return "Mage";
    }
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
