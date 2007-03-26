/**
 * A sub-class of Event Listener for UIElements.
 *
 * #include "UIEventListener.h"
 *
 * A sub-class of Event Listener for UIElements.
 *
 * @see EventListener
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, March 24 2007, Initial Creation
 * Karl Schmidt, March 25 2007 | Removed commented out methods :/
 */

#ifndef UIEventListener_h
#define UIEventListener_h

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <EventListener.h>

// LOCAL INCLUDES
//

// FORWARD REFERENCES
//


class UIEventListener : public EventListener
{
public:
// LIFECYCLE

    /**
     * Destructor.
	 */
    virtual ~UIEventListener(void) { };

// OPERATORS
// OPERATIONS

    /**
     * (Visually) Enables Element
     */
    virtual void Enable(void) { };

    /**
     * (Visually) Disables Element
     */
    virtual void Disable(void) { };

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

#endif  // _UIEventListener_h_
