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
    virtual vector<Point> CalcAction();

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
    void Move(Point p);

    /**
     * Set value of HP (damage)
	 */
    void SetHP(int value);

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

// INQUIRY

    /**
     * Get specified character attributes (use for calculations)
	 */
    int GetAttr(Attr value);

    /**
     * Get value of HP (for damage)
	 */
    int GetHP();

    /**
     * Get total possible HP
	 */
    int GetMaxHP();
    /**
     * Get point currently at (used for move)
	 */
    Point GetPoint();

    /**
     * Get name of class (for UI stuff, or limiting weapons)
	 */
    virtual string GetClassName();

    /**
     * Get Armor (for UI representation)
	 */
    ArmorItem* GetArmor();

    /**
     * Get Weapon (for UI representation)
	 */
    WeaponItem* GetWeapon();

    /**
     * Get name of character (for UI)
	 */
    string GetName();

    /**
     * Get exhausted status of character
	 */
    bool GetExhaust();

    /**
     * Get dead status of character
	 */
    bool IsDead();

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
