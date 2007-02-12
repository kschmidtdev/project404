/**
 * File: GameRoot.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Karl Schmidt, February 11 2007 | Added background music implementation
 * Karl Schmidt, February 11 2007 | Initial creation of implementation
 */
#include "GameRoot.h"                                // class implemented

#include <Logger.h>

// TODO: Implement SecurityManager
//#include <SecurityManager.h>
#include <Database/DatabaseManager.h>
#include <InputManager.h>
#include <Renderer/SDLRenderer.h>
#include <ResourceManager/ResourceManager.h>
#include <SoundManager.h>
#include <UIManager.h>

// TODO: Include when GameEngine is ready
//#include <GameEngine.h>

/////////////////////////////// PUBLIC ///////////////////////////////////////

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
}// GameRoot

GameRoot::~GameRoot()
{
}// ~GameRoot

void GameRoot::Initialize()
{
    Logger* logger = Logger::GetInstance( "tacLogFile.txt" );
    logger->Initialize();

    mRenderer = SDLRenderer::GetInstance();
    mRenderer->Initialize( 640, 480, 32 );

    mResManager = ResourceManager::GetInstance();
    mResManager->Initialize();

    mInput = InputManager::GetInstance();
    mInput->Initialize();

    mSoundManager = SoundManager::GetInstance();
    mSoundManager->Initialize();

// TODO: Implement SecurityManager
//    mSecurityManager = SecurityManager::GetInstance();
//    mSecurityManager->Initialize();

// TODO: Make DatabaseManager a singleton
//    mDatabase = DatabaseManager::GetInstance();
//    mDatabase->Initialize();

// TODO: Implement GameEngine when it is ready
//    mGameEngine = GameEngine()::GetInstance();

    mUIManager = UIManager::GetInstance();
    mUIManager->Initialize();

}

void GameRoot::Shutdown()
{
    mUIManager->Shutdown();

// TODO: Implement GameEngine when it is ready
//    mGameEngine->Shutdown();

// TODO: Make DatabaseManager a singleton
//    mDatabase->Shutdown();

// TODO: Implement SecurityManager
//    mSecurityManager->Shutdown();

    mSoundManager->Shutdown();

    mInput->Shutdown();

    mResManager->Shutdown();

    mRenderer->Shutdown();

    Logger::GetInstance()->Shutdown();
}

void GameRoot::GameLoop()
{
    Mix_Music* gameMusic = mResManager->LoadMusic( "Fantastic_B1-256.mp3" );
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
    }
    LogInfo( "The game has ended." );
}

//============================= OPERATORS ====================================
//============================= OPERATIONS ===================================
//============================= ACCESS     ===================================
//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
