/**
 * A texture resource
 *
 * #include "TextureResource.h"
 *
 * An implementation of Resource that handles textures
 * loaded with SDL, and stored as SDL_Surfaces
 *
 * @see Resource, ResourceManager
 *
 * Project 404 2007
 *
 * Authors:
 * Karl Schmidt, February 9 2007 | Initial creation of the header
 */

#ifndef TextureResource_h
#define TextureResource_h

// SYSTEM INCLUDES
//
#include <SDL.h>

// PROJECT INCLUDES
//
#include "Resource.h"

// LOCAL INCLUDES
//

// FORWARD REFERENCES
//

class TextureResource : public Resource
{
public:
// LIFECYCLE

    /**
     * Constructor, passes fileName to base Resource constructor
     */
    TextureResource( const string fileName )
    : Resource( fileName ), mSurface( NULL ) { };

    /**
     * Destructor
     */
    ~TextureResource();

// OPERATORS
// OPERATIONS

    /**
     * Loads the texture into memory using SDL
     */
    void Load();

    /**
     * Unloads the texture from memory using SDL
	 */
    void Unload();

// ACCESS (writing)
// INQUIRY (reading)

    /**
     * Returns the SDL_Surface* of the loaded
     * texture, inlined for speed
	 */
    SDL_Surface* GetTexture() { return mSurface; };

protected:
// PROTECTED VARIABLES

    SDL_Surface* mSurface;

private:
// PRIVATE VARIABLES
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif  // _TextureResource_h_