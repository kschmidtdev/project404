/**
 * File: MusicResource.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Karl Schmidt, February 13 2007 | Added logging when loading and unloading
 * Karl Schmidt, February 10 2007 | Initial creation, implementation
 */

#include <util.h>

#include "MusicResource.h"                                // class implemented

#include <Logger.h>

/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

MusicResource::~MusicResource()
{

}


//============================= OPERATORS ====================================
//============================= OPERATIONS ===================================

void MusicResource::Load()
{
    LogInfo( string("Loading music file: ") + mFileName );

    mMusData = Mix_LoadMUS( mFileName.c_str() );
    tacAssert( mMusData );
    if( !mMusData )
    {
        LogError( string("Error loading music file: ") + mFileName +
                  string(" (SDL_mixer error: ") + string(Mix_GetError()) + string(")") );
        return;
    }
}

void MusicResource::Unload()
{
    LogInfo( string("Unloading music file: ") + mFileName );
    tacAssert( mMusData );
    Mix_FreeMusic( mMusData );
    mMusData = NULL;
}

//============================= ACCESS     ===================================
//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
