/**
 * File: GameRoot.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Karl Schmidt, February 15 2007 | Added hardcoded battle initialization for v1
 * Karl Schmidt, February 13 2007 | Added config file parsing, some hardcoded value cleanup, enabled all managers
 * Karl Schmidt, February 11 2007 | Added background music implementation
 * Karl Schmidt, February 11 2007 | Initial creation of implementation
 */
#include "GameRoot.h"                                // class implemented

#include <Logger.h>
#include <util.h>

#include <SecurityManager.h>
#include <Database/DatabaseManager.h>
#include <InputManager.h>
#include <Renderer/SDLRenderer.h>
#include <ResourceManager/ResourceManager.h>
#include <SoundManager.h>
#include <UIManager.h>
#include <GameEngine/GameEngine.h>

/////////////////////////////// PUBLIC ///////////////////////////////////////

const string bgMusicFileName( "Fantastic_B1-256.ogg" );
const string logFileName( "tacLogFile.txt" );
const string configFileName( "config.cfg" );

//============================= LIFECYCLE ====================================

GameRoot::GameRoot()
: mSecurityManager( NULL ),
  mDatabase( NULL ),
  mInput( NULL ),
  mRenderer( NULL ),
  mResManager( NULL ),
  mSoundManager( NULL ),
  mGameEngine( NULL ),
  mUIManager( NULL )
{
    mSettings["width"] = 640;
    mSettings["height"] = 480;
    mSettings["depth"] = 32;

}// GameRoot

GameRoot::~GameRoot()
{
}// ~GameRoot

void GameRoot::Initialize()
{
    Logger* logger = Logger::GetInstance( logFileName );
    logger->Initialize();

    LoadConfigFileSettings( configFileName );

    mRenderer = SDLRenderer::GetInstance();
    mRenderer->Initialize( mSettings["width"], mSettings["height"], mSettings["depth"] );

    mResManager = ResourceManager::GetInstance();
    mResManager->Initialize();

    mInput = InputManager::GetInstance();
    mInput->Initialize();

    mSoundManager = SoundManager::GetInstance();
    mSoundManager->Initialize();

    mSecurityManager = SecurityManager::GetInstance();
    mSecurityManager->Initialize();

    mDatabase = DatabaseManager::GetInstance();
    mDatabase->Initialize();

    mGameEngine = GameEngine::GetInstance();

    mUIManager = UIManager::GetInstance();
    mUIManager->Initialize();

	// Temporarily hardcoding this initialization (until the UI has the overmap that does this)
    vector<Character*> partyTemp;
    mGameEngine->BattleInit( partyTemp, GameEngine::CITYA );

}

void GameRoot::Shutdown()
{
    mUIManager->Shutdown();

    mGameEngine->Shutdown();

    mDatabase->Shutdown();

    mSecurityManager->Shutdown();

    mSoundManager->StopAllPlayback();

    mResManager->Shutdown();

    mSoundManager->Shutdown();

    mInput->Shutdown();

    mRenderer->Shutdown();

    Logger::GetInstance()->Shutdown();
}

void GameRoot::GameLoop()
{
    Mix_Music* gameMusic = mResManager->LoadMusic( bgMusicFileName );
    if( gameMusic )
    {
        mSoundManager->PlayMusic( gameMusic, true );
    }

    bool done = false;
    while (!done)
    {
        // message processing loop
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            // check for messages
            switch (event.type)
            {
                // exit if the window is closed
                case SDL_QUIT:
                done = true;
                break;

                // check for keypresses
                case SDL_JOYBUTTONDOWN:
                case SDL_JOYBUTTONUP:
                case SDL_JOYAXISMOTION:
                case SDL_KEYDOWN:
                {
                    mInput->ProcessEvent( &event );
                    // exit if ESCAPE is pressed
                    if (event.key.keysym.sym == SDLK_ESCAPE)
                        done = true;
                    break;
                }
            } // end switch
        } // end of message processing

        mRenderer->Draw();
        if( !done )
        {
            done = mUIManager->GetEndGameState();
        }
    }
    LogInfo( "The game has ended." );
}

void GameRoot::LoadConfigFileSettings( const string fileName )
{
    FILE* configFileHandle = NULL;
    configFileHandle = fopen( fileName.c_str(), "r" );

    if( configFileHandle )
    {
        LogInfo( "Loading values from " + fileName );

        char key[32];
        int value = 0;
        // While we're not at the end of the file...
        while ( !feof( configFileHandle ) )
        {
        	// Load in a line of text formatted like "text #" (where # is some integer)
            fscanf( configFileHandle, "%s %i\n", key, &value );
            if( key[0] != '#' ) // Allow for "comments" in the file
            {
                mSettings[string(key)] = value;
                LogInfo( string("Loaded key: ") + string(key) + string(" with value: ") + toString(value) );
            }
            else // Seek to the end of the line if you find a comment
            {
                while( fgetc( configFileHandle ) != '\n' && !feof( configFileHandle ) )
                {
                    fseek( configFileHandle, 1, SEEK_CUR );
                }
            }
        }

        fclose( configFileHandle );
    }
    else
    {
        // We should always have config.cfg present
        tacAssert( false );
        LogWarning( fileName + string(" file not found, using defaults") );
    }
}

//============================= OPERATORS ====================================
//============================= OPERATIONS ===================================
//============================= ACCESS     ===================================
//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
