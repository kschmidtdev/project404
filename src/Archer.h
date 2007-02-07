/**
 * Subclass of character for Archer type
 *
 * #include "Archer.h"
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

#ifndef Archer_h
#define Archer_h

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include "Character.h"
// LOCAL INCLUDES
//

// FORWARD REFERENCES
//


class Archer : public Character
{
public:
// LIFECYCLE

    /**
     * Default constructor.
 	*/
    Archer(void);

    /**
     * Constructor
     */
    Archer(string name, level, weapon, armor);

    /**
     * Destructor.
	 */
    ~Archer(void);

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
private:
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif  // _Archer_h_
