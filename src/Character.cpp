/**
 * File: Character.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Mike Malyuk, February 7 2007 | Initial design
 */

#include "Character.h"                                // class implemented


/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

Character::Character(){}
Character::~Character()
{
}// ~Character

//============================= OPERATIONS ===================================
void Character::LevelUp(){}
vector<Point*> Character::CalcAction()
{
    vector<Point*> points;
    points.push_back(new Point(mCurPos.GetX()-1, mCurPos.GetY()));
    points.push_back(new Point(mCurPos.GetX()+1, mCurPos.GetY()));
    points.push_back(new Point(mCurPos.GetX(), mCurPos.GetY()-1));
    points.push_back(new Point(mCurPos.GetX(), mCurPos.GetY()+1));
    return points;
}

//============================= ACCESS     ===================================
void Character::Move(Point p)
{
    mCurPos.SetX(p.GetX());
    mCurPos.SetY(p.GetY());
}
void Character::SetHP(int value)
{
    mCurHP = value;
}
void Character::SetArmor(ArmorItem* item)
{
    mArmor = item;
}

void Character::SetWeapon(WeaponItem* item)
{
    if(mWeapon == NULL)
    {
        mAttributes[POW] = mAttributes[POW] + item->GetAttr();
        mWeapon = item;
    }
    else
    {
        mAttributes[POW] = mAttributes[POW] - mWeapon->GetAttr() + item->GetAttr();
        mWeapon = item;
    }
}
//============================= INQUIRY    ===================================
int Character::GetAttr(Attr value)
{
    return mAttributes[value];
}

int Character::GetHP()
{
    return mCurHP;
}

int Character::GetMaxHP()
{
    return mMaxHP;
}

Point Character::GetPoint()
{
    return mCurPos;
}

string Character::GetClassName()
{
    return "base";
}

ArmorItem* Character::GetArmor()
{
    return mArmor;
}

WeaponItem* Character::GetWeapon()
{
    return mWeapon;
}

string Character::GetName()
{
    return mName;
}

/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
