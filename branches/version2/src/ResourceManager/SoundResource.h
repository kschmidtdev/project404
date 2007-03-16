/**
 * An implementation of Resource to store Sound data
 *
 * #include "SoundResource.h"
 *
 * A Resource object that stores sound data that is loaded with SDL_mixer,
 * accepts WAV format files
 *
 * @see Resource, ResourceManager
 *
 * Project 404 2007
 *
 * Authors:
 * Karl Schmidt, February 10 2007 | Implementation
 * Karl Schmidt, February 9 2007 | Initial creation of header
 */

#ifndef SoundResource_h
#define SoundResource_h

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

class SoundResource : public Resource
{
public:
// LIFECYCLE

    /**
     * Default constructor, just sets the filename based on the given parameter
	 */
    SoundResource( const std::string & fileName );

    /**
     * Destructor, serves no purpose for this class
	 */
    ~SoundResource();

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
     * Returns a pointer to the Mix_Chunk
     * instance
	 */
    Mix_Chunk* GetSound() const;

private:
// PRIVATE VARIABLES

Mix_Chunk* mSndData;

};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif  // _SoundResource_h_
