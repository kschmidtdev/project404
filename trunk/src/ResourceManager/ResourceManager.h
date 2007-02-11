/**
 * A resource manager that prevents redundant loading
 *
 * #include "ResourceManager.h"
 *
 * A resource manager that prevents redundant loading
 * by keeping track of what has been loaded already
 *
 * @see Resource
 *
 * Project 404 2007
 *
 * Authors:
 * Karl Schmidt, February 10 2007, Added support for sound and music resources
 * Karl Schmidt, February 9 2007, Initial creation of header
 */

#ifndef ResourceManager_h
#define ResourceManager_h

// SYSTEM INCLUDES
//
#include <SDL.h>
#include <SDL_mixer.h>

#include <string>
#include <vector>
using namespace std;

// PROJECT INCLUDES
//

// LOCAL INCLUDES
//

// FORWARD REFERENCES
//
class Resource;

typedef vector<Resource*> ResourceVec;
typedef ResourceVec::iterator ResourceVecItr;

class ResourceManager
{
public:
// LIFECYCLE

    /**
     * Returns the static instance of ResourceManager (well, a pointer to it)
     * and if one does not exist yet, creates one and returns a pointer to that
	 */
    static ResourceManager* GetInstance();

    /**
     * Destructor.
	 */
    ~ResourceManager(void);

    /**
     * Initializes the resource manager, prepares
     * anything that needs to be done before
     * any other methods are called
	 */
    void Initialize();

    /**
     * Shuts down the resource managers, will
     * unload all loaded resources
	 */
    void Shutdown();

// OPERATORS
// OPERATIONS
// ACCESS (writing)
// INQUIRY (reading)


    /**
     * Returns a pointer to the loaded texture,
     * will return an existing pointer if texture
     * has already been loaded
	 */
    SDL_Surface* LoadTexture( const string fileName );

    /**
     * Returns a pointer to the loaded sound,
     * will return an existing pointer if sound
     * has already been loaded
	 */
    Mix_Chunk* LoadSound( const string fileName );

    /**
     * Returns a pointer to the loaded music,
     * will return an existing pointer if music
     * has already been loaded
	 */
    Mix_Music* LoadMusic( const string fileName );

protected:
// PROTECTED METHODS

    /**
     * Default constructor.
	 */
    ResourceManager(void);

    /**
     * A generic method used internally to check
     * if a resource has been loaded already, if it
     * has, it returns a pointer to that resource back,
     * if it cannot find one, it returns NULL
	 */
    Resource* CheckForResource( const string fileName );

// PROTECTED VARIABLES

    static ResourceManager* _instance;

    ResourceVec mLoadedResources;

private:
// PRIVATE VARIABLES
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif  // _ResourceManager_h_
