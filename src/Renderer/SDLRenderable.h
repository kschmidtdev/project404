/**
 * A simple abstract class for a renderable
 *
 * #include "SDLRenderable.h"
 *
 * A class to inherit from if you want
 * to have it draw something to the screen
 * (must register with SDLRenderer also)
 *
 * @see SDLRenderer
 *
 * Project 404 2007
 *
 * Authors:
 * Karl Schmidt, February 9 2007, Initial creation of header
 * Andrew Osborne, February 10 2007, added SDL include
 * Karl Schmidt, March 20 2007 | Added virtual destructor
 */

#ifndef SDLRenderable_h
#define SDLRenderable_h

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <SDL.h>

// LOCAL INCLUDES
//

// FORWARD REFERENCES
//


class SDLRenderable
{
public:
// LIFECYCLE

// OPERATORS

// OPERATIONS

    virtual ~SDLRenderable() { };

    /**
     * To be overritten by an inheriting class,
     * should draw to the given surface
    */
    virtual void RenderSelf( SDL_Surface* destination ) = 0;

// ACCESS (writing)
// INQUIRY (reading)

protected:
// PROTECTED VARIABLES
private:
// PRIVATE VARIABLES
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif  // _SDLRenderable_h_
