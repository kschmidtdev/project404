/**
 * File: InputManager.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Karl Schmidt, February 13 2007 | Added joystick support
 * Karl Schmidt, February 12 2007 | Added corner direction event sending changes
 * Karl Schmidt, February 9 2007 | Initial creation, all functions stubbed
 */
#include "InputManager.h"                                // class implemented

#include "EventListener.h"
#include "Logger.h"
#include <util.h>

/////////////////////////////// PUBLIC ///////////////////////////////////////

// Axis movement values aren't exactly 0 when the directional pad 'moves back to the center'
const int JOY_MOVEMENT_DAMPENING = 1000;

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
    if( SDL_NumJoysticks() > 0 )
    {
        // Open joystick
        mJoyStick = SDL_JoystickOpen(0);
        tacAssert( mJoyStick );
    }
    if( mJoyStick )
    {
        LogInfo( string("Opened Joystick 0: Name: ") + toString(SDL_JoystickName( 0 )) +
                 string(" Number of Axes: ") + toString(SDL_JoystickNumAxes( mJoyStick )) +
                 string(" Number of Buttons: ") + toString(SDL_JoystickNumButtons( mJoyStick )) +
                 string(" Number of Balls: ") + toString(SDL_JoystickNumBalls( mJoyStick )) );
    }
    else
    {
        LogInfo( "No joystick found." );
    }

    SetupKeyBindings();
    LogInfo( "The InputManager has been initialized successfully." );
}

void InputManager::Shutdown()
{
    if( SDL_JoystickOpened(0) && mJoyStick )
    {
        SDL_JoystickClose( mJoyStick );
        mJoyStick = NULL;
    }

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
    int foundBoundKey = -1;

    // translate Keyboard SDLEvent into appropriate key
    for( int i( 0 ); i < KEYCOUNT; ++i )
    {
        if( mKeys[i] == evt->key.keysym.sym )
        {
            foundBoundKey = i;
            break;
        }
    }

    // If there is a joystick, translate it's events
    if( mJoyStick )
    {
        // For directional movement (dampened because movement to the center
        // is not 0
        if( evt->jaxis.type == SDL_JOYAXISMOTION )
        {
            if( evt->jaxis.axis == 0 ) // X axis
            {
                if( evt->jaxis.value < -JOY_MOVEMENT_DAMPENING )
                {
                    foundBoundKey = LEFT;
                }
                else if( evt->jaxis.value > JOY_MOVEMENT_DAMPENING )
                {
                    foundBoundKey = RIGHT;
                }
            }
            else if( evt->jaxis.axis == 1 ) // Y axis
            {
                if( evt->jaxis.value < -JOY_MOVEMENT_DAMPENING )
                {
                    foundBoundKey = UP;
                }
                else if( evt->jaxis.value > JOY_MOVEMENT_DAMPENING )
                {
                    foundBoundKey = DOWN;
                }
            }
        }
        else if( evt->jbutton.type == SDL_JOYBUTTONUP ) // Button presses
        {
            for( int i( 0 ); i < KEYCOUNT; ++i )
            {
                if( mJButtons[i] == evt->jbutton.button )
                {
                    foundBoundKey = i;
                    break;
                }
            }
        }
    }

    if( foundBoundKey != -1 )
    {
        // We typically won't be using the corner directions,
        // so events are sent separately for LEFTUP (ie: LEFT then UP)
        if( foundBoundKey == LEFTUP )
        {
            SendEventToListeners( LEFT );
            SendEventToListeners( UP );
        }
        else if( foundBoundKey == LEFTDOWN )
        {
            SendEventToListeners( LEFT );
            SendEventToListeners( DOWN );
        }
        else if( foundBoundKey == RIGHTUP )
        {
            SendEventToListeners( LEFT );
            SendEventToListeners( UP );
        }
        else if( foundBoundKey == RIGHTDOWN )
        {
            SendEventToListeners( LEFT );
            SendEventToListeners( UP );
        }
        else // the usual
        {
            SendEventToListeners( INPUTKEYS( foundBoundKey ) );
        }
    }
}

//============================= ACCESS     ===================================
//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

InputManager::InputManager(void)
: mJoyStick( NULL )
{
    for( int i( 0 ); i < KEYCOUNT; ++i )
    {
        mKeys[i] = 0;
        mJButtons[i] = -1; // 0 is a valid button value for joystick buttons
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

    mJButtons[START] = 9;
    mJButtons[SELECT] = 8;
    mJButtons[CONFIRM] = 2;
    mJButtons[CANCEL] = 1;
    mJButtons[MENU] = 3;
}

void InputManager::SendEventToListeners( const INPUTKEYS evt )
{
    for( EventListenerItr i = mRegisteredListeners.begin(); i != mRegisteredListeners.end(); ++i )
    {
        (*i)->ProcessEvent( evt );
    }
}

/////////////////////////////// PRIVATE    ///////////////////////////////////