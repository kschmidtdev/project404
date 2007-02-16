/**
 * Defines basic item structure for armor/weapon to implement
 *
 * #include "Item.h"
 *
 * A longer description.
 *
 * Project 404 2007
 *
 * Authors:
 * Mike Malyuk, February 7, 2007 | Initial declaration
 */

#ifndef Item_h
#define Item_h

// SYSTEM INCLUDES
//
#include <string>
using namespace std;
// PROJECT INCLUDES
//

// LOCAL INCLUDES
//

// FORWARD REFERENCES
//


class Item
{
public:
// LIFECYCLE

    /**
     * Default constructor.
	 */
    Item(void)
    :mName("Base"), mValue(1)
    {};

    /**
     * Destructor.
	 */
    virtual ~Item(void);

// OPERATIONS
// ACCESS (writing)
// INQUIRY (reading)

    /**
     * Get attribute (power or def)
	 */
    int GetAttr();

    /**
     * Get name of item
	 */
    string GetName();

protected:
// PROTECTED VARIABLES
    string mName;
    int mValue;

private:
// PRIVATE VARIABLES
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif  // _Item_h_
