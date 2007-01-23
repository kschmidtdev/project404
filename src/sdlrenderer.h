#ifndef SDLRENDERER_H
#define SDLRENDERER_H

#include <SDL/SDL.h>

/**
 *  The SDL-specific 2D rendering manager
 */
class SDLRenderer
{
    public:
        SDLRenderer();
        virtual ~SDLRenderer();

      /**
       * Starts up SDL for rendering
       * @param xRes the screen resolution width
       * @param yRes the screen resolution height
       * @param depth the screen resolution colour depth
       * @return 0 if no errors occured, 1 or something else if error did occur
       */
        int Initialize( const unsigned short xRes, const unsigned short yRes, const unsigned short depth );

      /**
       * Draws to the screen using SDL commands
       */
        void Update();

      /**
       * Frees memory and objects to do with rendering, exits SDL
       */
        void Shutdown();

    protected:

        SDL_Surface* screen;
        unsigned short xRes;
        unsigned short yRes;
        unsigned short depth;

        SDL_Rect dstrect;
        SDL_Surface* bmp;
};

#endif // SDLRENDERER_H
