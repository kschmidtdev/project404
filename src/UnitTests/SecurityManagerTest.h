#ifndef __SECURITYMANAGERTEST_H
#define __SECURITYMANAGERTEST_H

#include <cxxtest/TestSuite.h>

#include <Logger.h>
#include <SecurityManager.h>
#include <unistd.h>

#include <set>
#include <string>

using namespace std;

typedef pair< string, string > UserPair;
typedef set< UserPair > UserSet;

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
        srand( time(0) );

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

    void testLargeAmountOfRandomPasswords()
    {
        SecurityManager* secMgr = SecurityManager::GetInstance();
        TS_ASSERT( secMgr != NULL );

        /*const int NUM_OF_TESTS = 1000;
        constn int LEN_OF_USERNAME_MAX = 32;

        UserSet users;
        string userName("");
        string passWord("");
        for( int i = 0; i < NUM_OF_TESTS; ++i )
        {
            int len = (rand() % LEN_OF_USERNAME_MAX-1 ) + 1;
            do
            {
                for( int j = 0; j < len; ++j )
                {
                    userName += static_cast<char>( (rand()%254) + 1 );
                }
            }
            while( users

            secMgr->AddUser( userName, passWord );
        }*/
    }

    void testEncryptionDecryptionBasic()
    {
        const char* dbEncryptedFileName = "databaseUnitTestEncrypted.xml";
        const char* dbDecryptedFileName = "databaseUnitTestDecrypted.xml";

        string result = SecurityManager::GetInstance()->EncryptFile( "database.xml", "TESTHASH", dbEncryptedFileName );
        TS_ASSERT( result.size() != 0 );
        TS_ASSERT_SAME_DATA( result.c_str(), dbEncryptedFileName, result.size() );

        result = SecurityManager::GetInstance()->DecryptFile( dbEncryptedFileName, "TESTHASH", dbDecryptedFileName );
        TS_ASSERT( result.size() != 0 );
        TS_ASSERT_SAME_DATA( result.c_str(), dbDecryptedFileName, result.size() );
    }

    void testEncryptionDecryptionOneElementLongHash()
    {
        const char* dbEncryptedFileName = "databaseUnitTestEncrypted.xml";
        const char* dbDecryptedFileName = "databaseUnitTestDecrypted.xml";

        string result = SecurityManager::GetInstance()->EncryptFile( "database.xml", "a", dbEncryptedFileName );
        TS_ASSERT( result.size() != 0 );
        TS_ASSERT_SAME_DATA( result.c_str(), dbEncryptedFileName, result.size() );

        result = SecurityManager::GetInstance()->DecryptFile( dbEncryptedFileName, "a", dbDecryptedFileName );
        TS_ASSERT( result.size() != 0 );
        TS_ASSERT_SAME_DATA( result.c_str(), dbDecryptedFileName, result.size() );

        result = SecurityManager::GetInstance()->EncryptFile( "database.xml", "b", dbEncryptedFileName );
        TS_ASSERT( result.size() != 0 );
        TS_ASSERT_SAME_DATA( result.c_str(), dbEncryptedFileName, result.size() );

        result = SecurityManager::GetInstance()->DecryptFile( dbEncryptedFileName, "b", dbDecryptedFileName );
        TS_ASSERT( result.size() != 0 );
        TS_ASSERT_SAME_DATA( result.c_str(), dbDecryptedFileName, result.size() );
    }

};


#endif // __SECURITYMANAGERTEST_H

