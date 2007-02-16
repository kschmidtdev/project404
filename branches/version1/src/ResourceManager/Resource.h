/**
 * Base abstract class for resources
 *
 * #include "Resource.h"
 *
 * A base abstract class for resources
 * to inherit from, contains generic
 * information (like filename)
 *
 * @see ResourceManager
 *
 * Project 404 2007
 *
 * Authors:
 * Karl Schmidt, February 8 2007 | Initial creation of header file
 */

#ifndef Resource_h
#define Resource_h

// SYSTEM INCLUDES
//
#include <string>
using namespace std;

// PROJECT INCLUDES
//

// LOCAL INCLUDES
//

// FORWARD REFERENCES
//


class Resource
{
public:
// LIFECYCLE

    /**
     * Constructor.
	 */
    Resource( const string fileName )
    : mFileName( fileName ) { };

    /**
     * Destructor.
	 */
    virtual ~Resource() { };

// OPERATORS
// OPERATIONS

    /**
     * To be implemented by the inheriting class, will
     * handle loading of the resource
	 */
    virtual void Load() = 0;

    /**
     * To be implemented by the inheriting class, will
     * handle unloading of the resource
	 */
    virtual void Unload() = 0;

// ACCESS (writing)
// INQUIRY (reading)

    /**
     * Returns the filename of the resource
	 */
    string GetFileName() { return mFileName; };

protected:
// PROTECTED VARIABLES

string mFileName;
private:
// PRIVATE VARIABLES
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif  // _Resource_h_
