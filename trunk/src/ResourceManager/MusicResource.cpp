/**
 * File: MusicResource.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Karl Schmidt, February 10 2007 | Initial creation, implementation
 */
#include "MusicResource.h"                                // class implemented

#include <Logger.h>
#include <util.h>

/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

MusicResource::~MusicResource()
{

}


//============================= OPERATORS ====================================
//============================= OPERATIONS ===================================

void MusicResource::Load()
{
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
    tacAssert( mMusData );
    Mix_FreeMusic( mMusData );
    mMusData = NULL;
}

//============================= ACCESS     ===================================
//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
