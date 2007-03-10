/**
 * File: Character.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Mike Malyuk, February 7 2007  | Initial design
 * Mike Malyuk, February 11 2007 | Added DEF attr, Made CalcAction return non-pointer Point vector,
 *                                 Added Exhaust, Invigorate, Attack, MakeDead, GetExhaust, IsDead,
 *                                 and two booleans, mExhausted and mIsDead
 * Mike Malyuk, February 14 2007 | Changed attacking to cout important info. Changed Defence calc by dividing by 2
 *                               | Protected against dealing "negative damage" or healing the defender.
 * Mike Malyuk, February 14 2007 | Levelling up occurs at 100 exp now instead of greater than 100
 * Mike Malyuk, March 10 2007    | Added explicit cast so no warning, the int cutting is intentional
 */

#include <util.h>


#include "Character.h"                                // class implemented


/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

Character::Character()
:mName("GENERIC"), mLevel(1), mExp(0), mCurHP(10), mMaxHP(10),
mMaxActRange(0), mExhausted(false), mIsDead(false), mCurPos(Point(0,0)), mArmor(NULL), mWeapon(NULL)
{
    mAttributes[POW] = 0;
    mAttributes[AGI] = 0;
    mAttributes[DEF] = 0;
}
Character::~Character()
{

}// ~Character

//============================= OPERATIONS ===================================
void Character::LevelUp()
{
    mAttributes[POW] = mAttributes[POW] + 1;
    mAttributes[AGI] = mAttributes[AGI] + 1;
    mAttributes[DEF] = mAttributes[DEF] + 1;
    mLevel++;
}
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
    cout << "Attacking " << GetClassName() <<" (" << GetName() << ")'s HP:" << GetHP() << endl;
    cout << "Defending " << another->GetClassName() <<" (" << another->GetName() << ")'s HP:" << another->GetHP() << endl;
    bool killed = false;
    if(GetClassName() == "Knight")
    {
        if(mAttributes[POW] - (another->GetAttr(Character::DEF)/2) <= 0)
        {
            cout << "Attacking " << GetClassName() <<" (" << GetName() << ") did 0 damage" << endl;
        }
        else
        {
        another->SetHP(another->GetHP()-mAttributes[POW]+(another->GetAttr(Character::DEF)/2));
        cout << "Attacking " << GetClassName() <<" (" << GetName() << ") did " << mAttributes[POW]-(another->GetAttr(Character::DEF)/2) << " damage" << endl;
        }
        if(another->GetHP() <= 0)
        {
            cout << "Defender " << another->GetClassName() << " (" << another->GetName() <<  ") Dead" << endl;
            another->MakeDead();
            another->Exhaust();
            killed = true;
        }
        else
        {
            if(another->GetClassName() == "Knight")
            {
                if(another->GetAttr(Character::POW) - (mAttributes[DEF]/2) <= 0)
                {
                    cout << "Defending " << another->GetClassName() <<" (" << another->GetName() << ") did 0 damage" << endl;
                }
                else
                {
                cout << "Defending " << another->GetClassName() <<" (" << another->GetName() << ") did " << another->GetAttr(Character::POW) - (mAttributes[DEF]/2) << " damage" << endl;
                mCurHP = (mCurHP-another->GetAttr(Character::POW) + (mAttributes[DEF]/2));
                }
                if (mCurHP <= 0)
                {
                    cout << "Attacker " << GetClassName() << " (" << GetName() <<  ") Dead" << endl;
                    mIsDead = true;
                    mExhausted = true;
                }
            }
        }
    }
    else
    {
        if(mAttributes[POW] - (another->GetAttr(Character::DEF)/2) <= 0)
        {
            cout << "Attacking " << GetClassName() <<" (" << GetName() << ") did 0 damage" << endl;
        }
        else
        {
        another->SetHP(another->GetHP()-mAttributes[POW]+(another->GetAttr(Character::DEF)/2));
        cout << "Attacking " << GetClassName() <<" (" << GetName() << ") did " << mAttributes[POW]-(another->GetAttr(Character::DEF)/2) << " damage" << endl;
        }
        if(another->GetHP() <= 0)
        {
            cout << "Defender " << another->GetClassName() << " (" << another->GetName() <<  ") Dead" << endl;
            another->MakeDead();
            another->Exhaust();
            killed = true;
        }
    }
    if(killed == true)
    {
        mExp = (int)(mExp + ((another->GetLevel()*1.0)/mLevel)*100);
        if(mExp >= 100)
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
        mAttributes[DEF] = mAttributes[DEF] - mArmor->GetAttr() + item->GetAttr();
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
