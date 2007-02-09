#include <cstdlib>

#include <SDL/SDL.h>
#include "sdlrenderer.h"

int main ( int argc, char** argv )
{
/*    SDLRenderer renderer;

    int result = renderer.Initialize( 640, 480, 16 );
    if( result != 0 )
    {
        printf( "Error during renderer initialization.\n" );
        return result;
    }*/
    SDLRenderer* renderer = SDLRenderer::GetInstance();

    renderer->Initialize( 640, 480, 32 );

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

    renderer->Shutdown();
    //renderer.Shutdown();

    // all is well ;)
    printf("Exited cleanly\n");
    return 0;
}
