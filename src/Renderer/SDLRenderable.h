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
 */

#ifndef SDLRenderable_h
#define SDLRenderable_h

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//

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
