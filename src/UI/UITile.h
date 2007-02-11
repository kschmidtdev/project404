/**
 * A one line description of the class.
 *
 * #include "UITile.h"
 *
 * A longer description.
 *
 * @see something
 *
 * Project 404 2007
 *
 * Authors:
 * Name, Date (Month Day Year), What was done
 */

#ifndef UITile_h
#define UITile_h

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <UIElement.h>

// LOCAL INCLUDES
//

// FORWARD REFERENCES
//


class UITile : public UIElement
{
public:
// LIFECYCLE

    /**
     * Default constructor.
	 */
    UITile(void);

    /**
     * Copy constructor.
	 *
	 * @param from The value to copy to this object.
	 */
    UITile(const UITile& from);

    /**
     * Destructor.
	 */
    ~UITile(void);

// OPERATORS

    /**
     * Assignment operator.
	 *
	 * @param from The value to assign to this object.
	 *
	 * @return A reference to this object.
	 */
    UITile&                     operator=(UITile& from);

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

#endif  // _UITile_h_
