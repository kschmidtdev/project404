/**
 * File: SoundResource.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Karl Schmidt, February 13 2007 | Added logging when loading and unloading
 * Karl Schmidt, February 10 2007 | Full functionality implemented
 * Karl Schmidt, February 9 2007 | Initial creation, stubbed
 * Karl Schmidt, March 13 2007    | Added support for sound subsystem disabling
 */

#include "SoundResource.h"                                // class implemented

#include <util.h>
#include <Logger.h>
#include <SoundManager.h>

/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

SoundResource::SoundResource( const std::string & fileName )
: Resource( fileName ),
  mSndData( NULL )
{

};

SoundResource::~SoundResource()
{

}


//============================= OPERATORS ====================================
//============================= OPERATIONS ===================================

void SoundResource::Load()
{
    if( SoundManager::GetInstance()->GetIsEnabled() )
    {
        LogInfo( string("Loading sound: ") + GetFileName() );

        mSndData = Mix_LoadWAV( GetFileName().c_str() );
        tacAssert( mSndData );
        if( !mSndData )
        {
            LogError( string("Error loading sound file: ") + GetFileName() +
                      string(" (SDL_mixer error: ") + string(Mix_GetError()) + string(")") );
            return;
        }
    }
}

void SoundResource::Unload()
{
    if( SoundManager::GetInstance()->GetIsEnabled() )
    {
        LogInfo( string("Unloading sound file: ") + GetFileName() );
        tacAssert( mSndData );
        Mix_FreeChunk( mSndData );
        mSndData = NULL;
    }
}

//============================= ACCESS     ===================================

Mix_Chunk* SoundResource::GetSound() const
{
    return mSndData;
};

//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
