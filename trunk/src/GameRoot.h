/**
 * The main object for our game
 *
 * #include "GameRoot.h"
 *
 * The is the application root, contains
 * the main loop and handles the starting
 * and shutdown of all major subsystems
 *
 * Project 404 2007
 *
 * Authors:
 * Karl Schmidt, February 11 2007 | Made all the members pointers
 * Karl Schmidt, February 07 2007, Initial creation of header
 */

#ifndef GameRoot_h
#define GameRoot_h

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//

// LOCAL INCLUDES
//

// FORWARD REFERENCES
//

class SecurityManager;
class DatabaseManager;
class InputManager;
class SDLRenderer;
class ResourceManager;
class SoundManager;
class GameEngine;
class UIManager;

class GameRoot
{
public:
// LIFECYCLE

    /**
    * Default constructor.
    */
    GameRoot(void);

    /**
    * Destructor.
    */
    ~GameRoot(void);

    /**
    * Goes through and initializes
    * variables and objects, must be called
    * before calling GameLoop()
    */
    void Initialize();

    /**
    * Goes through and shuts down
    * variables and objects, must be called
    * before the game ends
    */
    void Shutdown();

// OPERATIONS

    /**
    * This function will not return
    * until the game ends. It contains
    * the main SDL event listening
    * and will call updates to all major
    * subsystems. It will return
    * when the game is considered to be ended,
    * and Shutdown() should then be called
    * afterwards.
    */
    void GameLoop();

// ACCESS (writing)
// INQUIRY (reading)

protected:
// PROTECTED VARIABLES

    SecurityManager*    mSecurityManager;
    DatabaseManager*    mDatabase;
    InputManager*       mInput;
    SDLRenderer*        mRenderer;
    ResourceManager*    mResManager;
    SoundManager*       mSoundManager;
    GameEngine*         mGameEngine;
    UIManager*          mUIManager;

private:
// PRIVATE VARIABLES
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif  // _GameRoot_h_
