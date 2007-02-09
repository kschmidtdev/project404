/**
 * An abstract Renderer to the screen
 *
 * #include "Renderer.h"
 *
 * An abstract Rendering class that should allow
 * for independent renderer implementations
 *
 *
 * Project 404 2007
 *
 * Authors:
 * Karl Schmidt, February 7 2007, Initial creation of the header
 */

#ifndef Renderer_h
#define Renderer_h

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//

// LOCAL INCLUDES
//

// FORWARD REFERENCES
//

class Renderer
{
public:
// LIFECYCLE

    /**
     * Default constructor.
	 */
    Renderer(void);

    /**
     * Destructor.
	 */
    virtual ~Renderer(void);

    /**
     * Responsible for shutting down anything
     * that needs to be when rendering is over
     * (upon application termination sequence)
    */
    virtual void Shutdown() = 0;

    /**
     * Initializes the variables in the class
    */
    virtual void Initialize( const int xRes, const int yRes, const int colourDepth );

// OPERATORS

// OPERATIONS

    /**
     * Responsible for drawing to the screen once
    */
    virtual void Draw() = 0;

// ACCESS (writing)
// INQUIRY (reading)

protected:
// PROTECTED METHODS

// PROTECTED VARIABLES
    int mXRes;
    int mYRes;
    int mColourDepth;

private:
// PRIVATE VARIABLES
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif  // _Renderer_h_
