/**
 * An implementation of Resource to store Music data
 *
 * #include "MusicResource.h"
 *
 * A Resource object that stores sound data that is loaded with SDL_mixer,
 * accepts OGG and MP3 format files
 *
 * @see Resource, ResourceManager
 *
 * Project 404 2007
 *
 * Authors:
 * Karl Schmidt, February 10 2007 | Initial creation of header
 */

#ifndef MusicResource_h
#define MusicResource_h

// SYSTEM INCLUDES
//

#include <SDL_mixer.h>

// PROJECT INCLUDES
//
#include "Resource.h"

// LOCAL INCLUDES
//

// FORWARD REFERENCES
//

class MusicResource : public Resource
{
public:
// LIFECYCLE

    /**
     * Default constructor, just sets the filename based on the given parameter
	 */
    MusicResource( const std::string & fileName );

    /**
     * Destructor, serves no purpose for this class
	 */
    ~MusicResource();

// OPERATORS

// OPERATIONS

    /**
     * Loads the resource into memory
	 */
    void Load();

    /**
     * Unloads the resource from memory
	 */
    void Unload();

// ACCESS (writing)
// INQUIRY (reading)

    /**
     * Returns a pointer to the Mix_Music
     * instance
	 */
    Mix_Music* GetMusic() const;

protected:
// PROTECTED VARIABLES

Mix_Music* mMusData;

private:
// PRIVATE VARIABLES
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif  // _MusicResource_h_
