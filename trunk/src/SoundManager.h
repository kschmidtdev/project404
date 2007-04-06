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
 * Karl Schmidt, March 24 2007    | Renamed some variables to match coding standard, fixed return 03 problem.
 * Karl Schmidt, March 26 2007    | Added volume control functionality for both SDL_Mixer and RTAudio playback
 * Mike Malyuk,  April 1  2007    | Added vector include, added CalcHanning, Hanning, SetSoundArray, SetLeft, GetSound, Get Left
 *                                | and a whack of new params: mPi, mFS, mT, mSound, mLeft
 * Mike Malyuk,  April 2  2007    | Revised SetSoundArray to take a double.
 */

#ifndef SoundManager_h
#define SoundManager_h

// SYSTEM INCLUDES
//
#include <SDL_mixer.h>
//#include "RtAudio.h"
#include <vector>
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

    enum VOLUME_LEVEL
    {
        VL_MUTE = 0,
        VL_QUIET,
        VL_MODERATE,
        VL_LOUD,
        VL_VERY_LOUD,
        VL_MAX = VL_VERY_LOUD
    };

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

    std::vector<double> CalcHanning(int m,int n);

    std::vector<double> Hanning(int impulse);

// ACCESS (writing)

    void SetSoundArray(double tau);

    void SetLeft(bool left){mLeft = left;}
// INQUIRY (reading)

    /**
     * Returns true if sound is enabled
	 */
    const bool GetIsEnabled() const { return mIsEnabled; };

    /**
     * Sets the current volume level (will affect all audio, even what is being played back)
	 */
    void SetVolumeLevel( const VOLUME_LEVEL newVolumeLevel );

    /**
     * Returns the current volume setting
	 */
    const VOLUME_LEVEL GetVolumeLevel() const;

    double* GetSoundArr(){return mSound;}

    bool GetLeft(){return mLeft;}

protected:
// PROTECTED METHODS

    /**
     * Default constructor.
	 */
    SoundManager(void);

// PROTECTED VARIABLES

    static SoundManager* _instance;

    bool mIsEnabled;
//    RtAudio* mRTAudio;
//    double* mAudioData;
    VOLUME_LEVEL mCurVolumeLevel;
    double mPi;
    double mFS;
    double mT;
    double* mSound;
    bool mLeft;
private:
// PRIVATE VARIABLES
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif  // _SoundManager_h_
