/**
 * Our error logging system
 *
 * #include "Logger.h"
 *
 * Logs requested errors and warnings to disk in a log file
 * and optionally to the console.
 *
 *
 * Project 404 2007
 *
 * Authors:
 * Name, Date (Month Day Year), What was done
 * Karl Schmidt, February 7 2007, Created initial class definition
 */

#ifndef Logger_h
#define Logger_h

// SYSTEM INCLUDES
//
#include <string>
#include <stdio.h>
using namespace std;

// PROJECT INCLUDES
//

// LOCAL INCLUDES
//

// FORWARD REFERENCES
//

class Logger
{
public:

// ENUM
enum EMESSAGE_TYPE
{
    ERROR = 0,
    CRITICAL,
    WARNING,
    INFO,
    COUNT
};

// LIFECYCLE

    /**
    * Returns an instance of a Logger, if this
    * is the first time it is called, it will
    * use the param as the filename for the log file
    */
    static Logger* getInstance( const string logFileName );

    /**
    * Returns an instance of a Logger
    */
    static Logger* getInstance();

    /**
    * Shuts down the logger, must be called before
    * the application is shut down. Will clean
    * up the log file handle, etc.
    */
    void Shutdown();

    /**
    * Destructor.
    */
    virtual ~Logger(void);

// OPERATORS

// OPERATIONS

    /**
    * Log an error/info message
    */
    void LogMessage( const EMESSAGE_TYPE type, const string msg );

// ACCESS (writing)
// INQUIRY (reading)

// PROTECTED METHODS
protected:

    /**
    * Default constructor.
    */
    Logger(void);

    /**
    * Constructor that takes the name of the log filename in.
    */
    Logger( const string logFileName );

    static Logger* _instance;

// PROTECTED VARIABLES

    FILE* mLogFileHandle;
    string mLogFileName;

private:
// PRIVATE VARIABLES
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif  // _Logger_h_
