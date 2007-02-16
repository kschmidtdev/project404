/**
 * File: TextureResource.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Karl Schmidt, February 13 2007 | Added logging when loading and unloading
 * Karl Schmidt, February 9 2007 | Initial creation of implementation
 */
#include "TextureResource.h"                                // class implemented

#include <Logger.h>
#include <util.h>

/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

TextureResource::~TextureResource()
{
    // nothing to be done here
}

//============================= OPERATORS ====================================
//============================= OPERATIONS ===================================

void TextureResource::Load()
{
    tacAssert( mFileName != "" );

    // load an image

    LogInfo( string("Loading image: ") + mFileName );
    mSurface = SDL_LoadBMP( mFileName.c_str() );

    tacAssert( mSurface );
    if ( !mSurface )
    {
        LogError( string("Unable to load bitmap: ") + mFileName + string(" SDL error: ") + string( SDL_GetError() ) );
    }
}

void TextureResource::Unload()
{
    if( mSurface )
    {
        LogInfo( string("Unloading image: ") + mFileName );
        SDL_FreeSurface( mSurface );
        mSurface = NULL;
    }
}

//============================= ACCESS     ===================================
//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////