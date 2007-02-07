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


class Knight
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
    Knight(string name, level, weapon, armor);

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

#endif  // _Knight_h_
