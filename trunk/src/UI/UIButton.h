/**
 * The base class for a button element on screen
 *
 * #include "UIButton.h"
 *
 * The only addition feature of a button element will be a constructor that allows for the passed string to be seen
 * on the button
 *
 * @see UIMenu
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, February 11 2007 | Initial Creation
 */

#ifndef UIButton_h
#define UIButton_h

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <UIElement.h>

// LOCAL INCLUDES
//

// FORWARD REFERENCES
//


class UIButton : public UIElement
{
public:
// LIFECYCLE

    /**
     * Default constructor.
	 */
    UIButton(void);




    /**
     * Destructor.
	 */
    ~UIButton(void);

// OPERATORS

    /**
     * Assignment operator.
	 *
	 * @param from The value to assign to this object.
	 *
	 * @return A reference to this object.
	 */
    UIButton&                     operator=(UIButton& from);

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

#endif  // _UIButton_h_
