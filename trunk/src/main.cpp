#include "Renderer/sdlrenderer.h"
#include "ResourceManager/ResourceManager.h"
#include "Renderer/ExampleRenderable.h"

#include "InputManager.h"
#include "ExampleEventListener.h"
#include "Logger.h"
#include "UIManager.h"

int main ( int argc, char** argv )
{
    // TODO: Clean all this up, make the darn GameRoot!

    Logger* logger = Logger::GetInstance( "tacLogFile.txt" );

    logger->Initialize();

    ResourceManager* resManager = ResourceManager::GetInstance();
    LogInfo( "ResourceManager started successfully" );

    InputManager* inputManager = InputManager::GetInstance();

    resManager->Initialize();

    SDL_Surface* testSurface = 0;
    testSurface = resManager->LoadTexture( "cb.bmp" );

    ExampleRenderable dude;

    SDLRenderer* renderer = SDLRenderer::GetInstance();

    renderer->Initialize( 640, 480, 32 );
    inputManager->Initialize();

    renderer->AddToRenderQueue( &dude );

    ExampleEventListener testListener;

    inputManager->AddEventListener( &testListener );

    // program main loop
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
                    inputManager->ProcessEvent( &event );
                    // exit if ESCAPE is pressed
                    if (event.key.keysym.sym == SDLK_ESCAPE)
                        done = true;
                    break;
                }
            } // end switch
        } // end of message processing

        //renderer.Update();
        renderer->Draw();
    }

    inputManager->Shutdown();
    resManager->Shutdown();
    renderer->Shutdown();
    logger->Shutdown();

    return 0;
}
