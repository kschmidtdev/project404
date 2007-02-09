/**
 * An implementation of Resource to store Sound data
 *
 * #include "SoundResource.h"
 *
 * A Resource object that stores sound data that is loaded with SDL
 *
 * @see Resource, ResourceManager
 *
 * Project 404 2007
 *
 * Authors:
 * Karl Schmidt, February 9 2007 | Initial creation of header
 */

#ifndef SoundResource_h
#define SoundResource_h

// SYSTEM INCLUDES
//

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
    SoundResource( const string fileName )
    : Resource( fileName ) { };

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

// TODO: Add source resource retrieval function

protected:
// PROTECTED VARIABLES

// add actual sound resource pointer here

private:
// PRIVATE VARIABLES
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif  // _SoundResource_h_
