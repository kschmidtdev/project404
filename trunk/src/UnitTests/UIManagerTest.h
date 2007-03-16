#ifndef __UIMANAGERTEST_H
#define __UIMANAGERTEST_H

#include <cxxtest/TestSuite.h>

#include <UIManager.h>

//
// A generated test suite: Just write tests!
//

class UIManagerTest : public CxxTest::TestSuite
{
private:
// any variables that could be shared between tests

    UIManager* mUIM;

// Unit Tests:
public:

    // Called before all unit tests in this suite, remove if not needed
    void setUp()
    {
        // Header for all UI Testing Elements
        Logger::GetInstance( "unitTestLog.txt" );
        Logger::GetInstance()->Initialize();
        SDLRenderer::GetInstance()->Initialize( 640, 480, 32 );
        ResourceManager::GetInstance()->Initialize();
        UIManager::GetInstance()->Initialize();
    }

    // Called after all unit tests in this suite, remove if note needed
    void tearDown()
    {
        ResourceManager::GetInstance()->Shutdown();
        SDLRenderer::GetInstance()->Shutdown();
        Logger::GetInstance()->Shutdown();
        UIManager::GetInstance()->Shutdown();
    }

    void testManager()
    {
        mUIM = UIManager::GetInstance();

        // Remove SetPassword as first layout
        mUIM->PopAllLayouts();
        //TS_TRACE( "Bottom Layout: " + mUIM->PeekLayout()->GetName() );

        // Test PushLayout
        mUIM->PushLayout("PasswordVer");
        TS_ASSERT( mUIM->PeekLayout()->GetName() == "PasswordVer" );


        // Test PopLayout
        mUIM->PopLayout();
        //mUIM->PopLayout();
        //TS_TRACE( "Bottom Layout: " + mUIM->PeekLayout()->GetName() );
        TS_ASSERT( mUIM->PeekLayout()->GetName() == "TitleScreen" );

        // Test PopAllLayouts
        mUIM->PushLayout("MainMenu");
        mUIM->PushLayout("Win");
        mUIM->PushLayout("Lose");
        mUIM->PopAllLayouts();
        TS_ASSERT( mUIM->PeekLayout()->GetName() == "TitleScreen" );

        // Test GetLayout
        TS_ASSERT( mUIM->GetLayout("Win")->GetName() == "Win" );

        // Test Get/Set GameState
        mUIM->SetEndGameState(false);
        TS_ASSERT(  mUIM->GetEndGameState() == false );

        mUIM->SetEndGameState(true);
        TS_ASSERT(  mUIM->GetEndGameState() == true );



    }

};


#endif // __UIMANAGERTEST_H

