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
 * Karl Schmidt, March 22 2007      | Correcting include orders and paths
 */

#ifndef UIOverMapCursor_h
#define UIOverMapCursor_h

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <UI/UIElement.h>
#include <Point.h>

// LOCAL INCLUDES
//

// FORWARD REFERENCES
//
class UIOverMapTile;

class UIOverMapCursor : public UIElement
{
public:
// LIFECYCLE

    /**
     * Default constructor.
	 */
    UIOverMapCursor(void);

    /**
     * Destructor.
	 */
    ~UIOverMapCursor(void);

// OPERATORS
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
