/**
 * File: main.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Karl Schmidt, February 11 2007 | Added C call to make console output work
 * Karl Schmidt, March 14 2007    | Added support for some command line parameter parsing
 * Karl Schmidt, March 27 2007    | Added a form of reporting if memory leaks were detected during a run session to the developer
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

#ifdef _DEBUG
    FILE* memLeaksLog = fopen( "memleaks.log", "r" );
    if( memLeaksLog )
    {
        fseek( memLeaksLog, 0, SEEK_END );
        unsigned int fileSize = ftell( memLeaksLog );

        if( fileSize != 449 )
        {
            printf( "\n\n\n*** MEMORY LEAKS WERE DETECTED DURING THIS SESSION ! CHECK MEMLEAKS.LOG ! ***\n\n" );
            fclose( memLeaksLog );
            return -1;
        }
    }
    fclose( memLeaksLog );
#endif

    return 0;
}
