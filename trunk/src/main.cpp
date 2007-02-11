#include <GameRoot.h>

int main ( int argc, char** argv )
{
    GameRoot ourGame;

    ourGame.Initialize();

    ourGame.GameLoop();

    ourGame.Shutdown();

    return 0;
}
