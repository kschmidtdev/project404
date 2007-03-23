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
 * Karl Schmidt, March 23 2007    | Got rid of more using namespace std; usage, renamed some enums
                                    because of name collisions
 */

#ifndef Logger_h
#define Logger_h

// SYSTEM INCLUDES
//
#include <string>
#include <stdio.h>

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
    EL_ERROR = 0,
    EL_CRITICAL,
    EL_WARNING,
    EL_INFO,
    EL_ERRCOUNT
};

// LIFECYCLE

    /**
    * Returns an instance of a Logger, if this
    * is the first time it is called, it will
    * use the param as the filename for the log file
    */
    static Logger* GetInstance( const std::string & logFileName );

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
    void LogMessage( const EMESSAGE_TYPE type, const std::string & msg );

    /**
    * Log an error/info message, with additional developer
    * information (source filename, line number)
    */
    void LogMessage( const EMESSAGE_TYPE type, const std::string & msg, const std::string & srcFileName, const int lineNum );


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
    Logger( const std::string & logFileName );

    static Logger* _instance;

// PROTECTED VARIABLES

    FILE* mLogFileHandle;
    std::string mLogFileName;
    const char* mMsgTypeText[EL_ERRCOUNT];

private:
// PRIVATE VARIABLES
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#define LogError( msg ) Logger::GetInstance()->LogMessage( Logger::EL_ERROR, msg, __FILE__, __LINE__ );
#define LogCritical( msg ) Logger::GetInstance()->LogMessage( Logger::EL_CRITICAL, msg, __FILE__, __LINE__ );
#define LogWarning( msg ) Logger::GetInstance()->LogMessage( Logger::EL_WARNING, msg, __FILE__, __LINE__ );
#define LogInfo( msg ) Logger::GetInstance()->LogMessage( Logger::EL_INFO, msg, __FILE__, __LINE__ );

#endif  // _Logger_h_
