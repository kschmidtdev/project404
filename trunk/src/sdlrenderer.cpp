#include "sdlrenderer.h"

SDLRenderer::SDLRenderer()
: screen( NULL ),
  xRes( 640 ),
  yRes( 480 ),
  depth( 16 )
{
    //ctor
}

SDLRenderer::~SDLRenderer()
{
    //dtor
}

int SDLRenderer::Initialize( const unsigned short xRes, const unsigned short yRes, const unsigned short depth )
{
    // initialize SDL video
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return 1;
    }

    // create a new window
    screen = SDL_SetVideoMode(xRes, yRes, depth, SDL_HWSURFACE|SDL_DOUBLEBUF);

    if ( !screen )
    {
        printf("Unable to set %ix%i video: %s\n", xRes, yRes, SDL_GetError());
        return 1;
    }

    // load an image
    bmp = SDL_LoadBMP("cb.bmp");
    if (!bmp)
    {
        printf("Unable to load bitmap: %s\n", SDL_GetError());
        return 1;
    }

    // centre the bitmap on screen
    dstrect.x = (screen->w - bmp->w) / 2;
    dstrect.y = (screen->h - bmp->h) / 2;

    return 0; // successful
}

void SDLRenderer::Shutdown()
{
    // free loaded bitmap
    SDL_FreeSurface(bmp);

    SDL_Quit();
}

void SDLRenderer::Update()
{
    // clear screen
    SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));

    // DRAWING STARTS HERE

    // TODO: Remove this code, it's just here for testing
    static unsigned int xDir = 1;
    static unsigned int yDir = 1;

    dstrect.x += xDir;
    if( dstrect.x > xRes-bmp->w || dstrect.x < 0 )
    {
        xDir = -xDir;
    }
    dstrect.y += yDir;
    if( dstrect.y > yRes-bmp->h || dstrect.y < 0 )
    {
        yDir = -yDir;
    }

    // draw bitmap
    SDL_BlitSurface(bmp, 0, screen, &dstrect);
    // end TODO test code

    // DRAWING ENDS HERE

    // finally, update the screen :)
    SDL_Flip(screen);
}


