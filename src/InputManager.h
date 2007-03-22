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
 * Karl Schmidt, February 13 2007 | Added joystick support
 * Karl Schmidt, February 12 2007 | Added inline function for sending events to listeners
 * Karl Schmidt, February 9 2007  | Fixed minor issues (so it could compile)
 * Karl Schmidt, February 7 2007  | Initial creation of the header
 * Karl Schmidt, March 14 2007    | Added event recording/playback support
 * Karl Schmidt, March 15 2007    | Made an attempt to fix event recording/playback, still not acting right
 * Karl Schmidt, March 21 2007    | Added directional-key auto-repeat, storing/loading rand seed in key recording file
 */

#ifndef InputManager_h
#define InputManager_h

// SYSTEM INCLUDES
//
#include <vector>
#include <string>

#include <SDL.h>

// PROJECT INCLUDES
//

// LOCAL INCLUDES
//

// FORWARD REFERENCES
//
class EventListener;

// TYPEDEFS
//
typedef std::vector<EventListener*> EventListenerVec;
typedef EventListenerVec::iterator EventListenerItr;

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
    LAST_DIRECTION = RIGHTUP,
    START,
    SELECT,
    CONFIRM,
    CANCEL,
    MENU,
    KEYCOUNT
};

typedef std::vector<int> KeyVec;
typedef KeyVec::iterator KeyVecItr;

enum INPUT_MODE
{
    NORMAL = 0,
    RECORDING,
    PLAYBACK
};

// LIFECYCLE

    /**
    * Returns an instance of the inputmanager
    */
    static InputManager* GetInstance();

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
    void Initialize( const INPUT_MODE mode = NORMAL, const std::string & mRecPlayFileName = "" );

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
    void ProcessEvent( const SDL_Event* evt );

    /**
    * Called every game loop, is only used for
    * fake event playback debugging tool right now
    */
    void Update();

	/**
	* Returns the current mode of the input manager
	*/
    const int GetMode() const { return mMode; };

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

    /**
    * Internal method that sends the incoming event
    * to all event listeners registered
    */
    inline void SendEventToListeners( const INPUTKEYS evt );

	/**
	* Loads recorded keys from fileName into mKeyList
	*/
    void LoadKeyListFromFile( const std::string & fileName );

	/**
	* Saves keys in mKeyList to fileName
	*/
    void SaveKeyListToFile( const std::string & fileName );

	/**
	* Saves a single key (appends after clearing the file once) to
	* fileName
	*/
    void SaveKeyToFile( const std::string & fileName, const int key );

// PROTECTED VARIABLES
    static InputManager* _instance;
    int mKeys[KEYCOUNT];
    int mJButtons[KEYCOUNT];
    bool mKeyState[KEYCOUNT]; // true if down, false if up
    EventListenerVec mRegisteredListeners;
    SDL_Joystick* mJoyStick;

    INPUT_MODE mMode;
    std::string mRecPlayFileName;
    KeyVec mKeyList;
    KeyVecItr mCurrentPlaybackKey;

    unsigned int mLastAutoRepeatTime; // time in ticks for next auto-repeat allowance in future

private:
// PRIVATE VARIABLES
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif  // _InputManager_h_
