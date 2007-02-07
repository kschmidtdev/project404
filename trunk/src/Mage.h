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
 * Mike Malyuk, February 7 2007 | Initial design
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
    Mage(string name, level, weapon, armor);

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
    virtual Point[] CalcAction();
// ACCESS

    /**
     * Move Character to new position
	 */
    virtual void Move(Point p);
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

#endif  // _Mage_h_
