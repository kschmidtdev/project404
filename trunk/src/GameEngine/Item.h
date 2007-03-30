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
 * Mike Malyuk, March 27, 2007   | Added cost
 * Andrew Osborne, March 29, 2007 | Added mType attribute, ITEM_TYPE enum, and GetType method
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

enum ITEM_TYPE
{
    BASE = 0,
    ARMOR,
    WEAPON
};

// LIFECYCLE

    /**
     * Default constructor.
	 */
    Item(void)
    :mName("Base"), mValue(1), mCost(0), mType(Item::BASE)
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

    /**
     * Get Type
     */
    ITEM_TYPE GetType(void) { return mType; }

    /**
     * Get cost of item
	 */
    int GetCost(){ return mCost;};
protected:
// PROTECTED VARIABLES
    string mName;
    int mValue;
    int mCost;
    ITEM_TYPE mType;

private:
// PRIVATE VARIABLES
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif  // _Item_h_
