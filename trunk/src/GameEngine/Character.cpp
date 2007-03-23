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
 * Mike Malyuk, March 15 2007    | Fixed Levelling up! yay!
 * Karl Schmidt, March 20 2007   | Major adding of consts and reference usage, rearranging includes
 */

#include <util.h>

#include <cstdlib>
#include <ctime>
#include <cmath>

#include "Character.h"                                // class implemented


/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

Character::Character()
:mName("GENERIC"), mLevel(1), mExp(0), mCurHP(10), mMaxHP(10),
mMaxActRange(0), mExhausted(false), mIsDead(false), mTarget(NULL), mCurPos(Point(0,0)), mArmor(NULL), mWeapon(NULL)
{
    mAttributes[POW] = 0;
    mAttributes[AGI] = 3;
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
const PointVec Character::CalcAction()
{
    PointVec points;
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
    int randPOW;
    if(rand()%(100/(mAttributes[AGI]/3)) == 0)
    {
        randPOW = (rand()%5-2) + mAttributes[POW];
        randPOW = randPOW*1.5;
    }
    else
    {
        randPOW = (rand()%5-2) + mAttributes[POW];
    }
    cout << "Attacking " << GetClassName() <<" (" << GetName() << ")'s HP:" << GetHP() << endl;
    cout << "Defending " << another->GetClassName() <<" (" << another->GetName() << ")'s HP:" << another->GetHP() << endl;
    if(GetClassName() == "Knight")
    {
        if(randPOW - (another->GetAttr(Character::DEF)/2) <= 0)
        {
            cout << "Attacking " << GetClassName() <<" (" << GetName() << ") did 0 damage" << endl;
        }
        else
        {
        another->SetHP(another->GetHP()-randPOW+(another->GetAttr(Character::DEF)/2));
        cout << "Attacking " << GetClassName() <<" (" << GetName() << ") did " << randPOW-(another->GetAttr(Character::DEF)/2) << " damage" << endl;
        }
        if(another->GetHP() <= 0)
        {
            cout << "Defender " << another->GetClassName() << " (" << another->GetName() <<  ") Dead" << endl;
            another->MakeDead();
            another->Exhaust();
            mExp = (int)(mExp + ((another->GetLevel()*1.0)/mLevel)*100);
            if(mExp >= 100)
            {
                int multi = mExp/100;
                for(int i = 0; i < multi; i++)
                {
                    LevelUp();
                }
                mExp = mExp-100*multi;
            }
        }
        else
        {
            if(another->GetClassName() == "Knight")
            {
                if(rand()%(100/(another->GetAttr(Character::AGI)/3)) == 0)
                    {
                        randPOW = (rand()%5-2) + another->GetAttr(Character::POW);
                        randPOW = randPOW*1.5;
                    }
                    else
                    {
                        randPOW = (rand()%5-2) + another->GetAttr(Character::POW);
                    }
                if(randPOW - (mAttributes[DEF]/2) <= 0)
                {
                    cout << "Defending " << another->GetClassName() <<" (" << another->GetName() << ") did 0 damage" << endl;
                }
                else
                {
                cout << "Defending " << another->GetClassName() <<" (" << another->GetName() << ") did " << randPOW - (mAttributes[DEF]/2) << " damage" << endl;
                mCurHP = (mCurHP-randPOW + (mAttributes[DEF]/2));
                }
                if (mCurHP <= 0)
                {
                    cout << "Attacker " << GetClassName() << " (" << GetName() <<  ") Dead" << endl;
                    mIsDead = true;
                    mExhausted = true;
                    (*another).mExp = (int)((*another).mExp + ((GetLevel()*1.0)/ (*another).mLevel)*100);
                    if((*another).mExp >= 100)
                    {
                    int multi = (*another).mExp/100;
                    for(int i = 0; i < multi; i++)
                    {
                        (*another).LevelUp();
                    }
                    (*another).mExp = (*another).mExp-100*multi;
                    }
                }
            }
        }
    }
    else
    {
        if(randPOW - (another->GetAttr(Character::DEF)/2) <= 0)
        {
            cout << "Attacking " << GetClassName() <<" (" << GetName() << ") did 0 damage" << endl;
        }
        else
        {
        another->SetHP(another->GetHP()-randPOW+(another->GetAttr(Character::DEF)/2));
        cout << "Attacking " << GetClassName() <<" (" << GetName() << ") did " << randPOW-(another->GetAttr(Character::DEF)/2) << " damage" << endl;
        }
        if(another->GetHP() <= 0)
        {
            cout << "Defender " << another->GetClassName() << " (" << another->GetName() <<  ") Dead" << endl;
            another->MakeDead();
            another->Exhaust();
            mExp = (int)(mExp + ((another->GetLevel()*1.0)/mLevel)*100);
            if(mExp >= 100)
            {
                int multi = mExp/100;
                for(int i = 0; i < multi; i++)
                {
                    LevelUp();
                }
                mExp = mExp-100*multi;
            }
        }
    }
    mExhausted = true;
}
//============================= ACCESS     ===================================
void Character::Move( const Point & p)
{
    mCurPos.SetX(p.GetX());
    mCurPos.SetY(p.GetY());
}
void Character::SetHP( const int value)
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

void Character::SetTarget(Character* target)
{
    mTarget = target;
}

void Character::RestoreToFullLife()
{
    Invigorate();
    SetHP( mMaxHP );
    mIsDead = false;
}

//============================= INQUIRY    ===================================
const int Character::GetAttr( const Attr value) const
{
    return mAttributes[value];
}

const int Character::GetHP() const
{
    return mCurHP;
}

const int Character::GetMaxHP() const
{
    return mMaxHP;
}

const Point& Character::GetPoint() const
{
    return mCurPos;
}

const string Character::GetClassName() const
{
    return "base";
}

ArmorItem* Character::GetArmor() const
{
    return mArmor;
}

WeaponItem* Character::GetWeapon() const
{
    return mWeapon;
}

const string & Character::GetName() const
{
    return mName;
}

const bool Character::GetExhaust() const
{
    return mExhausted;
}

const bool Character::IsDead() const
{
    return mIsDead;
}

const int Character::GetLevel() const
{
    return mLevel;
}

const int Character::GetExp() const
{
    return mExp;
}

Character* Character::GetTarget() const
{
    return mTarget;
}
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
