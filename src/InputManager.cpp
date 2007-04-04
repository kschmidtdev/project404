/**
 * File: InputManager.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Karl Schmidt, February 9 2007  | Initial creation, all functions stubbed
 * Karl Schmidt, February 12 2007 | Added corner direction event sending changes
 * Karl Schmidt, February 13 2007 | Added joystick support
 * Karl Schmidt, March 14 2007    | Added event recording/playback support
 * Karl Schmidt, March 15 2007    | Made a few fixes, but event recording/playback still isn't stable
 * Karl Schmidt, March 21 2007    | Added directional-key auto-repeat, storing/loading rand seed in key recording file
 * Karl Schmidt, March 22 2007    | Fixed a bug where auto-repeated key events weren't being logged during recording
 * Karl Schmidt, March 23 2007    | Got rid of more using namespace std; usage
 * Karl Schmidt, April 3 2007     | Added ResetKeysDown to reset all keydown states
 */

#include "InputManager.h"                                // class implemented

#include <util.h>
#include <algorithm>

#include "EventListener.h"
#include "Logger.h"

/////////////////////////////// PUBLIC ///////////////////////////////////////

// Axis movement values aren't exactly 0 when the directional pad 'moves back to the center'
const int JOY_MOVEMENT_DAMPENING = 1000;

const int AUTO_REPEAT_DELAY_MS = 200;

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

void InputManager::Initialize( const INPUT_MODE mode, const std::string & recPlayFileName )
{
    if( SDL_NumJoysticks() > 0 )
    {
        // Open joystick
        mJoyStick = SDL_JoystickOpen(0);
        tacAssert( mJoyStick );
    }
    if( mJoyStick )
    {
        LogInfo( std::string("Opened Joystick 0: Name: ") + toString(SDL_JoystickName( 0 )) +
                 std::string(" Number of Axes: ") + toString(SDL_JoystickNumAxes( mJoyStick )) +
                 std::string(" Number of Buttons: ") + toString(SDL_JoystickNumButtons( mJoyStick )) +
                 std::string(" Number of Balls: ") + toString(SDL_JoystickNumBalls( mJoyStick )) );
    }
    else
    {
        LogInfo( "No joystick found." );
    }

    SetupKeyBindings();

    mMode = mode;
    if( mMode != NORMAL )
    {
        mRecPlayFileName = recPlayFileName;
        if( mMode == PLAYBACK )
        {
            LoadKeyListFromFile( mRecPlayFileName );
            if( !mKeyList.empty() )
            {
                mCurrentPlaybackKey = mKeyList.begin();
                srand( *mCurrentPlaybackKey ); // Seeding by the stored seed value (stored at the top of the recorded file)
                ++mCurrentPlaybackKey;
            }
        }
        else if( mMode == RECORDING )
        {
            unsigned int seedValue = time(NULL);
            mKeyList.push_back( seedValue );
            SaveKeyToFile( mRecPlayFileName, seedValue );
            srand( seedValue ); // Seeding by same value so we don't get a the AI doing different things on playback
        }
    }

    LogInfo( "The InputManager has been initialized successfully." );
}

void InputManager::Shutdown()
{
    if( SDL_JoystickOpened(0) && mJoyStick )
    {
        SDL_JoystickClose( mJoyStick );
        mJoyStick = NULL;
    }

    if( mMode == RECORDING )
    {
        SaveKeyListToFile( mRecPlayFileName );
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
            return;
        }
    }
    LogError( "An event listener has been requested to be removed, but does not exist on the list" );
}

void InputManager::ProcessEvent( const SDL_Event* evt )
{
    if( mMode == PLAYBACK )
    {
        return;
    }

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

    // If a bound key was pressed...
    if( foundBoundKey != -1 )
    {
        // If it was a keydown event, set our internal keystate for that key is that it is down
        if( evt->type == SDL_KEYDOWN )
        {
            mKeyState[foundBoundKey] = true;
            // Increment this time so we don't auto-repeat right away (this is probably not a great way of doing this)
            mLastAutoRepeatTime = SDL_GetTicks() + AUTO_REPEAT_DELAY_MS;
        }
        else if( evt->type == SDL_KEYUP ) // If it was a keyup, update our records so we know the key isn't being pressed anymore
        {
            mKeyState[foundBoundKey] = false;
        }
    }

    // If a bound key event was sent, and that key is currently down, process it
    if( foundBoundKey != -1 && mKeyState[foundBoundKey] )
    {
        // We typically won't be using the corner directions,
        // so events are sent separately for LEFTUP (ie: LEFT then UP)
        if( foundBoundKey == LEFTUP )
        {
            SendEventToListeners( LEFT );
            SendEventToListeners( UP );
            if( mMode == RECORDING )
            {
                mKeyList.push_back( LEFT );
                mKeyList.push_back( UP );
            }
        }
        else if( foundBoundKey == LEFTDOWN )
        {
            SendEventToListeners( LEFT );
            SendEventToListeners( DOWN );
            if( mMode == RECORDING )
            {
                mKeyList.push_back( LEFT );
                mKeyList.push_back( DOWN );
            }
        }
        else if( foundBoundKey == RIGHTUP )
        {
            SendEventToListeners( RIGHT );
            SendEventToListeners( UP );
            if( mMode == RECORDING )
            {
                mKeyList.push_back( RIGHT );
                mKeyList.push_back( UP );
            }
        }
        else if( foundBoundKey == RIGHTDOWN )
        {
            SendEventToListeners( RIGHT );
            SendEventToListeners( UP );
            if( mMode == RECORDING )
            {
                mKeyList.push_back( RIGHT );
                mKeyList.push_back( UP );
            }
        }
        else // the usual
        {
            if( mMode == RECORDING )
            {
                mKeyList.push_back( foundBoundKey );
                SaveKeyToFile( mRecPlayFileName, INPUTKEYS(foundBoundKey) );
            }
            SendEventToListeners( INPUTKEYS( foundBoundKey ) );
        }
    }
}

