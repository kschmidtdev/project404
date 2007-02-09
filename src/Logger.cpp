/**
 * File:Logger.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Karl Schmidt, February 7 2007, Created initial class definition
 */

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

void Logger::Shutdown()
{
    delete _instance;
    _instance = NULL;
}

Logger::~Logger()
{
    // close the file handle, etc
}

//============================= OPERATIONS ===================================
//============================= ACCESS      ===================================
//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////
Logger::Logger()
{
    // create logger with default name
}

Logger::Logger( const string logFileName )
{
    // stub
}

/////////////////////////////// PRIVATE    ///////////////////////////////////
