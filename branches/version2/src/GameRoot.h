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
 * Karl Schmidt, February 13 2007 | Added config file support
 * Karl Schmidt, February 11 2007 | Made all the members pointers
 * Karl Schmidt, February 07 2007 | Initial creation of header
 * Karl Schmidt, March 13 2007	  | Added parameter to Initialize for disabling the sound system
 * Karl Schmidt, March 14 2007    | Added event recording/playback support
 */

#ifndef GameRoot_h
#define GameRoot_h

// SYSTEM INCLUDES
//
#include <map>
#include <string>

using namespace std;

// PROJECT INCLUDES
//

// LOCAL INCLUDES
//

// FORWARD REFERENCES
//

typedef map<string,int> ConfigMap;
typedef ConfigMap::iterator ConfigItr;

class SecurityManager;
class DatabaseManager;
class DBEngine;
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
    * before calling GameLoop(), pass in a different value for soundEnabled
    * to disable sound
    */
    void Initialize( const int argc = 0, char** argv = NULL, const bool soundEnabled = true );

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

    /**
    * Loads the given config file if it exists, and takes the
    * the values out of it and puts them into mSettings
    */
    void LoadConfigFileSettings( const string fileName );

    /**
    * Processes the command line and sets certain options
    * based on the input (this is mainly used for the debugging tools for recording + playback of events)
    */
    void ProcessCommandLine( const int argc, char** argv );

// PROTECTED VARIABLES

    SecurityManager*    mSecurityManager;
    DatabaseManager*    mDatabase;
    DBEngine*           mDBEngine;
    InputManager*       mInput;
    SDLRenderer*        mRenderer;
    ResourceManager*    mResManager;
    SoundManager*       mSoundManager;
    GameEngine*         mGameEngine;
    UIManager*          mUIManager;

    ConfigMap           mSettings;

    string              mRecordFileName;
    string              mPlaybackFileName;

private:
// PRIVATE VARIABLES
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif  // _GameRoot_h_
