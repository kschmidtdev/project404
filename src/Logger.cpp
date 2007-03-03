/**
 * File:Logger.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Karl Schmidt, February 15 2007 | Corrected setting a pointer to false instead of NULL
 * Karl Schmidt, February 13 2007, Re-added opening file handle in Initialize, needed it to clear log so we don't keeping appending after running concurrently
 * Karl Schmidt, February 12 2007, Removed opening the file handle in Initialize, unnecessary.
 * Karl Schmidt, February 9 2007, Added full functionality
 * Karl Schmidt, February 7 2007, Created initial class definition
 */


#include <util.h>

#include "Logger.h"

/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

Logger* Logger::_instance = 0;

Logger* Logger::GetInstance( const string logFileName )
{
    // If a logger exists, return it's instance,
    // otherwise create a new one.
    if( _instance )
    {
        return _instance;
    }
    else
    {
        _instance = new Logger( logFileName );
        return _instance;
    }
}

Logger* Logger::GetInstance()
{
    // If a logger exists, return it's instance,
    // otherwise create a new one.
        if( _instance )
        {
            return _instance;
        }
        else
        {
            _instance = new Logger();
            return _instance;
        }
}

void Logger::Initialize()
{
    mMsgTypeText[ERROR] = "ERROR";
    mMsgTypeText[CRITICAL] = "** CRITICAL **";
    mMsgTypeText[WARNING] = "WARNING";
    mMsgTypeText[INFO] = "INFO";

    tacAssert( !mLogFileHandle ); // Shouldn't already have a file handle, means we've called Initialize twice
    tacAssert( mLogFileName != "" ); // Log filename should be valid

    // Open the handle so the next message is written to the log file, and it wipes the old file
    // after this log messages will be appended to the current log
    mLogFileHandle = fopen( mLogFileName.c_str(), "w" );

#ifdef _DEBUG
    LogMessage( INFO, "The log has started successfully for a DEBUG build" );
#else
    LogMessage( INFO, "The log has started successfully for a RELEASE build" );
#endif
}

void Logger::Shutdown()
{
    delete _instance;
    _instance = NULL;
}

Logger::~Logger()
{
    // close the file handle, etc
    LogMessage( INFO, "Log closing" );
    if( mLogFileHandle )
    {
        fclose( mLogFileHandle );
        mLogFileHandle = NULL;
    }
}

//============================= OPERATIONS ===================================

void Logger::LogMessage( const EMESSAGE_TYPE type, const string msg )
{
    if( !mLogFileHandle )
    {
        mLogFileHandle = fopen( mLogFileName.c_str(), "a" );
    }
    tacAssert( mLogFileHandle ); // Log file should be able to be written

    fprintf( mLogFileHandle, "%s: %s\n", mMsgTypeText[type], msg.c_str() );

    fclose( mLogFileHandle );
    mLogFileHandle = NULL;
}

void Logger::LogMessage( const EMESSAGE_TYPE type, const string msg, const string srcFileName, const int lineNum )
{
    LogMessage( type, msg + string(" ( FILE: ") + srcFileName.substr(srcFileName.rfind("\\") + 1) + string(" LINE: ") + toString( lineNum ) + string(" ) ") );
}

//============================= ACCESS      ===================================
//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////
Logger::Logger()
: mLogFileHandle( NULL ), mLogFileName( "logoutput.txt" )
{
    // create logger with default name
}

Logger::Logger( const string logFileName )
: mLogFileHandle( NULL ), mLogFileName( logFileName )
{
    // stub
}

/////////////////////////////// PRIVATE    ///////////////////////////////////
