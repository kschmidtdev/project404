/**
 * File: SoundManager.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Karl Schmidt, February 13 2007 | Added StopAllPlayback, made playback functions safer
 * Karl Schmidt, February 11 2007 | Added calls to stop playing music before shutting down
 * Karl Schmidt, February 11 2007 | Correctly cleared the singleton instance in Shutdown()
 * Karl Schmidt, February 10 2007 | Initial creation of the class
 * Karl Schmidt, March 13 2007    | Added support for sound subsystem disabling
 * Karl Schmidt, March 23 2007    | Got rid of more using namespace std; usage
 * Mike Malyuk, March 24 2007     | Added code for RTAudio real time output.
 */



#include "SoundManager.h"                                // class implemented
#include <math.h>
#include <Logger.h>
#include <util.h>

typedef float  MY_TYPE;
#define FORMAT RTAUDIO_FLOAT32
#define SCALE  1.0

#define BASE_RATE 0.005
#define TIME   1.0
/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

SoundManager* SoundManager::_instance = 0;

SoundManager* SoundManager::GetInstance()
{
    if( !_instance )
    {
        _instance = new SoundManager();
    }
    return _instance;
}

SoundManager::~SoundManager()
{
    // stub
}// ~SoundManager

void SoundManager::Initialize( const bool isEnabled )
{
    mIsEnabled = isEnabled;
    if( mIsEnabled )
    {
        LogInfo( "Beginning SoundManager initialization..." );
        if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1 )
        {
            LogCritical( std::string("Mix_OpenAudio: ") + std::string(Mix_GetError()) );
            tacAssert( false ); // this should never happen
            return;
        }
        int buffer_size, fs, device = 0;
        audio = 0;
        data = new double(1);
        fs = 44100;
        // Open the realtime output device
        buffer_size = 1024;
        try
        {
            audio = new RtAudio(device, 1, 0, 0,
                                FORMAT, fs, &buffer_size, 4);
        }
        catch (RtError &error)
        {
            error.printMessage();
            exit(EXIT_FAILURE);
        }
        try
        {
            //audio->setStreamCallback(&cosine, (void *)data);
            //audio->startStream();
        }
        catch (RtError &error)
        {
            error.printMessage();
        }
        // TODO: Make functions for this or something
        Mix_AllocateChannels( 1 );
        Mix_Volume( -1, MIX_MAX_VOLUME /2 );

        LogInfo( "SoundManager initialized successfully." );
    }
}

void SoundManager::Shutdown()
{
    if( mIsEnabled )
    {
        LogInfo( "Beginning SoundManager shut down..." );

        StopAllPlayback();

        Mix_CloseAudio();

        audio->stopStream();
        audio->closeStream();
        delete audio;
        delete[] data;
    }

    delete _instance;
    _instance = NULL;

    if( mIsEnabled )
    {
        LogInfo( "SoundManager shut down successfully." );
    }
}

//============================= OPERATORS ====================================
//============================= OPERATIONS ===================================

void SoundManager::PlaySoundSample( Mix_Chunk* toPlay, const bool looping )
{
    if( mIsEnabled )
    {
        tacAssert( toPlay );
        if( toPlay )
        {
            Mix_PlayChannel( -1, toPlay, looping ? -1 : 0 );
        }
        else
        {
            LogError( "Attempting to play invalid sound (NULL)" );
        }
    }
}

void SoundManager::PlayMusic( Mix_Music* toPlay, const bool looping )
{
    if( mIsEnabled )
    {
        tacAssert( toPlay );
        if( toPlay )
        {
            Mix_PlayMusic( toPlay, looping ? -1 : 0 );
        }
        else
        {
            LogError( "Attempting to play invalid music (NULL)" );
        }
    }
}
static int cosine(char *buffer, int buffer_size, void *data)
{
    int i, j;
    static int chans = 1;
    static int times = 0;
    float T = 1.0 / 44100.0;
    MY_TYPE *my_buffer = (MY_TYPE *) buffer;
    double *my_data = (double *) data;
    double pi = 3.141592653589793;
    MY_TYPE sinval = 0;
    static int n = 0;
    float f0 = 262.0;
    for (i=0; i<buffer_size; i++)
    {
        sinval = .5*(cos(2.0*pi*f0*T*(float)n) + cos(2.0*pi*f0*T*(float)n) * cos(2.0*pi*f0*T*(float)n)) +
                 (cos(2.0*pi*3*f0*T*(float)n) + cos(2.0*pi*f0*T*(float)n) * cos(2.0*pi*3*f0*T*(float)n)) +
                 (cos(2.0*pi*4*f0*T*(float)n) + cos(2.0*pi*f0*T*(float)n) * cos(2.0*pi*4*f0*T*(float)n)) +
                 (cos(2.0*pi*5*f0*T*(float)n) + cos(2.0*pi*f0*T*(float)n) * cos(2.0*pi*5*f0*T*(float)n)) +
                 .1*(cos(2.0*pi*7*f0*T*(float)n) + cos(2.0*pi*f0*T*(float)n) * cos(2.0*pi*7*f0*T*(float)n)) +
                 .05*(cos(2.0*pi*9*f0*T*(float)n) + cos(2.0*pi*f0*T*(float)n) * cos(2.0*pi*9*f0*T*(float)n));
        n++;
        if (n > 44100)
        {
            n = 0;
            times++;
        }
        for (j=0; j<chans; j++)
        {
            *my_buffer++ = (MY_TYPE) (my_data[j] * SCALE);
            my_data[j] = sinval/7.4;
        }
    }
    if (times == 1)
    {
        times = 0;
        return 1;
    }
    return 0;
}
void SoundManager::PlayRTAUDIO()
{
    if( mIsEnabled )
    {
        audio->startStream();
        audio->setStreamCallback(&cosine, (void *)data);
    }
}

void SoundManager::StopAllPlayback()
{
    if( mIsEnabled )
    {
        Mix_HaltChannel(-1);
        Mix_HaltMusic();
    }
}

//============================= ACCESS     ===================================
//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

SoundManager::SoundManager(void)
: mIsEnabled( true )
{
    // stub
}

/////////////////////////////// PRIVATE    ///////////////////////////////////
