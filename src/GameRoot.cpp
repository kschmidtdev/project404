/**
 * File: GameRoot.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Karl Schmidt, February 15 2007 | Added SecurityManager loading password hash file
 * Mike Malyuk,  February 15 2007 | Added looping for AI
 * Karl Schmidt, February 15 2007 | Added hardcoded battle initialization for v1
 * Karl Schmidt, February 13 2007 | Added config file parsing, some hardcoded value cleanup, enabled all managers
 * Karl Schmidt, February 11 2007 | Added background music implementation
 * Karl Schmidt, February 11 2007 | Initial creation of implementation
 * Karl Schmidt, March 13 2007    | Added sound system disabling, mainly for unit tests
 * Karl Schmidt, March 14 2007    | Added event recording/playback support
 * Seung Woo Han, March 15 2007   | Added DBEngine and DBEngine initialization.
 * Karl Schmidt, March 15 2007	  | Removed DBEngine init, it is our save-game so we load later on
 * Karl Schmidt, March 15 2007	  | Added support for -encrypt parameter
 * Karl Schmidt, March 16 2007    | Fixed infinite loop state bug, recorded event playback now works!
 * Karl Schmidt, March 21 2007    | Added support for SDL_KEYDOWN handling in InputManager
 */

#include "GameRoot.h"                                // class implemented

#include <Logger.h>
#include <util.h>

#include <SecurityManager.h>
#include <Database/DatabaseManager.h>
#include <Database/DBEngine.h>
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
  mUIManager( NULL ),
  mRecordFileName(""),
  mPlaybackFileName("")
{
    mSettings["width"] = 640;
    mSettings["height"] = 480;
    mSettings["depth"] = 32;
    mSettings["soundEnabled"] = 1;
}// GameRoot

GameRoot::~GameRoot()
{
}// ~GameRoot

void GameRoot::Initialize( const int argc, char** argv, const bool soundEnabled )
{
    Logger* logger = Logger::GetInstance( logFileName );
    logger->Initialize();

    LoadConfigFileSettings( configFileName );
    ProcessCommandLine( argc, argv );

    // If they both are not empty
    tacAssert( !(!mRecordFileName.empty() && !mPlaybackFileName.empty()) );

    if( (!mRecordFileName.empty() && !mPlaybackFileName.empty()) )
    {
        LogWarning( "You cannot set playback mode AND record mode, over-writing to playback mode" );
        mRecordFileName = "";
    }

    mRenderer = SDLRenderer::GetInstance();
    mRenderer->Initialize( mSettings["width"], mSettings["height"], mSettings["depth"] );

    mResManager = ResourceManager::GetInstance();
    mResManager->Initialize();

    mInput = InputManager::GetInstance();

    if( !mRecordFileName.empty() )
    {
        mInput->Initialize( InputManager::RECORDING, mRecordFileName );
    }
    else if( !mPlaybackFileName.empty() )
    {
        mInput->Initialize( InputManager::PLAYBACK, mPlaybackFileName );
    }
    else if( mSettings.find("recordMode") != mSettings.end() && mSettings["recordMode"] == 1 )
    {
        mInput->Initialize( InputManager::RECORDING, "recordedKeys" );
    }
    else
    {
        mInput->Initialize();
    }

    if( !soundEnabled )
    {
        mSettings["soundEnabled"] = 0;
    }

    mSoundManager = SoundManager::GetInstance();
    mSoundManager->Initialize( static_cast<bool>( mSettings["soundEnabled"] ) );

    mSecurityManager = SecurityManager::GetInstance();
    mSecurityManager->Initialize();

    mSecurityManager->LoadPasswordHashFile( "passwords" );

    mDatabase = DatabaseManager::GetInstance();
    mDatabase->Initialize();

    mDBEngine = DBEngine::GetInstance();

    if( mSettings.find( "encrypt" ) != mSettings.end() )
    {
        mDBEngine->Initialize();
        mDBEngine->SaveEncryptedFile( "databaseEncrypted.xml" );
    }

    mGameEngine = GameEngine::GetInstance();

    mUIManager = UIManager::GetInstance();
    mUIManager->Initialize();
}

void GameRoot::Shutdown()
{
    mUIManager->Shutdown();

    mGameEngine->Shutdown();

    mDatabase->Shutdown();

    mDBEngine->Shutdown();

    mSecurityManager->SavePasswordHashFile( "passwords" );
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
        if((mGameEngine != NULL) && ((mGameEngine->GetLevel() && mGameEngine->GetLevel()->GetTurn()) ||
          ( mGameEngine != NULL && mGameEngine->GetLevel() == NULL ) ||
          ( mGameEngine != NULL && ( mGameEngine->GetLevel()->GetWinCondition() || mGameEngine->GetLevel()->GetLoseCondition() ))) )
        {
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
                    case SDL_KEYUP:
                    {
                        mInput->ProcessEvent( &event );
                        // exit if ESCAPE is pressed
                        if (event.key.keysym.sym == SDLK_ESCAPE)
                            done = true;
                        break;
                    }
                } // end switch
            } // end of message processing
            mInput->Update();
        }
        else
        {
            if( mGameEngine->GetAI() && mGameEngine->GetLevel() && ( !mGameEngine->GetLevel()->GetWinCondition() && !mGameEngine->GetLevel()->GetLoseCondition() ) )
            {
                const Point inputPt = mGameEngine->GetAI()->DoAction();
                mUIManager->GetLayout("BattleScreen")->GetGrid()->ConfirmFunction(inputPt);
            }
        }
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

void GameRoot::ProcessCommandLine( const int argc, char** argv )
{
    for( int i = 0; i < argc; ++i )
    {
        if( strcmp( argv[i], "-record") == 0 )
        {
            if( argv[i+1] != NULL && (argv[i+1])[0] != '-' )
            {
                mRecordFileName = argv[i+1];
                ++i;
            }
            else
            {
                LogError( "-record was passed with no filename" );
            }
        }
        else if( strcmp( argv[i], "-playback") == 0 )
        {
            if( argv[i+1] != NULL && (argv[i+1])[0] != '-' )
            {
                mPlaybackFileName = argv[i+1];
                ++i;
            }
            else
            {
                LogError( "-playback was passed with no filename" );
            }
        }
        else if( strcmp( argv[i], "-encrypt") == 0 )
        {
            mSettings["encrypt"] = 1;
        }
    }
}

//============================= OPERATORS ====================================
//============================= OPERATIONS ===================================
//============================= ACCESS     ===================================
//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
