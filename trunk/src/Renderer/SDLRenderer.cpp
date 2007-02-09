/**
 * File: SDLRenderer.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Karl Schmidt, February 8 2007 | Initial creation of cpp file
 */
#include "SDLRenderer.h"                                // class implemented

#include "SDLRenderable.h"

SDLRenderer* SDLRenderer::_instance = 0;

/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

SDLRenderer::~SDLRenderer()
{

}

SDLRenderer* SDLRenderer::GetInstance()
{
    if( _instance == NULL )
    {
        _instance = new SDLRenderer();
    }
    return _instance;
}

void SDLRenderer::Initialize( const int xRes, const int yRes, const int colourDepth )
{
    Renderer::Initialize( xRes, yRes, colourDepth );
   // initialize SDL video
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
// TODO: Use Logger instead of printf
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return;
    }

// TODO: Implement font support (below)
    /*TTF_Init();

    font=TTF_OpenFont("Vera.ttf", 32);

    // Render some text in solid black to a new surface
    // then blit to the upper left of the screen
    // then free the text surface
    //SDL_Surface *screen;
    SDL_Color color={255,255,255};
    text_surface = 0;
    text_surface=TTF_RenderText_Blended(font,"Cool Tactics Game!",color);
    printf( "Rendering text result=%i\n", text_surface );*/
    //handle error here, perhaps print TTF_GetError at least


    // create a new window
    mScreen = SDL_SetVideoMode(xRes, yRes, colourDepth, SDL_HWSURFACE|SDL_DOUBLEBUF);

    if ( !mScreen )
    {
        printf("Unable to set %ix%i video: %s\n", xRes, yRes, SDL_GetError());
        return;
    }
/*
    // load an image
    bmp = SDL_LoadBMP("cb.bmp");
    if (!bmp)
    {
        printf("Unable to load bitmap: %s\n", SDL_GetError());
        return 1;
    }

    // centre the bitmap on screen
    dstrect.x = (screen->w - bmp->w) / 2;
    dstrect.y = (screen->h - bmp->h) / 2;*/
}

void SDLRenderer::Shutdown()
{
    //SDL_FreeSurface(bmp);

    //perhaps we can reuse it, but I assume not for simplicity.
    //SDL_FreeSurface(text_surface);

    //TTF_CloseFont(font);
    //TTF_Quit();

    SDL_Quit();
}

//============================= OPERATORS ====================================
//============================= OPERATIONS ===================================

void SDLRenderer::Draw()
{
    // clear screen
    SDL_FillRect(mScreen, 0, SDL_MapRGB(mScreen->format, 0, 0, 0));

    // DRAWING STARTS HERE

    for( RenderableVecItr i = mRenderQueue.begin(); i != mRenderQueue.end(); ++i )
    {
        (*i)->RenderSelf( mScreen );
    }

    // TODO: Remove this code, it's just here for testing
    /*static unsigned int xDir = 1;
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

    // draw text
    SDL_BlitSurface(text_surface,NULL,screen,NULL);

    // end TODO test code
*/
    // DRAWING ENDS HERE

    // finally, update the screen :)
    SDL_Flip(mScreen);
}

void SDLRenderer::AddToRenderQueue( SDLRenderable * toAdd )
{
    mRenderQueue.push_back( toAdd );
}

void SDLRenderer::RemoveFromRenderQueue( SDLRenderable * toRemove )
{
    for( RenderableVecItr i = mRenderQueue.begin(); i != mRenderQueue.end(); ++i )
    {
        if( *i == toRemove )
        {
            mRenderQueue.erase( i );
            break;
        }
    }
}

void SDLRenderer::DrawImageAt( SDL_Surface* src, const int x, const int y, const int width, const int height, SDL_Surface* dest )
{
    SDL_Rect dstrect;
    dstrect.x = x;
    dstrect.y = y;
    dstrect.w = width;
    dstrect.h = height;
    SDL_BlitSurface(src, 0, dest, &dstrect);
}

//============================= ACCESS     ===================================
//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

SDLRenderer::SDLRenderer(void)
: Renderer()
{

}

/////////////////////////////// PRIVATE    ///////////////////////////////////
