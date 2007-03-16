/**
 * File: main.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Karl Schmidt, February 11 2007 | Added C call to make console output work
 * Karl Schmidt, March 14 2007    | Added support for some command line parameter parsing
 */

#include <util.h>

#include <GameRoot.h>
#include <stdio.h>

int main ( int argc, char** argv )
{
    fflush (stdout); // Enable console output, SDL disables this

    GameRoot ourGame;

    ourGame.Initialize( argc, argv );

    ourGame.GameLoop();

    ourGame.Shutdown();

    return 0;
}
