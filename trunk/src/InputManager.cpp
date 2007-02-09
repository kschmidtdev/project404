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
    // stub
}

void InputManager::Shutdown()
{
    // stub
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
    for( EventListenerItr i = mRegisteredListeners.begin(); i != mRegisteredListeners.end(); ++i )
    {
        (*i)->ProcessEvent( RIGHT );
        // THIS IS JUST A BAD HARDCODED TEST CASE
    }
    // stub
}

//============================= ACCESS     ===================================
//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

InputManager::InputManager(void)
{
    // stub
}

void InputManager::SetupKeyBindings()
{
    // stub
}

/////////////////////////////// PRIVATE    ///////////////////////////////////
