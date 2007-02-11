/**
 * File: SoundManager.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Karl Schmidt, February 10 2007 | Initial creation of the class
 */
#include "SoundManager.h"                                // class implemented

#include <Logger.h>
#include <util.h>

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

void SoundManager::Initialize()
{
    LogInfo( "Beginning SoundManager initialization..." );
    if(Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1 )
    {
        LogCritical( string("Mix_OpenAudio: ") + string(Mix_GetError()) );
        tacAssert( false ); // this should never happen
        return;
    }

    // TODO: Make functions for this or something
    Mix_AllocateChannels( 1 );
    Mix_Volume( -1, MIX_MAX_VOLUME /2 );

    LogInfo( "SoundManager initialized successfully." );
}

void SoundManager::Shutdown()
{
    LogInfo( "Beginning SoundManager shut down..." );
    Mix_CloseAudio();
    LogInfo( "SoundManager shut down successfully." );
}

//============================= OPERATORS ====================================
//============================= OPERATIONS ===================================

void SoundManager::PlaySound( Mix_Chunk* toPlay, const bool looping )
{
    Mix_PlayChannel( -1, toPlay, looping ? -1 : 0 );
}

void SoundManager::PlayMusic( Mix_Music* toPlay, const bool looping )
{
    Mix_PlayMusic( toPlay, looping ? -1 : 0 );
}

//============================= ACCESS     ===================================
//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

SoundManager::SoundManager(void)
{
    // stub
}

/////////////////////////////// PRIVATE    ///////////////////////////////////
