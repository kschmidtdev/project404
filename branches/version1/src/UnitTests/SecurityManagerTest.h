#ifndef __SECURITYMANAGERTEST_H
#define __SECURITYMANAGERTEST_H

#include <cxxtest/TestSuite.h>

#include <SecurityManager.h>
#include <unistd.h>

//
// A generated test suite: Just write tests!
//

class SecurityManagerTest : public CxxTest::TestSuite
{
private:
// any variables that could be shared between tests
     string testPasswordFileName;

// Unit Tests:
public:

    // Called before all unit tests in this suite, remove if not needed
    void setUp()
    {
        Logger::GetInstance( "unitTestLog.txt" );
        Logger::GetInstance()->Initialize();

        testPasswordFileName = "unitTestPasswordHash";
        SecurityManager::GetInstance()->Initialize();
        unlink( testPasswordFileName.c_str() );
        TS_ASSERT( access( testPasswordFileName.c_str(), F_OK ) != 0 );
        SecurityManager::GetInstance()->AddUser( "unitTestUser1", "blah" );
        SecurityManager::GetInstance()->AddUser( "unitTestUser1", "blah" );
        SecurityManager::GetInstance()->AddUser( "unitTestUser2", "blah2" );
        TS_ASSERT( SecurityManager::GetInstance()->VerifyPassword( "unitTestUser1", "blah" ) );
        TS_ASSERT( SecurityManager::GetInstance()->VerifyPassword( "unitTestUser1", "blah" ) );
        TS_ASSERT( SecurityManager::GetInstance()->VerifyPassword( "unitTestUser2", "blah2" ) );
        SecurityManager::GetInstance()->SavePasswordHashFile( testPasswordFileName );
    }

    // Called after all unit tests in this suite, remove if note needed
    void tearDown()
    {
        SecurityManager::GetInstance()->Shutdown();
        Logger::GetInstance()->Shutdown();
    }

    void testAddingUsersAndWritingPasswordHashFile()
    {
        unlink( testPasswordFileName.c_str() );
        TS_ASSERT( access( testPasswordFileName.c_str(), F_OK ) != 0 );
        SecurityManager::GetInstance()->AddUser( "unitTestUser1", "blah" );
        SecurityManager::GetInstance()->AddUser( "unitTestUser1", "blah" );
        SecurityManager::GetInstance()->AddUser( "unitTestUser2", "blah2" );
        TS_ASSERT( SecurityManager::GetInstance()->VerifyPassword( "unitTestUser1", "blah" ) );
        TS_ASSERT( SecurityManager::GetInstance()->VerifyPassword( "unitTestUser1", "blah" ) );
        TS_ASSERT( SecurityManager::GetInstance()->VerifyPassword( "unitTestUser2", "blah2" ) );
        SecurityManager::GetInstance()->SavePasswordHashFile( testPasswordFileName );
    }

    void testLoadingPasswordHashFile()
    {
        TS_ASSERT( access( testPasswordFileName.c_str(), F_OK ) == 0 );
        SecurityManager::GetInstance()->LoadPasswordHashFile( testPasswordFileName );
        TS_ASSERT( SecurityManager::GetInstance()->VerifyPassword( "unitTestUser1", "blah" ) );
        TS_ASSERT( SecurityManager::GetInstance()->VerifyPassword( "unitTestUser1", "blah" ) );
        TS_ASSERT( SecurityManager::GetInstance()->VerifyPassword( "unitTestUser2", "blah2" ) );
    }

};


#endif // __SECURITYMANAGERTEST_H

