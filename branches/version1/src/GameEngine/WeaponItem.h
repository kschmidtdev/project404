/**
 * Inherited from item, defines attack bonus of unit
 *
 * #include "WeaponItem.h"
 *
 * @see Item.h
*
 * Project 404 2007
 *
 * Authors:
 * Mike Malyuk, February 7 2007 | Initial declaration
 */

#ifndef WeaponItem_h
#define WeaponItem_h

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include "Item.h"
// LOCAL INCLUDES
//

// FORWARD REFERENCES
//


class WeaponItem : public Item
{
public:
// LIFECYCLE

    /**
     * Default constructor.
	 */
    WeaponItem(void);

    /**
     * Constructor
	 */
    WeaponItem(string name, int attr);

    /**
     * Destructor.
	 */
    virtual ~WeaponItem(void);
// OPERATIONS
// ACCESS (writing)
// INQUIRY (reading)

protected:
// PROTECTED VARIABLES
private:
// PRIVATE VARIABLES
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif  // _WeaponItem_h_
