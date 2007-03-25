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
     * Default constructor.
	 */
    //UIEventListener(void) { };

    /**
     * Copy constructor.
	 *
	 * @param from The value to copy to this object.
	 */
    //UIEventListener(const UIEventListener& from);

    /**
     * Destructor.
	 */
    virtual ~UIEventListener(void) { };

// OPERATORS

    /**
     * Assignment operator.
	 *
	 * @param from The value to assign to this object.
	 *
	 * @return A reference to this object.
	 */
    //UIEventListener&                     operator=(UIEventListener& from);

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
