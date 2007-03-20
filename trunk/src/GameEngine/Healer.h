/**
 * Subclass of character for Healer type
 *
 * #include "Healer.h"
 *
 * Has personalization for level up and weapon ranges
 *
 * @see Character.h
 *
 * Project 404 2007
 *
 * Authors:
 * Mike Malyuk, February 7 2007 | Initial design
 * Mike Malyuk, February 11 2007 | Made CalcAction return non-pointer Point vector
 * Mike Malyuk, February 14 2007 | Added Heal function
 * Karl Schmidt, March 20 2007   | Major adding of consts and reference usage, rearranging includes
 */

#ifndef Healer_h
#define Healer_h

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include "Character.h"
// LOCAL INCLUDES
//

// FORWARD REFERENCES
//


class Healer : public Character
{
public:
// LIFECYCLE

    /**
     * Default constructor.
	 */
    Healer(void);

    /**
     * Constructor
     */
    Healer( const string & name, const int level, WeaponItem* weapon, ArmorItem* armor);

    /**
     * Destructor.
	 */
    ~Healer(void);

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
     * Healer specific healing
     */
     void Heal(Character* buddy);

// ACCESS
// INQUIRY

    /**
     * Get name of class (for UI stuff, or limiting weapons)
	 */
    virtual const string GetClassName() const;


protected:
// PROTECTED VARIABLES
private:
// PRIVATE VARIABLES
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif  // _Healer_h_
