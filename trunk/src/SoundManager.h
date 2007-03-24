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
 * Karl Schmidt, February 13 2007 | Added StopAllPlayback
 * Karl Schmidt, February 10 2007 | Initial creation of the class
 * Karl Schmidt, March 13 2007    | Added support for sound subsystem disabling
 */

#ifndef SoundManager_h
#define SoundManager_h

// SYSTEM INCLUDES
//
#include <SDL_mixer.h>
#include "RtAudio.h"
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
    * and playing back of audio, will disable the sound manager if isEnabled is false
    */
    void Initialize( const bool isEnabled = true );

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
    void PlaySoundSample( Mix_Chunk* toPlay, const bool looping );

    /**
     * Plays the given music, will make it looping
     * if looping is true
	 */
    void PlayMusic( Mix_Music* toPlay, const bool looping );

    //int cosine(char *buffer, int buffer_size, void *data);

    /**
     *
     */
    void PlayRTAUDIO();
    /**
     * Plays the given music, will make it looping
     * if looping is true
	 */
    void StopAllPlayback();

// ACCESS (writing)
// INQUIRY (reading)

    /**
     * Returns true if sound is enabled
	 */
    bool GetIsEnabled() { return mIsEnabled; };

protected:
// PROTECTED METHODS

    /**
     * Default constructor.
	 */
    SoundManager(void);

// PROTECTED VARIABLES

    static SoundManager* _instance;

    bool mIsEnabled;
    RtAudio* audio;
    double* data;

private:
// PRIVATE VARIABLES
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif  // _SoundManager_h_
