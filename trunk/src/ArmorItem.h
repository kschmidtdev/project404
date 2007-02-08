/**
 * Inherited from item, defines defense of unit
 *
 * #include "ArmorItem.h"
 *
 * @see Item.h
 *
 * Project 404 2007
 *
 * Authors:
 * Mike Malyuk, February 7, 2007 | Initial declaration
 */

#ifndef ArmorItem_h
#define ArmorItem_h

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include "Item.h"
// LOCAL INCLUDES
//

// FORWARD REFERENCES
//


class ArmorItem : public Item
{
public:
// LIFECYCLE

    /**
     * Default constructor.
	 */
    ArmorItem(void);

    /**
     * Constructor
	 */
    ArmorItem(string name, int attr);


    /**
     * Destructor.
	 */
    ~ArmorItem(void);

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

#endif  // _ArmorItem_h_
