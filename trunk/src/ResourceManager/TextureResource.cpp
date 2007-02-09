/**
 * File: TextureResource.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Karl Schmidt, February 9 2007 | Initial creation of implementation
 */
#include "TextureResource.h"                                // class implemented


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
    // TODO: Make a default constructor that sets the pointers to NULL
    mSurface = NULL;
    // load an image
    mSurface = SDL_LoadBMP( mFileName.c_str() );
    if ( !mSurface )
    {
        // TODO: Use the logger for this
        printf("Unable to load bitmap: %s\n", SDL_GetError());
    }
}

void TextureResource::Unload()
{
    if( mSurface )
    {
        SDL_FreeSurface( mSurface );
        mSurface = NULL;
    }
}

//============================= ACCESS     ===================================
//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
