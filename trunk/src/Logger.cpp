/**
 * File:Logger.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Karl Schmidt, February 9 2007, Added full functionality
 * Karl Schmidt, February 7 2007, Created initial class definition
 */

#include "Logger.h"
#include "util.h"
#include <sstream>

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

    mLogFileHandle = fopen( mLogFileName.c_str(), "w" );

    tacAssert( mLogFileHandle ); // Log file should be able to be written

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

// Utility Function
template< typename T >
string toString( const T& toConvert )
{
    ostringstream output;
    output << toConvert;
    return output.str();
}

void Logger::LogMessage( const EMESSAGE_TYPE type, const string msg )
{
    if( !mLogFileHandle )
    {
        mLogFileHandle = fopen( mLogFileName.c_str(), "a" );
    }
    tacAssert( mLogFileHandle ); // Log file should be able to be written

    fprintf( mLogFileHandle, "%s: %s\n", mMsgTypeText[type], msg.c_str() );

    fclose( mLogFileHandle );
    mLogFileHandle = false;
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
