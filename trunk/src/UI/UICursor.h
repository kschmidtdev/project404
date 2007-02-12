/**
 * A one line description of the class.
 *
 * #include "UICursor.h"
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
