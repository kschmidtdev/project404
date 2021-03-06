#ifndef __SECURITYMANAGERTEST_H
#define __SECURITYMANAGERTEST_H

#include <cxxtest/TestSuite.h>

#include <Logger.h>
#include <unistd.h>
#include <SecurityManager.h>

#include <set>
#include <string>

typedef std::map< std::string, std::string > UserMap;
typedef UserMap::iterator UserMapItr;

//
// A generated test suite: Just write tests!
//

const char* dbEncryptedFileName = "databaseUnitTestEncrypted.xml";
const char* dbDecryptedFileName = "databaseUnitTestDecrypted.xml";


class SecurityManagerTest : public CxxTest::TestSuite
{
private:
// any variables that could be shared between tests
     std::string testPasswordFileName;

// Unit Tests:
public:

    // Called before all unit tests in this suite, remove if not needed
    void setUp()
    {
        Logger::GetInstance( "secManagerUnitTestLog.txt" );
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

        srand( 7775 ); // Seeding by same value so we don't get a resultset that fails sometimes, and not others

        const int NUM_OF_TESTS = 1000;
        const int LEN_OF_USERNAME_MAX = 32;

        UserMap users;
        std::string userName("");
        std::string passWord("");
        for( int i = 0; i < NUM_OF_TESTS; ++i )
        {
            // Get a random length for the username
            int len = (rand() % LEN_OF_USERNAME_MAX-1 ) + 1;
            do // Keep generating names, if it already exists then make another and try again
            {
                userName = "";
                for( int j = 0; j < len; ++j )
                {
                    userName += static_cast<char>( (rand()%255) );
                }
            }
            while( users.find( userName ) != users.end() );

            // Get a random length for the password
            len = (rand() % LEN_OF_USERNAME_MAX-1 ) + 1;
            for( int j = 0; j < len; ++j )
            {
                userName += static_cast<char>( (rand()%255) );
            }

            secMgr->AddUser( userName, passWord );
        }

        for( UserMapItr i = users.begin(); i != users.end(); ++i )
        {
            // Test that they all verify against what they were set to
            TS_ASSERT( secMgr->VerifyPassword( i->first, i->second ) );
        }
    }

    void testEncryptionDecryptionBasic()
    {
        std::string result = SecurityManager::GetInstance()->EncryptFile( "databaseUnencrypted.xml", "TESTHASH", dbEncryptedFileName );
        TS_ASSERT( result.size() != 0 );
        TS_ASSERT_SAME_DATA( result.c_str(), dbEncryptedFileName, result.size() );

        result = SecurityManager::GetInstance()->DecryptFile( dbEncryptedFileName, "TESTHASH", dbDecryptedFileName );
        TS_ASSERT( result.size() != 0 );
        TS_ASSERT_SAME_DATA( result.c_str(), dbDecryptedFileName, result.size() );
    }

    void testEncryptionDecryptionOneElementLongHash()
    {
        std::string result = SecurityManager::GetInstance()->EncryptFile( "databaseUnencrypted.xml", "a", dbEncryptedFileName );
        TS_ASSERT( result.size() > 0 );
        TS_ASSERT_SAME_DATA( result.c_str(), dbEncryptedFileName, result.size() );

        result = SecurityManager::GetInstance()->DecryptFile( dbEncryptedFileName, "a", dbDecryptedFileName );
        TS_ASSERT( result.size() > 0 );
        TS_ASSERT_SAME_DATA( result.c_str(), dbDecryptedFileName, result.size() );

        result = SecurityManager::GetInstance()->EncryptFile( "databaseUnencrypted.xml", "b", dbEncryptedFileName );
        TS_ASSERT( result.size() > 0 );
        TS_ASSERT_SAME_DATA( result.c_str(), dbEncryptedFileName, result.size() );

        result = SecurityManager::GetInstance()->DecryptFile( dbEncryptedFileName, "b", dbDecryptedFileName );
        TS_ASSERT( result.size() > 0 );
        TS_ASSERT_SAME_DATA( result.c_str(), dbDecryptedFileName, result.size() );
    }

    void testEncryptionBlankHash()
    {
        std::string result = SecurityManager::GetInstance()->EncryptFile( "databaseUnencrypted.xml", "", dbEncryptedFileName );
        TS_ASSERT( result.empty() ); // The above is invalid, so result should be a blank std::string
    }

    void testDecryptionBlankHash()
    {
        std::string result = SecurityManager::GetInstance()->DecryptFile( "databaseUnencrypted.xml", "", dbDecryptedFileName );
        TS_ASSERT( result.empty() ); // The above is invalid, so result should be a blank std::string
    }

    void testEncryptionBlankFileName()
    {
        std::string result = SecurityManager::GetInstance()->EncryptFile( "", "TEST_HASH", dbEncryptedFileName );
        TS_ASSERT( result.empty() ); // The above is invalid, so result should be a blank std::string
    }

    void testDecryptionBlankFileName()
    {
        std::string result = SecurityManager::GetInstance()->DecryptFile( "", "TEST_HASH", dbDecryptedFileName );
        TS_ASSERT( result.empty() ); // The above is invalid, so result should be a blank std::string
    }

    void testDecryptionToAString()
    {
        const char* fileName = "unitTestDecryptToMem.xml";
        std::string fileContents = "TEST FILE ONE TWO THREE 1 2 3";
        const char* hashToUse = "DECRYPTION_TO_STRING_TEST_HASH_STRING";

        FILE* testFile = NULL;
        testFile = fopen( fileName, "wb" );
        TS_ASSERT( testFile != NULL );
        TS_ASSERT_EQUALS( fwrite( fileContents.c_str(), sizeof(char), fileContents.size(), testFile ), fileContents.size() );
        fclose( testFile );

        std::string result = SecurityManager::GetInstance()->EncryptFile( fileName, hashToUse );
        TS_ASSERT( result.size() > 0 );
        TS_ASSERT_SAME_DATA( result.c_str(), fileName, result.size() );

        std::string resultString = SecurityManager::GetInstance()->DecryptFileToString( fileName, hashToUse );
        TS_ASSERT( resultString.size() > 0 );

        TS_ASSERT_EQUALS( resultString.size(), fileContents.size() );
        TS_ASSERT_SAME_DATA( resultString.c_str(), fileContents.c_str(), resultString.size() );
    }

    void testDecryptionToAStringBlankHash()
    {
        std::string result = SecurityManager::GetInstance()->DecryptFileToString( "databaseUnencrypted.xml", "" );
        TS_ASSERT( result.empty() ); // The above is invalid, so result should be a blank std::string
    }

    void testDecryptionToAStringBlankFileName()
    {
        std::string result = SecurityManager::GetInstance()->DecryptFileToString( "", "TEST_HASH" );
        TS_ASSERT( result.empty() ); // The above is invalid, so result should be a blank std::string
    }

    void testGetUserHash()
    {
        SecurityManager::GetInstance()->AddUser( "userGetUserHash", "blah" );
        TS_ASSERT( SecurityManager::GetInstance()->GetUserHash( "userGetUserHash" ) != "" );
    }
};


#endif // __SECURITYMANAGERTEST_H

