#ifndef __LOGGERTEST_H
#define __LOGGERTEST_H

#include <cxxtest/TestSuite.h>
#include <unistd.h>

#include <Logger.h>

//
// A generated test suite: Just write tests!
//

class LoggerTest : public CxxTest::TestSuite
{
private:
// any variables that could be shared between tests

// Unit Tests:
public:

    // Called before all unit tests in this suite, remove if not needed
    void setUp()
    {
        const char* unitTestFileName = "unitTestLog.txt";

        // Destroy any exists log file
        unlink( unitTestFileName );

        Logger::GetInstance( unitTestFileName );
        Logger::GetInstance()->Initialize();

        // Make sure this file was actually made!
        TS_ASSERT( access( unitTestFileName, F_OK ) == 0 );
    }

    // Called after all unit tests in this suite, remove if note needed
    void tearDown()
    {
        Logger::GetInstance()->Shutdown();
    }

    void testWriteLogInfo()
    {
    	LogInfo( "Test write info message to log" );
    }

};


#endif // __LOGGERTEST_H

