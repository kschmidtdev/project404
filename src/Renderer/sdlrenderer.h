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
 * Karl Schmidt, March 26 2007    | Added support for drawing an image to the screen
 								    with a particular alpha value
 * Karl Schmidt, March 26 2007    | Added helper AddAnimation function
 * Karl Schmidt, March 22 2007    | Correcting include orders and paths
 * Karl Schmidt, March 21 2007    | Added support for black-backround rendering behind text
 * Karl Schmidt, February 15 2007 | Added temporary renderable functionality
 * Karl Schmidt, February 7 2007, Initial creation of the header
 */

#ifndef SDLRenderer_h
#define SDLRenderer_h

// SYSTEM INCLUDES
//
#include <vector>
#include <map>
#include <SDL_ttf.h>

// PROJECT INCLUDES
//
#include "Renderer.h"

// LOCAL INCLUDES
//

// FORWARD REFERENCES
//
class SDLRenderable;
class SDL_Surface;

typedef unsigned int Uint32;

typedef std::vector<SDLRenderable*> RenderableVec;
typedef RenderableVec::iterator RenderableVecItr;
typedef std::map<int, TTF_Font*> FontMap;
typedef FontMap::iterator FontMapItr;

typedef std::pair<Uint32, Uint32> TimeStartEndPair;
typedef std::pair<SDLRenderable*, TimeStartEndPair> TempRenderable;
typedef std::vector< TempRenderable > TempRenderableVec;
typedef TempRenderableVec::iterator TempRenderableItr;

typedef std::vector<SDLRenderable*> SDLRenderableVec;
typedef SDLRenderableVec::iterator SDLRenderableItr;
typedef SDLRenderableVec::const_iterator SDLRenderableConstItr;

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
     * Adds a SDLRenderable to the temporary render queue, that
     * will be removed when timeToRemove becomes older than the current time
     * and will start drawing when timeToStart is reached if it is not 0
     * THIS WILL DELETE EXPIRED RENDERABLES ITSELF
	 */
    void AddToTempRenderQueue( SDLRenderable * toAdd, const Uint32 timeToRemove, const Uint32 timeToStart = 0 );

    /**
     * Removes a SDLRenderable from the render queue
	 */
    void RemoveFromRenderQueue( SDLRenderable * toRemove );

    /**
     * Blits an image (src) on to dest at the particular point (x, y) and size (width, height)
	 */
    void DrawImageAt( SDL_Surface* src, const int x, const int y, const int width, const int height, SDL_Surface* dest, const Uint32 alpha = 255 );

    /**
     * Creates a SDL_Surface object with the given text written to that surface, colour
     * will default to white if no colour components are passed in. IF YOU CALL THIS YOU
     * MUST HANDLE DESTROYING THE SURFACE IT GIVES YOU WHEN YOU ARE DONE WITH IT
	 */
    SDL_Surface* SDLRenderer::CreateTextSurface( const std::string & textToRender, const int size, const int red = 255, const int green = 255,
                                                 const int blue = 255, const bool backBlack = false );

    /**
     * Adds all SDLRenderables in frames to the temporary render queue, and sets
     * up their respective delays accordingly
	 */
    void AddAnimation( const SDLRenderableVec & frames, const Uint32 delay, const Uint32 initialDelay = 0 );

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
    SDL_Surface* mTransTempScreen;
    FontMap mFonts;
    TempRenderableVec mTempRenderables;

private:
// PRIVATE VARIABLES
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif  // _SDLRenderer_h_
