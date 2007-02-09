/**
 * An abstract class for EventListeners
 *
 * #include "EventListener.h"
 *
 * A class to inherit from when you have
 * an object you want to register with the InputManager
 * to receive event information, basically key presses
 *
 * @see InputManager
 *
 * Project 404 2007
 *
 * Authors:
 * Karl Schmidt, February 9 2007 | Initial creation of the header
 */

#ifndef EventListener_h
#define EventListener_h

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include "InputManager.h"

// LOCAL INCLUDES
//

// FORWARD REFERENCES
//

class EventListener
{
public:
// LIFECYCLE

    /**
    * Does something with a key press, to be
    * determined by the inheriting classes
    */
    virtual void ProcessEvent( const InputManager::INPUTKEYS evt ) = 0;

    /**
    * Destructor
    */
    virtual ~EventListener() { };

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

#endif  // _EventListener_h_
