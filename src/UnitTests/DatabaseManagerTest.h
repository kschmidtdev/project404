#ifndef __DATABASEMANAGERTEST_H
#define __DATABASEMANAGERTEST_H

#include <cxxtest/TestSuite.h>
#include <../Database/DatabaseManager.h>
#include <unistd.h>
//
// A generated test suite: Just write tests!
//

class DatabaseManagerTest : public CxxTest::TestSuite
{
private:
// any variables that could be shared between tests

// Unit Tests:
public:

    // Called before all unit tests in this suite, remove if not needed
    void setUp()
    {
        // testLoadFromFile().
        TS_ASSERT( DatabaseManager::GetInstance() ); // test wheather if the pointer of DatabaseManager is not NULL.

        const char* DatabaseFile = "database.xml";

        TS_ASSERT( access( DatabaseFile, F_OK ) == 0 ); // test if 'database.xml' exist in the directory.

        TS_ASSERT( DatabaseManager::GetInstance()->LoadFromFile( DatabaseFile ) ); // test if database.xml has been loaded successfully.

        // TS_TRACE( "Loading database. If you don't see any error messages, it is loaded successfully.\n");
    }

    // Called after all unit tests in this suite, remove if note needed
    void tearDown()
    {
        DatabaseManager::GetInstance()->Shutdown();
    }

    void testGetRoot()
    {
        TS_ASSERT_EQUALS( DatabaseManager::GetInstance()->GetRootNode()->GetName(), "Database"); // see if the RootNode of database is named "Database".
    }

    void testSearch()
    {
        DBNode* LevelNode = DatabaseManager::GetInstance()->GetRootNode()->GetChild("Level"); // Get LevelNode by traversing tree. (Parent to child recursively.)

        DBNode* FoundNode = DatabaseManager::GetInstance()->Search( "Level" ); // Get LevelNode by Search function. (Iterates the vector list of node pointers.)

        TS_ASSERT_EQUALS( LevelNode, FoundNode); // test if they are the same pointer.(if they have the same pointer address.)
    }

};


#endif // __DATABASEMANAGERTEST_H

