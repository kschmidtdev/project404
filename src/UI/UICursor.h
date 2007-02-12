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
 */

#ifndef UICursor_h
#define UICursor_h

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <UIElement.h>

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
     * Input constructor.
     */
    UICursor(const string filename, const string buttonHeading);

    /**
     * Destructor.
	 */
    ~UICursor(void);

// OPERATORS

// OPERATIONS

//virtual void RenderSelf(SDL_Surface* destination, Point offset);
// ACCESS (writing)
// INQUIRY (reading)

protected:
// PROTECTED VARIABLES
 //   int maxPosition;
 //   int curPosition;

private:
// PRIVATE VARIABLES
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif  // _UICursor_h_
