/**
 * A simple EventListener for demonstration
 *
 * #include "ExampleEventListener.h"
 *
 * A simple implementation of an EventListener,
 * which listens for CONFIRM presses.
 *
 * @see EventListener, InputManager
 *
 * Project 404 2007
 *
 * Authors:
 * Karl Schmidt, February 9 2007 | Initial creation of header
 */

#ifndef ExampleEventListener_h
#define ExampleEventListener_h

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include "EventListener.h"
#include "Logger.h"

// LOCAL INCLUDES
//

// FORWARD REFERENCES
//


class ExampleEventListener : public EventListener
{
public:
// LIFECYCLE

    /**
     * Default constructor.
	 */
    ExampleEventListener(void)
    { };

// OPERATORS
// OPERATIONS

    /**
     * Listens for CONFIRM presses, and logs
     * a critical error to the log when it receives one
     * (for testing purposes)
	 */
    void ProcessEvent( const InputManager::INPUTKEYS evt )
    {
        if( evt == InputManager::CONFIRM )
        {
            LogCritical( "You pressed CONFIRM!" );
        }
    }

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

#endif  // _ExampleEventListener_h_
