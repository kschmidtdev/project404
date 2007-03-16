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
 * Karl Schmidt, February 9 2007, Found a need for ERR_COUNT, added it back in, added
 * shortcut macros to the bottom
 *
 * Karl Schmidt, February 7 2007, Modified slightly (no need forseen for COUNT in EMESSAGE_TYPE)
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
    ERR_COUNT
};

// LIFECYCLE

    /**
    * Returns an instance of a Logger, if this
    * is the first time it is called, it will
    * use the param as the filename for the log file
    */
    static Logger* GetInstance( const string logFileName );

    /**
    * Returns an instance of a Logger
    */
    static Logger* GetInstance();

    void Initialize();

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

    /**
    * Log an error/info message, with additional developer
    * information (source filename, line number)
    */
    void LogMessage( const EMESSAGE_TYPE type, const string msg, const string srcFileName, const int lineNum );


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
    const char* mMsgTypeText[ERR_COUNT];

private:
// PRIVATE VARIABLES
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#define LogError( msg ) Logger::GetInstance()->LogMessage( Logger::ERROR, msg, __FILE__, __LINE__ );
#define LogCritical( msg ) Logger::GetInstance()->LogMessage( Logger::CRITICAL, msg, __FILE__, __LINE__ );
#define LogWarning( msg ) Logger::GetInstance()->LogMessage( Logger::WARNING, msg, __FILE__, __LINE__ );
#define LogInfo( msg ) Logger::GetInstance()->LogMessage( Logger::INFO, msg, __FILE__, __LINE__ );

#endif  // _Logger_h_
