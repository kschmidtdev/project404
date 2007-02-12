/**
 * File: Character.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Mike Malyuk, February 7 2007 | Initial design
 * Mike Malyuk, February 11 2007 | Added DEF attr, Made CalcAction return non-pointer Point vector,
 *                                 Added Exhaust, Invigorate, Attack, MakeDead, GetExhaust, IsDead,
 *                                 and two booleans, mExhausted and mIsDead
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
vector<Point> Character::CalcAction()
{
    vector<Point> points;
    points.push_back(Point(mCurPos.GetX()-1, mCurPos.GetY()));
    points.push_back(Point(mCurPos.GetX()+1, mCurPos.GetY()));
    points.push_back(Point(mCurPos.GetX(), mCurPos.GetY()-1));
    points.push_back(Point(mCurPos.GetX(), mCurPos.GetY()+1));
    return points;
}

void Character::Exhaust()
{
    mExhausted = true;
}

void Character::Invigorate()
{
    mExhausted = false;
}
void Character::MakeDead()
{
    mIsDead = true;
    mExhausted = true;
}
void Character::Attack(Character* another)
{
    bool killed = false;
    if(GetClassName() == "Knight")
    {
        another->SetHP(another->GetHP()-mAttributes[POW]+another->GetAttr(Character::DEF));
        if(another->GetHP() < 0)
        {
            cout << "Opponent dead" << endl;
            another->MakeDead();
            another->Exhaust();
            killed = true;
        }
        else
        {
            mCurHP = (mCurHP-another->GetAttr(Character::POW) + mAttributes[DEF]);
            if (mCurHP < 0)
            {
                mIsDead = true;
                mExhausted = true;
            }
        }
    }
    else
    {
        another->SetHP(another->GetHP()-mAttributes[DEF]+another->GetAttr(DEF));
        if(another->GetHP() < 0)
        {
            another->MakeDead();
            another->Exhaust();
            killed = true;
        }
    }
    if(killed == true)
    {
        mExp = ((another->GetLevel()*1.0)/mLevel)*100;
        if(mExp > 100)
        {
            LevelUp();
            mExp = mExp-100;
        }
    }
    mExhausted = true;
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
    if(mArmor == NULL)
    {
        mAttributes[DEF] = mAttributes[DEF] + item->GetAttr();
        mArmor = item;
    }
    else
    {
        mAttributes[DEF] = mAttributes[DEF] - mWeapon->GetAttr() + item->GetAttr();
        mArmor = item;
    }
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

bool Character::GetExhaust()
{
    return mExhausted;
}

bool Character::IsDead()
{
    return mIsDead;
}

int Character::GetLevel()
{
    return mLevel;
}

int Character::GetExp()
{
    return mExp;
}
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
