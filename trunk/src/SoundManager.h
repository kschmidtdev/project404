/**
 * A system system for playing sounds
 *
 * #include "SoundManager.h"
 *
 * A simple system (Singleton) that gives access
 * to sound playback functionality.
 *
 * @see SoundResource
 *
 * Project 404 2007
 *
 * Authors:
 * Karl Schmidt, February 10 2007 | Initial creation of the class
 */

#ifndef SoundManager_h
#define SoundManager_h

// SYSTEM INCLUDES
//
#include <SDL_mixer.h>

// PROJECT INCLUDES
//

// LOCAL INCLUDES
//

// FORWARD REFERENCES
//


class SoundManager
{
public:
// LIFECYCLE

    /**
    * Returns an instance of the soundmanager
    */
    static SoundManager* GetInstance();

    /**
     * Destructor.
	 */
    ~SoundManager(void);

    /**
    * Initializes SDL_Mixer,
    * prepares system for loading
    * and playing back of audio
    */
    void Initialize();

    /**
    * Shuts the sound manager down,
    * performs SDL_mixer cleanup and other
    * cleanup operations required
    */
    void Shutdown();

// OPERATORS
// OPERATIONS

    /**
     * Plays the given sound, will make it looping
     * if looping is true
	 */
    void PlaySound( Mix_Chunk* toPlay, const bool looping );

    /**
     * Plays the given music, will make it looping
     * if looping is true
	 */
    void PlayMusic( Mix_Music* toPlay, const bool looping );

// ACCESS (writing)
// INQUIRY (reading)

protected:
// PROTECTED METHODS

    /**
     * Default constructor.
	 */
    SoundManager(void);

// PROTECTED VARIABLES

    static SoundManager* _instance;

private:
// PRIVATE VARIABLES
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif  // _SoundManager_h_
