/**
 * File: SDLRenderer.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Karl Schmidt, February 15 2007 | Added temporary renderable functionality
 * Karl Schmidt, February 13 2007 | Added joystick init to SDL parameters
 * Karl Schmidt, February 11 2007 | Disabled the mouse cursor, added custom window title, more error/info logging
 * Karl Schmidt, February 10 2007 | Added SDL_INIT_AUDIO flag to SDL_Init
 * Karl Schmidt, February 8 2007 | Initial creation of cpp file
 */
#include "SDLRenderer.h"                                // class implemented

#include "SDLRenderable.h"
#include "Logger.h"

#include <util.h>

SDLRenderer* SDLRenderer::_instance = 0;

const char* fontName( "Vera.ttf" );

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
    LogInfo( "Beginning SDLRenderer initialization..." );
    Renderer::Initialize( xRes, yRes, colourDepth );

   // initialize SDL video
    if ( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_JOYSTICK ) < 0 )
    {
        tacAssert( false ); // Always assert if this happens
        LogCritical( string("Unable to init SDL: ") + string( SDL_GetError() ) );
        return;
    }

    SDL_ShowCursor( SDL_DISABLE );

    // Initialize the font library
    TTF_Init();

    // Preload our typical font size
    mFonts[32] = TTF_OpenFont( fontName, 32);

    // create a new window
    mScreen = SDL_SetVideoMode(xRes, yRes, colourDepth, SDL_HWSURFACE|SDL_DOUBLEBUF);

    tacAssert( mScreen );
    if ( !mScreen )
    {
        LogError( string("Unable to set video mode: ") + toString(xRes) + string(" ") + toString(yRes) + string("SDL error is: ") + toString(SDL_GetError()) + string(")") );
        printf("Unable to set %ix%i video: %s\n", xRes, yRes, SDL_GetError());
        return;
    }

    SDL_WM_SetCaption( "SymTac Alpha 1", NULL );

    LogInfo( string("Set video mode: ") + toString(xRes) + string(" ") + toString(yRes) );
    LogInfo( "The SDLRenderer has been initialized successfully." );
}

void SDLRenderer::Shutdown()
{
    LogInfo( "Beginning SDLRenderer shut down..." );

    for( FontMapItr i = mFonts.begin(); i != mFonts.end(); ++i )
    {
        TTF_CloseFont( i->second );
    }
    TTF_Quit();

    SDL_Quit();

    delete _instance;
    _instance = NULL;
    LogInfo( "The SDLRenderer has been shut down successfully." );
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

    Uint32 currentTime = SDL_GetTicks();
    for( TempRenderableItr i = mTempRenderables.begin(); i != mTempRenderables.end(); ++i )
    {
        // If it is expired...
        if( i->second < currentTime )
        {
            // Find it in the renderqueue and turf it
            for( RenderableVecItr j = mRenderQueue.begin(); j != mRenderQueue.end(); ++j )
            {
                if( i->first == (*j)  )
                {
                    mRenderQueue.erase( j );
                    break;
                }
            }
            delete i->first;
            i = mTempRenderables.erase( i );
            --i;
        }
    }

    SDL_Flip(mScreen);
}

void SDLRenderer::AddToRenderQueue( SDLRenderable * toAdd )
{
    mRenderQueue.push_back( toAdd );
}

void SDLRenderer::AddToTempRenderQueue( SDLRenderable * toAdd, const Uint32 timeToRemove )
{
    mTempRenderables.push_back( TempRenderable( toAdd, timeToRemove ) );
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

SDL_Surface* SDLRenderer::CreateTextSurface( const string textToRender, const int size, const int red = 255, const int green = 255, const int blue = 255 )
{
    tacAssert( textToRender != "" );
    tacAssert( red >= 0 );
    tacAssert( green >= 0 );
    tacAssert( blue >= 0 );
    tacAssert( size > 0 );

    if( mFonts.find( size ) == mFonts.end() )
    {
        mFonts[size] = TTF_OpenFont( fontName, size );
    }

    // Render some text in solid black to a new surface
    // then blit to the upper left of the screen
    // then free the text surface
    SDL_Color colour = { red, green, blue, 255 };

    SDL_Surface* textSurface = NULL;
    textSurface = TTF_RenderText_Blended( mFonts[size], textToRender.c_str(), colour );

    tacAssert( textSurface );
    if( !textSurface )
    {
        LogError( string("Could not render text to surface, given text: ") + textToRender + string(", TTF_GetError says: ") + string( TTF_GetError() ) );
        return NULL;
    }

    return textSurface;
}

void SDLRenderer::DrawImageAt( SDL_Surface* src, const int x, const int y, const int width, const int height, SDL_Surface* dest )
{
    if( !src || !dest )
    {
        return;
    }
    tacAssert( src );
    tacAssert( dest );

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
: Renderer(), mScreen( NULL )
{

}

/////////////////////////////// PRIVATE    ///////////////////////////////////
