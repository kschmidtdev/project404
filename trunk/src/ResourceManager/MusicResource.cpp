/**
 * File: MusicResource.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Karl Schmidt, February 13 2007 | Added logging when loading and unloading
 * Karl Schmidt, February 10 2007 | Initial creation, implementation
 * Karl Schmidt, March 13 2007    | Added support for sound subsystem disabling
 * Karl Schmidt, March 23 2007    | Got rid of more using namespace std; usage
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
        LogInfo( std::string("Loading music file: ") + GetFileName() );

        mMusData = Mix_LoadMUS( GetFileName().c_str() );
        tacAssert( mMusData );
        if( !mMusData )
        {
            LogError( std::string("Error loading music file: ") + GetFileName() +
                      std::string(" (SDL_mixer error: ") + std::string(Mix_GetError()) + std::string(")") );
            return;
        }
    }
}

void MusicResource::Unload()
{
    if( SoundManager::GetInstance()->GetIsEnabled() )
    {
        LogInfo( std::string("Unloading music file: ") + GetFileName() );
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
