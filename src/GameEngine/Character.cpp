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
 * Karl Schmidt, March 22 2007   | More include re-arranging, fixed some warnings
 * Karl Schmidt, March 22 2007   | Changed name of GetClassName
 * Mike Malyuk, March 24 2007    | Added code to call RTAudio proof of concept trumpet sound on attack. Prepare for annoyance!
 * Mike Malyuk, April 1  2007    | RTAudio rejiggered, sounds nicer, now sets whether attack is from left or right.
 * Mike Malyuk, April 2  2007    | Dynamic sound introduced. Attack sound varies on damage.
 * Mike Malyuk, April 5  2007    | Added two new functions RevertOld() and SetOldPos, to allow reverting state on moves for users.
 */

#include "Character.h"                                // class implemented

#include <util.h>
#include "SoundManager.h"
#include <cstdlib>
#include <ctime>
#include <cmath>

namespace
{
    const std::string characterClassName = "base";
}

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
        randPOW = static_cast<int>( randPOW*1.5 );
    }
    else
    {
        randPOW = (rand()%5-2) + mAttributes[POW];
    }
    cout << "Attacking " << GetCharacterClassName() <<" (" << GetName() << ")'s HP:" << GetHP() << endl;
    cout << "Defending " << another->GetCharacterClassName() <<" (" << another->GetName() << ")'s HP:" << another->GetHP() << endl;
    if(GetCharacterClassName() == "Knight")
    {
        if(randPOW - (another->GetAttr(Character::DEF)/2) <= 0)
        {
            cout << "Attacking " << GetCharacterClassName() <<" (" << GetName() << ") did 0 damage" << endl;
        }
        else
        {
        another->SetHP(another->GetHP()-randPOW+(another->GetAttr(Character::DEF)/2));
        cout << "Attacking " << GetCharacterClassName() <<" (" << GetName() << ") did " << randPOW-(another->GetAttr(Character::DEF)/2) << " damage" << endl;
        }
        if(another->GetHP() <= 0)
        {
            cout << "Defender " << another->GetCharacterClassName() << " (" << another->GetName() <<  ") Dead" << endl;
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
            if(another->GetCharacterClassName() == "Knight")
            {
                if(rand()%(100/(another->GetAttr(Character::AGI)/3)) == 0)
                    {
                        randPOW = (rand()%5-2) + another->GetAttr(Character::POW);
                        randPOW = static_cast<int>( randPOW*1.5 );
                    }
                    else
                    {
                        randPOW = (rand()%5-2) + another->GetAttr(Character::POW);
                    }
                if(randPOW - (mAttributes[DEF]/2) <= 0)
                {
                    cout << "Defending " << another->GetCharacterClassName() <<" (" << another->GetName() << ") did 0 damage" << endl;
                }
                else
                {
                cout << "Defending " << another->GetCharacterClassName() <<" (" << another->GetName() << ") did " << randPOW - (mAttributes[DEF]/2) << " damage" << endl;
                mCurHP = (mCurHP-randPOW + (mAttributes[DEF]/2));
                }
                if (mCurHP <= 0)
                {
                    cout << "Attacker " << GetCharacterClassName() << " (" << GetName() <<  ") Dead" << endl;
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
            cout << "Attacking " << GetCharacterClassName() <<" (" << GetName() << ") did 0 damage" << endl;
        }
        else
        {
        another->SetHP(another->GetHP()-randPOW+(another->GetAttr(Character::DEF)/2));
        cout << "Attacking " << GetCharacterClassName() <<" (" << GetName() << ") did " << randPOW-(another->GetAttr(Character::DEF)/2) << " damage" << endl;
        }
        if(another->GetHP() <= 0)
        {
            cout << "Defender " << another->GetCharacterClassName() << " (" << another->GetName() <<  ") Dead" << endl;
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

    if(mCurPos.GetX() < another->GetPoint().GetX())
        {
            SoundManager::GetInstance()->SetLeft(true);
        }
        else
        {
            SoundManager::GetInstance()->SetLeft(false);
        }
        if(GetCharacterClassName() != "Mage")
        {
//            SoundManager::GetInstance()->SetSoundArray((randPOW-(another->GetAttr(Character::DEF)/2))/150.0);
            SoundManager::GetInstance()->PlayRTAUDIO();
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

void Character::SetOldPos(const Point & p) {mOldPos = p;}

void Character::RevertOld(){mCurPos = mOldPos;}

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

const inline std::string & Character::GetCharacterClassName() const
{
    return characterClassName;
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
