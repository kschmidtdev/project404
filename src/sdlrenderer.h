/**
 * An implementation of Renderer that uses SDL
 *
 * #include "SDLRenderer.h"
 *
 * A Renderer that uses SDL to draw 2D graphics
 *
 * @see Renderer
 *
 * Project 404 2007
 *
 * Authors:
 * Karl Schmidt, February 7 2007, Initial creation of the header
 */

#ifndef SDLRenderer_h
#define SDLRenderer_h

// SYSTEM INCLUDES
//
#include <SDL.h>
// TODO: Add SDL_ttf.h to distribution
//#include <SDL_ttf.h>
#include <vector>
using namespace std;

// PROJECT INCLUDES
//
#include "Renderer.h"

// LOCAL INCLUDES
//

// FORWARD REFERENCES
//
class SDLRenderable;

typedef vector<SDLRenderable*> RenderableVec;
typedef RenderableVec::iterator RenderableVecItr;

class SDLRenderer : public Renderer
{
public:
// LIFECYCLE

    /**
     * Destructor.
	 */
    virtual ~SDLRenderer(void);

    /**
     * Retrieves the instance of SDLRenderer,
     * if there is none, is makes one and retrieves
     * a pointer to it.
    */
    static SDLRenderer* GetInstance();

    /**
     * Initializes the SDLRenderer (sets values and starts SDL
     * rendering sequence)
	 */
    void Initialize( const int xRes, const int yRes, const int colourDepth );

    /**
     * Shuts down the renderer, cleaning up and freeing resources
     * specific to SDL rendering
	 */
    void Shutdown();

// OPERATORS
// OPERATIONS

    /**
     * Responsible for drawing to the screen once, will call
     * renderSelf on registered renderables in the render queue (in order)
	 */
    void Draw();

    /**
     * Adds a SDLRenderable to the render queue
	 */
    void AddToRenderQueue( SDLRenderable * toAdd );

    /**
     * Removes a SDLRenderable from the render queue
	 */
    void RemoveFromRenderQueue( SDLRenderable * toRemove );

    void DrawImageAt( SDL_Surface* src, const int x, const int y, const int width, const int height, SDL_Surface* dest );

// ACCESS (writing)
// INQUIRY (reading)

protected:
// PROTECTED METHODS
    /**
     * Default constructor.
	 */
    SDLRenderer(void);

// PROTECTED VARIABLES

    static SDLRenderer* _instance;
    RenderableVec mRenderQueue;
    SDL_Surface* mScreen;
// TODO: Implement font support
//    TTF_Font *font;

private:
// PRIVATE VARIABLES
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif  // _SDLRenderer_h_
