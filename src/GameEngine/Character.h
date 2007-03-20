/**
 * Defines one instance of a generic character in game
 *
 * #include "Character.h"
 *
 * Character class will contain the bear necessities for
 * constructing a character, while the actual work will
 * be done by subclasses.
 *
 * Project 404 2007
 *
 * Authors:
 * Mike Malyuk, February 7 2007  | Initial design
 * Mike Malyuk, February 11 2007 | Added DEF attr, Made CalcAction return non-pointer Point vector,
 *                                 Added Exhaust, Invigorate, Attack, MakeDead, GetExhaust, IsDead,
 *                                 and two booleans, mExhausted and mIsDead
 * Karl Schmidt, March 20 2007   | Major adding of consts and reference usage, rearranging includes
 */

#ifndef Character_h
#define Character_h

// SYSTEM INCLUDES
//
#include <string>
#include <iostream>
#include <vector>
using namespace std;
// PROJECT INCLUDES
//
#include "ArmorItem.h"
#include "WeaponItem.h"
#include "Point.h"
// LOCAL INCLUDES
//

// FORWARD REFERENCES
//

typedef std::vector<Point> PointVec;
typedef PointVec::iterator PointItr;
typedef PointVec::const_iterator PointConstItr;

class Character
{
public:

//ENUMS
enum Attr
    {
        POW = 0,
        AGI,
        DEF,
        ATTR_COUNT
    };
// LIFECYCLE

    /**
     * Default constructor.
	 */
    Character(void);

    /**
     * Destructor.
	 */
    virtual ~Character(void);

// OPERATIONS
    /**
     * Controls attributes of character when it levels up
	 */
    virtual void LevelUp();

    /**
     * Returns array of Points a character may have action on
	 */
    virtual const PointVec CalcAction();

    /**
     * Set character to exhausted, done moving or attack
	 */
    void Exhaust();

    /**
     * Reset characters exhausted state
	 */
    void Invigorate();

    /**
     * Attack another character
	 */
    void Attack(Character* another);

// ACCESS

    /**
     * Move Character to new position
	 */
    void Move( const Point & p );

    /**
     * Set value of HP (damage)
	 */
    void SetHP( const int value);

    /**
     * Set value of Armor (new equips)
	 */
    void SetArmor(ArmorItem* item);

    /**
     * Set value of Weapon (new equips)
	 */
    void SetWeapon(WeaponItem* item);

    /**
     * Kill this character so the game knows it is dead
     */
    void MakeDead();

    /**
     * SetTarget for AI
     */
    void SetTarget(Character* target);

    /**
     * Set health to max, make undead if dead, invigorate
	 */
    void RestoreToFullLife();

// INQUIRY

    /**
     * Get specified character attributes (use for calculations)
	 */
    const int GetAttr(Attr value) const;

    /**
     * Get value of HP (for damage)
	 */
    const int GetHP() const;

    /**
     * Get total possible HP
	 */
    const int GetMaxHP() const;
    /**
     * Get point currently at (used for move)
	 */
    const Point & GetPoint() const;

    /**
     * Get name of class (for UI stuff, or limiting weapons)
	 */
    virtual const string GetClassName() const;

    /**
     * Get Armor (for UI representation)
	 */
    ArmorItem* GetArmor() const;

    /**
     * Get Weapon (for UI representation)
	 */
    WeaponItem* GetWeapon() const;

    /**
     * Get name of character (for UI)
	 */
    const string& GetName() const;

    /**
     * Get exhausted status of character
	 */
    const bool GetExhaust() const;

    /**
     * Get dead status of character
	 */
    const bool IsDead() const;

    /**
     * Get Level of character
	 */
    const int GetLevel() const;

    /**
     * Get Exp of character
	 */
    const int GetExp() const;

    /**
     * Get target (AI)
	 */
    Character* GetTarget() const;

protected:

// VARIABLES
    string mName;
    int mLevel;
    int mExp;
    int mCurHP;
    int mMaxHP;
    int mAttributes[ATTR_COUNT];
    int mMaxActRange;
    bool mExhausted;
    bool mIsDead;
    Character* mTarget;
    Point mCurPos;
    ArmorItem* mArmor;
    WeaponItem* mWeapon;

private:
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif  // _Character_h_
