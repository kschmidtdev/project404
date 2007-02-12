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
#include <SDL_ttf.h>
#include <vector>
#include <map>
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
typedef map<int, TTF_Font*> FontMap;
typedef FontMap::iterator FontMapItr;

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

    /**
     * Blits an image (src) on to dest at the particular point (x, y) and size (width, height)
	 */
    void DrawImageAt( SDL_Surface* src, const int x, const int y, const int width, const int height, SDL_Surface* dest );

    /**
     * Creates a SDL_Surface object with the given text written to that surface, colour
     * will default to white if no colour components are passed in. IF YOU CALL THIS YOU
     * MUST HANDLE DESTROYING THE SURFACE IT GIVES YOU WHEN YOU ARE DONE WITH IT
	 */
    SDL_Surface* SDLRenderer::CreateTextSurface( const string textToRender, const int size, const int red, const int green, const int blue );

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
    FontMap mFonts;

private:
// PRIVATE VARIABLES
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif  // _SDLRenderer_h_
