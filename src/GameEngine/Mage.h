/**
 * Subclass of character for Mage type
 *
 * #include "Mage.h"
 *
 * Has personalization for level up and weapon ranges
 *
 * @see Character.h
 *
 * Project 404 2007
 *
 * Authors:
 * Mike Malyuk, February 7 2007  | Initial design
 * Mike Malyuk, February 11 2007 | Made CalcAction return non-pointer Point vector
 * Karl Schmidt, March 20 2007   | Major adding of consts and reference usage, rearranging includes
 * Karl Schmidt, March 22 2007   | Changed name of GetClassName
 */

#ifndef Mage_h
#define Mage_h

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include "Character.h"
// LOCAL INCLUDES
//

// FORWARD REFERENCES
//


class Mage : public Character
{
public:
// LIFECYCLE

    /**
     * Default constructor.
	 */
    Mage(void);

    /**
     * Constructor
     */
    Mage( const string & name, const int level, WeaponItem* weapon, ArmorItem* armor);

    /**
     * Destructor.
	 */
    ~Mage(void);

// OPERATIONS

    /**
     * Controls attributes of character when it levels up
	 */
    virtual void LevelUp();

    /**
     * Returns array of Points a character may have action on
	 */
    virtual const PointVec CalcAction();
// ACCESS

// INQUIRY

    /**
     * Get name of class (for UI stuff, or limiting weapons)
	 */
    virtual const string & GetCharacterClassName() const;

protected:
// PROTECTED VARIABLES
private:
// PRIVATE VARIABLES
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif  // _Mage_h_
