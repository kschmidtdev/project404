/**
 * File: TextureResource.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Karl Schmidt, February 13 2007 | Added logging when loading and unloading
 * Karl Schmidt, February 9 2007  | Initial creation of implementation
 * Karl Schmidt, March 9 2007	  | Added SDL_image implementation to support other texture file formats
 * Karl Schmidt, March 23 2007    | Got rid of more using namespace std; usage
 */

#include <util.h>
#include <SDL_image.h>

#include "TextureResource.h"                                // class implemented

#include <Logger.h>

namespace
{
	const std::string IMG_DIR( "img/" );
}

/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

TextureResource::TextureResource( const std::string & fileName )
: Resource( fileName ),
  mSurface( NULL )
{

};

TextureResource::~TextureResource()
{
    // nothing to be done here
}

//============================= OPERATORS ====================================
//============================= OPERATIONS ===================================

void TextureResource::Load()
{
    tacAssert( GetFileName() != "" );

    // load an image

    LogInfo( std::string("Loading image: ") + GetFileName() );
    mSurface = IMG_Load( (IMG_DIR + GetFileName()).c_str() );

    tacAssert( mSurface );
    if ( !mSurface )
    {
        LogError( std::string("Unable to load bitmap: ") + GetFileName() + std::string(" SDL_image error: ") + std::string( IMG_GetError() ) );
    }
}

void TextureResource::Unload()
{
    if( mSurface )
    {
        LogInfo( std::string("Unloading image: ") + GetFileName() );
        SDL_FreeSurface( mSurface );
        mSurface = NULL;
    }
}

//============================= ACCESS     ===================================

SDL_Surface* TextureResource::GetTexture() const
{
    return mSurface;
};

//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
