/**
 * File: SDLRenderer.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Karl Schmidt, March 26 2007    | Added support for drawing an image to the screen
 								    with a particular alpha value
 * Karl Schmidt, March 26 2007    | Added helper function AddAnimation
 * Karl Schmidt, March 23 2007    | Got rid of more using namespace std; usage
 * Karl Schmidt, March 22 2007    | Correcting include orders and paths
 * Karl Schmidt, March 21 2007    | Added support for black-backround rendering behind text
 * Karl Schmidt, February 15 2007 | Added temporary renderable functionality
 * Karl Schmidt, February 13 2007 | Added joystick init to SDL parameters
 * Karl Schmidt, February 11 2007 | Disabled the mouse cursor, added custom window title, more error/info logging
 * Karl Schmidt, February 10 2007 | Added SDL_INIT_AUDIO flag to SDL_Init
 * Karl Schmidt, February 8 2007  | Initial creation of cpp file
 */

#include "SDLRenderer.h"                                // class implemented

#include <util.h>

#include <SDL/SDL.h>

#include <Renderer/SDLRenderable.h>
#include <Logger.h>


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
        LogCritical( std::string("Unable to init SDL: ") + std::string( SDL_GetError() ) );
        return;
    }

    SDL_ShowCursor( SDL_DISABLE );

    // Initialize the font library
    TTF_Init();

    // Preload our typical font size
    mFonts[32] = TTF_OpenFont( fontName, 32);

    // create a new window
    mScreen = SDL_SetVideoMode(xRes, yRes, colourDepth, SDL_HWSURFACE|SDL_DOUBLEBUF);

    mTransTempScreen = SDL_CreateRGBSurface( mScreen->flags, xRes, yRes, colourDepth, mScreen->format->Rmask,
                                             mScreen->format->Gmask, mScreen->format->Bmask, mScreen->format->Amask );

    tacAssert( mScreen );
    if ( !mScreen )
    {
        LogError( std::string("Unable to set video mode: ") + toString(xRes) + std::string(" ") + toString(yRes) + std::string("SDL error is: ") + toString(SDL_GetError()) + std::string(")") );
        printf("Unable to set %ix%i video: %s\n", xRes, yRes, SDL_GetError());
        return;
    }

    SDL_WM_SetCaption( "SymTac Alpha 2", NULL );

    LogInfo( std::string("Set video mode: ") + toString(xRes) + std::string(" ") + toString(yRes) );
    LogInfo( "The SDLRenderer has been initialized successfully." );
}

void SDLRenderer::Shutdown()
{
    LogInfo( "Beginning SDLRenderer shut down..." );

    for( TempRenderableItr i = mTempRenderables.begin(); i != mTempRenderables.end(); ++i )
    {
        delete i->first;
    }
    mTempRenderables.clear();

    for( FontMapItr i = mFonts.begin(); i != mFonts.end(); ++i )
    {
        TTF_CloseFont( i->second );
    }
    TTF_Quit();

    if( mTransTempScreen )
    {
        SDL_FreeSurface( mTransTempScreen );
        mTransTempScreen = NULL;
    }

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
        if( i->second.second < currentTime && find( mRenderQueue.begin(), mRenderQueue.end(), i->first ) == mRenderQueue.end() )
        {
            mRenderQueue.push_back( i->first );
        }

        // If it is expired...
        if( i->second.first < currentTime )
        {
            // Find it in the renderqueue and turf it
            RenderableVecItr j = find( mRenderQueue.begin(), mRenderQueue.end(), i->first );
            if( j != mRenderQueue.end() )
            {
                mRenderQueue.erase( j );
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

void SDLRenderer::AddToTempRenderQueue( SDLRenderable * toAdd, const Uint32 timeToRemove, const Uint32 timeToStart )
{
    mTempRenderables.push_back( TempRenderable( toAdd, TimeStartEndPair(timeToRemove, timeToStart) ) );

    if( timeToStart == 0 )
    {
        mRenderQueue.push_back( toAdd );
    }
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

SDL_Surface* SDLRenderer::CreateTextSurface( const std::string & textToRender, const int size, const int red, const int green, const int blue,
                                             const bool backBlack )
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

    SDL_Color colour = { red, green, blue, 255 };
    SDL_Color bgColour = { 0, 0, 0, 255 };

    SDL_Surface* textSurface = NULL;
    if( backBlack )
    {
        textSurface = TTF_RenderText_Shaded( mFonts[size], textToRender.c_str(), colour, bgColour );
    }
    else
    {
        textSurface = TTF_RenderText_Blended( mFonts[size], textToRender.c_str(), colour );
    }

    tacAssert( textSurface );
    if( !textSurface )
    {
        LogError( std::string("Could not render text to surface, given text: ") + textToRender + std::string(", TTF_GetError says: ") + std::string( TTF_GetError() ) );
        return NULL;
    }

    return textSurface;
}

void SDLRenderer::DrawImageAt( SDL_Surface* src, const int x, const int y, const int width, const int height, SDL_Surface* dest, const Uint32 alpha )
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

    if( alpha == 255 )
    {
        SDL_BlitSurface( src, 0, dest, &dstrect );
    }
    else
    {
        SDL_SetAlpha( mTransTempScreen, SDL_SRCALPHA | SDL_RLEACCEL, alpha );
        SDL_BlitSurface( src, 0, mTransTempScreen, &dstrect );
        SDL_BlitSurface( mTransTempScreen, &dstrect, dest, &dstrect );
    }
}

void SDLRenderer::AddAnimation( const SDLRenderableVec & frames, const Uint32 delay, const Uint32 initialDelay )
{
    Uint32 baseTime = initialDelay;
    if( baseTime == 0 )
    {
        baseTime = SDL_GetTicks();
    }
    for( SDLRenderableConstItr i = frames.begin(); i != frames.end(); ++i )
    {
        AddToTempRenderQueue( *i, baseTime + delay, baseTime );
        baseTime += delay;
    }
}

//============================= ACCESS     ===================================
//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

SDLRenderer::SDLRenderer(void)
: Renderer(), mScreen( NULL ), mTransTempScreen( NULL )
{

}

/////////////////////////////// PRIVATE    ///////////////////////////////////