void InputManager::Update()
{
    if( mMode == PLAYBACK )
    {
        if( mCurrentPlaybackKey != mKeyList.end() )
        {
            SendEventToListeners( INPUTKEYS(*mCurrentPlaybackKey) );
            //printf( "Sending key: %i\n", *mCurrentPlaybackKey );
            ++mCurrentPlaybackKey;
        }
        else
        {
            LogInfo("Key playback over.");
            mMode = NORMAL;
        }
        SDL_Delay( 50 );
    }
    else // Recording or playing normally
    {
        // We don't want to send an auto-repeat every since Update, that would make it happen too much
        if( mLastAutoRepeatTime < SDL_GetTicks() )
        {
            // If it's a directional key (no point auto-repeating confirm, cancel, etc
            for( int i = 0; i < LAST_DIRECTION+1; ++i )
            {
                if( mKeyState[i] )
                {
                    if( mMode == RECORDING )
                    {
                        mKeyList.push_back( i );
                        SaveKeyToFile( mRecPlayFileName, INPUTKEYS(i) );
                    }
                    SendEventToListeners( INPUTKEYS( i ) );
                }
            }
            mLastAutoRepeatTime = SDL_GetTicks() + AUTO_REPEAT_DELAY_MS;
        }
    }
}

//============================= ACCESS     ===================================
//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

InputManager::InputManager(void)
: mJoyStick( NULL ),
  mMode( NORMAL ),
  mRecPlayFileName( "" ),
  mLastAutoRepeatTime( 0 )
{
    std::fill( &mKeys[0], &mKeys[KEYCOUNT], 0 );
    std::fill( &mJButtons[0], &mJButtons[KEYCOUNT], -1 );
    std::fill( &mKeyState[0], &mKeyState[KEYCOUNT], false );
}

void InputManager::SetupKeyBindings()
{
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

void InputManager::LoadKeyListFromFile( const std::string & fileName )
{
    FILE* keyListFileHandle = NULL;
    keyListFileHandle = fopen( fileName.c_str(), "r" );

    if( keyListFileHandle )
    {
        LogInfo( "Loading keys from " + fileName );

        int value = 0;
        // While we're not at the end of the file...
        while ( !feof( keyListFileHandle ) )
        {
        	// Load in a line of text formatted like "text #" (where # is some integer)
            fscanf( keyListFileHandle, "%i\n", &value );
            mKeyList.push_back( INPUTKEYS( value ) );
            LogInfo( std::string("Loaded recorded key with value: ") + toString(value) );
        }

        fclose( keyListFileHandle );
    }
    else
    {
        tacAssert( false );
        LogWarning( fileName + std::string(" file not found, no keys to playback") );
    }
}

void InputManager::SaveKeyListToFile( const std::string & fileName )
{
    if( mKeyList.empty() )
    {
        // Nothing to write
        return;
    }

    FILE* keyListFileHandle = NULL;
    keyListFileHandle = fopen( fileName.c_str(), "w" );

    if( keyListFileHandle )
    {
        LogInfo( "Saving recorded keys to " + fileName );
        for( KeyVecItr i = mKeyList.begin(); i != mKeyList.end(); ++i )
        {
            fprintf( keyListFileHandle, "%i\n", *i );
        }

        fclose( keyListFileHandle );
    }
    else
    {
        // Unable to write to file for some reason
        tacAssert( false );
        LogWarning( fileName + std::string(": Unable to write to key list file") );
    }
}

void InputManager::SaveKeyToFile( const std::string & fileName, const int key )
{
    static bool firstTime = true;

    FILE* keyListFileHandle = NULL;
    if( firstTime )
    {
        keyListFileHandle = fopen( fileName.c_str(), "w" );
        firstTime = false;
    }
    else
    {
        keyListFileHandle = fopen( fileName.c_str(), "a" );
    }


    if( keyListFileHandle )
    {
        //printf( "Recording key: %i\n", key );
        fprintf( keyListFileHandle, "%i\n", key );
        fclose( keyListFileHandle );
    }
    else
    {
        // Unable to write to file for some reason
        tacAssert( false );
        LogWarning( fileName + std::string(": Unable to write to key list file") );
    }
}

void InputManager::ResetKeysDown()
{
    std::fill( &mKeyState[0], &mKeyState[KEYCOUNT], false );
}

/////////////////////////////// PRIVATE    ///////////////////////////////////
