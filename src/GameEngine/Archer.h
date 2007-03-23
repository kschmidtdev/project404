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
 * Mike Malyuk, February 7 2007  | Initial design
 * Mike Malyuk, February 11 2007 | Made CalcAction return non-pointer Point vector
 * Karl Schmidt, March 20 2007   | Major adding of consts and reference usage, rearranging includes
 * Karl Schmidt, March 22 2007   | Changed name of GetClassName
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
    Archer( const string & name, const int level, WeaponItem* weapon, ArmorItem* armor);

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
    virtual const PointVec CalcAction();

// INQUIRY

    /**
     * Get name of class (for UI stuff, or limiting weapons)
	 */
    virtual const std::string & GetCharacterClassName() const;

protected:
private:
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif  // _Archer_h_
