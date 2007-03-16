/**
 * A one line description of the class.
 *
 * #include "UIOverMapCursor.h"
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

#ifndef UIOverMapCursor_h
#define UIOverMapCursor_h

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <UIElement.h>
#include <UIOverMapTile.h>
#include <Point.h>

// LOCAL INCLUDES
//

// FORWARD REFERENCES
//


class UIOverMapCursor : public UIElement
{
public:
// LIFECYCLE

    /**
     * Default constructor.
	 */
    UIOverMapCursor(void);

    /**
     * Copy constructor.
	 *
	 * @param from The value to copy to this object.
	 */
    //UIOverMapCursor(const UIOverMapCursor& from);

    /**
     * Destructor.
	 */
    ~UIOverMapCursor(void);

// OPERATORS

    /**
     * Assignment operator.
	 *
	 * @param from The value to assign to this object.
	 *
	 * @return A reference to this object.
	 */
    //UIOverMapCursor&                     operator=(UIOverMapCursor& from);

// OPERATIONS


// ACCESS (writing)
    void SetCurTile(UIOverMapTile* nCurTile);

// INQUIRY (reading)
    UIOverMapTile* GetCurTile(void);


protected:
// PROTECTED VARIABLES
    Point mOffset;
    UIOverMapTile* mCurTile;

private:
// PRIVATE VARIABLES
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif  // _UIOverMapCursor_h_
