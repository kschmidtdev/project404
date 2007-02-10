/**
 * File: InputManager.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Karl Schmidt, February 9 2007 | Initial creation, all functions stubbed
 */
#include "InputManager.h"                                // class implemented

#include "EventListener.h"
#include "Logger.h"

/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

InputManager* InputManager::_instance = 0;

InputManager* InputManager::GetInstance()
{
    if( !_instance )
    {
        _instance = new InputManager();
    }
    return _instance;
}
InputManager::~InputManager(void)
{
    // stub
}

void InputManager::Initialize()
{
    SetupKeyBindings();
    LogInfo( "The InputManager has been initialized successfully." );
}

void InputManager::Shutdown()
{
    delete _instance;
    _instance = NULL;
    LogInfo( "The InputManager has been shut down successfully." );
}

//============================= OPERATORS ====================================
//============================= OPERATIONS ===================================

void InputManager::AddEventListener( EventListener* toAdd )
{
    mRegisteredListeners.push_back( toAdd );
}

void InputManager::RemoveEventListener( EventListener* toRemove )
{
    for( EventListenerItr i = mRegisteredListeners.begin(); i != mRegisteredListeners.end(); ++i )
    {
        if( (*i) == toRemove )
        {
            mRegisteredListeners.erase( i );
            break;
        }
    }
    // TODO: Add logging if could not find the eventlistener requested to remove
}

void InputManager::ProcessEvent( const SDL_Event* evt )
{
    // translate SDLEvent into appropriate key
    int foundBoundKey = -1;
    for( int i( 0 ); i < KEYCOUNT; ++i )
    {
        if( mKeys[i] == evt->key.keysym.sym )
        {
            foundBoundKey = i;
            break;
        }
    }

    if( foundBoundKey != -1 )
    {
        for( EventListenerItr i = mRegisteredListeners.begin(); i != mRegisteredListeners.end(); ++i )
        {
            (*i)->ProcessEvent( INPUTKEYS( foundBoundKey ) );
        }
    }
}

//============================= ACCESS     ===================================
//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

InputManager::InputManager(void)
{
    for( int i( 0 ); i < KEYCOUNT; ++i )
    {
        mKeys[i] = 0;
    }
}

void InputManager::SetupKeyBindings()
{
    // TODO: This is for keyboard-only until we expand it
    mKeys[UP] = SDLK_UP;
    mKeys[LEFTUP] = SDLK_HOME;
    mKeys[LEFT] = SDLK_LEFT;
    mKeys[LEFTDOWN] = SDLK_END;
    mKeys[DOWN] = SDLK_DOWN;
    mKeys[RIGHTDOWN] = SDLK_PAGEDOWN;
    mKeys[RIGHT] = SDLK_RIGHT;
    mKeys[RIGHTUP] = SDLK_PAGEUP;

    mKeys[START] = SDLK_s;
    mKeys[SELECT] = SDLK_a;
    mKeys[CONFIRM] = SDLK_RETURN;
    mKeys[CANCEL] = SDLK_BACKSPACE;
    mKeys[MENU] = SDLK_m;
}

/////////////////////////////// PRIVATE    ///////////////////////////////////
