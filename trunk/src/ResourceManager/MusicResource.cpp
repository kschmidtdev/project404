/**
 * File: MusicResource.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Karl Schmidt, February 13 2007 | Added logging when loading and unloading
 * Karl Schmidt, February 10 2007 | Initial creation, implementation
 * Karl Schmidt, March 13 2007    | Added support for sound subsystem disabling
 */

#include "MusicResource.h"                                // class implemented

#include <util.h>

#include <Logger.h>
#include <SoundManager.h>

/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

MusicResource::MusicResource( const std::string & fileName )
: Resource( fileName ),
  mMusData( NULL )
{

};

MusicResource::~MusicResource()
{

}


//============================= OPERATORS ====================================
//============================= OPERATIONS ===================================

void MusicResource::Load()
{
    if( SoundManager::GetInstance()->GetIsEnabled() )
    {
        LogInfo( string("Loading music file: ") + GetFileName() );

        mMusData = Mix_LoadMUS( GetFileName().c_str() );
        tacAssert( mMusData );
        if( !mMusData )
        {
            LogError( string("Error loading music file: ") + GetFileName() +
                      string(" (SDL_mixer error: ") + string(Mix_GetError()) + string(")") );
            return;
        }
    }
}

void MusicResource::Unload()
{
    if( SoundManager::GetInstance()->GetIsEnabled() )
    {
        LogInfo( string("Unloading music file: ") + GetFileName() );
        tacAssert( mMusData );
        Mix_FreeMusic( mMusData );
        mMusData = NULL;
    }
}

//============================= ACCESS     ===================================

Mix_Music* MusicResource::GetMusic() const
{
    return mMusData;
};

//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
