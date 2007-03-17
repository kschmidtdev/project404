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

        const char* DatabaseFile = "databaseUnencrypted.xml";

        TS_ASSERT( access( DatabaseFile, F_OK ) == 0 ); // test if 'database.xml' exist in the directory.

        TS_ASSERT( DatabaseManager::GetInstance()->LoadFromFile( DatabaseFile ) ); // test if database.xml has been loaded successfully.

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

    void testSaveToFile()
    {
        TS_ASSERT( DatabaseManager::GetInstance() ); // test wheather if the pointer of DatabaseManager is not NULL.

        const char* SaveFile = "unitTestSaveFile.xml";

        DatabaseManager::GetInstance()->SaveToFile( SaveFile );

        TS_ASSERT( access( SaveFile, F_OK ) == 0 ); // test if 'unitTestSaveFile.xml' exist in the directory.
    }

    void testUpdateNode()
    {
        // #1
        DBNode* testNode = NULL;
        testNode = DatabaseManager::GetInstance()->Search( "Han" );
        DBString* testData1 = dynamic_cast<DBString*>( testNode->GetAttribute( "Class" ) );

        TS_ASSERT_EQUALS( testData1->GetData(), "Healer" );

        DatabaseManager::GetInstance()->UpdateNode( "Han", "Class", "SuperTestClass" ); // After update the node.

        testData1 = dynamic_cast<DBString*>( testNode->GetAttribute( "Class" ) );

        TS_ASSERT_EQUALS( testData1->GetData(), "SuperTestClass" );


        // #2
        DBInt* testData2 = dynamic_cast<DBInt*>( testNode->GetAttribute( "Level" ) );

        TS_ASSERT_EQUALS( testData2->GetData(), 1 );

        DatabaseManager::GetInstance()->UpdateNode( "Han", "Level", 99 ); // After update the node.

        testData2 = dynamic_cast<DBInt*>( testNode->GetAttribute( "Level" ) );

        TS_ASSERT_EQUALS( testData2->GetData(), 99 );
    }

};


#endif // __DATABASEMANAGERTEST_H

