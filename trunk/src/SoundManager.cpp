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
 */

#include <util.h>


#include "SoundManager.h"                                // class implemented

#include <Logger.h>

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

void SoundManager::PlaySound( Mix_Chunk* toPlay, const bool looping )
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
