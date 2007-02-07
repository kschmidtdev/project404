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
 * Mike Malyuk, February 7 2007 | Initial design
 */

#ifndef Character_h
#define Character_h

// SYSTEM INCLUDES
//
#include <string>
using namespace std;
// PROJECT INCLUDES
//
#include "ArmorItem.h"
#include "WeaponItem.h"
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
        ATTR_COUNT
    }
// LIFECYCLE

    /**
     * Default constructor.
	 */
    virtual Character(void) = 0;

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
    virtual Point[] CalcAction();

// ACCESS

    /**
     * Move Character to new position
	 */
    virtual void Move(Point p);

    /**
     * Set value of HP (damage)
	 */
    void SetHP(int value);

    /**
     * Set value of Armor (new equips)
	 */
    void SetArmor(ArmorItem item);

    /**
     * Set value of Weapon (new equips)
	 */
    void SetWeapon(WeaponItem item);


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
     * Get point currently at (used for move)
	 */
    int GetPoint();

    /**
     * Get name of class (for UI stuff, or limiting weapons)
	 */
    virtual string GetClassName();

    /**
     * Get Armor (for UI representation)
	 */
    const ArmorItem& GetArmor();

    /**
     * Get Weapon (for UI representation)
	 */
    const WeaponItem& GetWeapon();

    /**
     * Get name of character (for UI)
	 */
    string GetName();

protected:

// VARIABLES
    string mName;
    int mLevel;
    int mExp;
    int mHP;

    int mAttributes[ATTR_COUNT];
    int mMaxActRange;
    Point mCurPos;
    ArmorItem mArmor;
    WeaponItem mWeapon;

private:
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif  // _Character_h_
