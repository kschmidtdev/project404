/**
 * A simple demonstration of how renderables work
 *
 * #include "ExampleRenderable.h"
 *
 * An example SDLRenderable object to serve as a reference
 * as well as a test case
 *
 * @see SDLRenderable, SDLRenderer
 *
 * Project 404 2007
 *
 * Authors:
 * Karl Schmidt, February 9 2007 | Initial creation of header
 */

#ifndef ExampleRenderable_h
#define ExampleRenderable_h

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include "SDLRenderable.h"

// LOCAL INCLUDES
//

// FORWARD REFERENCES
//

class ExampleRenderable : public SDLRenderable
{
public:
// LIFECYCLE

    /**
     * Default constructor.
	 */
    ExampleRenderable(void)
    : mSurface( NULL ), mX( 0 ), mY( 0 )
    {
        mSurface = ResourceManager::GetInstance()->LoadTexture( "cb.bmp" );
    }

// OPERATORS
// OPERATIONS

    /**
     * Renders this renderable to the given destination surface
	 */
    void RenderSelf( SDL_Surface* destination )
    {
        SDLRenderer::GetInstance()->DrawImageAt( mSurface, mX, mY, mSurface->w, mSurface->h, destination );
    }

// ACCESS (writing)
// INQUIRY (reading)

protected:
// PROTECTED VARIABLES

    SDL_Surface* mSurface;
    int mX, mY;

private:
// PRIVATE VARIABLES
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif  // _ExampleRenderable_h_
