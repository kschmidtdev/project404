/**
 * Handler of all user input events
 *
 * #include "InputManager.h"
 *
 * Handles receiving input events from SDL,
 * and passing them out to registered listeners
 *
 * Project 404 2007
 *
 * Authors:
 * Karl Schmidt, February 7 2007, Initial creation of the header
 */

#ifndef InputManager_h
#define InputManager_h

// SYSTEM INCLUDES
//
#include "SDL.h"
#include <vector>

// PROJECT INCLUDES
//

// LOCAL INCLUDES
//

// FORWARD REFERENCES
//
class EventListener;

// TYPEDEFS
//
typedef vector<EventListener*> EventListenerVec;
typedef EventListener::iterator EventListenerItr;

class InputManager
{
public:
// ENUMS
enum INPUTKEYS
{
    UP = 0,
    LEFTUP,
    LEFT,
    LEFTDOWN,
    DOWN,
    RIGHTDOWN,
    RIGHT,
    RIGHTUP,
    START,
    SELECT,
    CONFIRM,
    CANCEL,
    MENU,
    KEYCOUNT
}

// LIFECYCLE

    /**
    * Returns an instance of the inputmanager
    */
    static InputManager* getInstance();

    /**
    * Destructor.
    */
    virtual ~InputManager(void);

    /**
    * Initializes SDL and the manager
    * for receiving input, must be called
    * after instantiation and before
    * other methods
    */
    void Initialize();

    /**
    * Shuts the input manager down,
    * performs SDL cleanup and other
    * cleanup operations
    */
    void Shutdown();

// OPERATIONS

    /**
    * Adds an eventlistener to the current
    * list of registered listeners
    */
    void AddEventListener( EventListener* toAdd );

    /**
    * Removes the particular listener
    * from the list of registered listeners
    */
    void RemoveEventListener( EventListener* toRemove );

    /**
    * Determines how to deal with the input
    * event, may broadcast to listeners
    */
    void ProcessEvent( SDLEvent* evt );

// ACCESS (writing)
// INQUIRY (reading)

protected:
// PROTECTED METHODS
    /**
    * Default constructor.
    */
    InputManager(void);

    /**
    * Sets up the keys correctly depending
    * on if we are using keyboard or joystick
    * input
    */
    void SetupKeyBindings();

// PROTECTED VARIABLES
    static InputManager* _instance;
    int mKeys[KEY_COUNT];
    EventListenerVec mRegisteredListeners;

private:
// PRIVATE VARIABLES
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif  // _InputManager_h_
