/**
 * Subclass of character for Knight type
 *
 * #include "Knight.h"
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
 */

#ifndef Knight_h
#define Knight_h

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include "Character.h"
// LOCAL INCLUDES
//

// FORWARD REFERENCES
//


class Knight : public Character
{
public:
// LIFECYCLE

    /**
     * Default constructor.
	 */
    Knight(void);

    /**
     * Constructor
     */
    Knight(string name, int level, WeaponItem* weapon, ArmorItem* armor);

    /**
     * Destructor.
	 */
    ~Knight(void);

// OPERATIONS

    /**
     * Controls attributes of character when it levels up
	 */
    virtual void LevelUp();

    /**
     * Returns array of Points a character may have action on
	 */
    virtual vector<Point> CalcAction();
// ACCESS

// INQUIRY

    /**
     * Get name of class (for UI stuff, or limiting weapons)
	 */
    virtual string GetClassName();

protected:
// PROTECTED VARIABLES
private:
// PRIVATE VARIABLES
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif  // _Knight_h_
