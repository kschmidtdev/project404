/**
 * File: SoundResource.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Karl Schmidt, February 10 2007 | Full functionality implemented
 * Karl Schmidt, February 9 2007 | Initial creation, stubbed
 */
#include "SoundResource.h"                                // class implemented

#include <Logger.h>
#include <util.h>

/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

SoundResource::~SoundResource()
{

}


//============================= OPERATORS ====================================
//============================= OPERATIONS ===================================

void SoundResource::Load()
{
    mSndData = Mix_LoadWAV( mFileName.c_str() );

    tacAssert( mSndData );
    if( !mSndData )
    {
        LogError( string("Error loading sound file: ") + mFileName +
                  string(" (SDL_mixer error: ") + string(Mix_GetError()) + string(")") );
        return;
    }
}

void SoundResource::Unload()
{
    tacAssert( mSndData );
    Mix_FreeChunk( mSndData );
    mSndData = NULL;
}

//============================= ACCESS     ===================================
//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
