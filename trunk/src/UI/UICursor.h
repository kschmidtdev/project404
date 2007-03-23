/**
 * The UI class representation of a cursor on screen
 *
 * #include "UICursor.h"
 *
 * The UI class representation of a cursor on screen
 *
 * @see UIMenu
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, February 11 2007, Initial Creation
 * Andrew Osborne, March 18 2007, Re-initialized class for use, added UpdatePos and SetAttach methods
 * Karl Schmidt, March 22 2007      | Correcting include orders and paths
 */

#ifndef UICursor_h
#define UICursor_h

// SYSTEM INCLUDES
//
#include <string>

// PROJECT INCLUDES
//
#include <UI/UIElement.h>

// LOCAL INCLUDES
//

// FORWARD REFERENCES
//


class UICursor : public UIElement
{
public:
// LIFECYCLE

    /**
     * Default constructor.
	 */
    UICursor(void);

    /**
     * image file constructor.
	 */
    UICursor( const std::string & filename, const Point & point, UIElement* start );

    /**
     * Destructor.
	 */
    ~UICursor(void);

// OPERATORS

// OPERATIONS

    /**
     * Update Position.
	 */
    void UpdatePos(void);

// ACCESS (writing)

    /**
     * Set New center Element.
	 */
    void SetAttach(UIElement* e);


// INQUIRY (reading)

protected:
// PROTECTED VARIABLES
    UIElement* mAttach;
    Point mOffset;

private:
// PRIVATE VARIABLES
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif  // _UICursor_h_
