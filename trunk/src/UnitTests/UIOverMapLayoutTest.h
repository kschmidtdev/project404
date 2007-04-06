#ifndef __UIOVERMAPLAYOUTTEST_H
#define __UIOVERMAPLAYOUTTEST_H

#include <cxxtest/TestSuite.h>

#include <UI/Layouts/UIOverMapLayout.h>
#include <UI/UILayoutTestHelp.h>
#include <SecurityManager.h>
#include <Database/DBEngine.h>
#include <Renderer/SDLRenderer.h>

//
// A generated test suite: Just write tests!
//

class UIOverMapLayoutTest : public CxxTest::TestSuite
{
private:
// any variables that could be shared between tests

    UILayoutTestHelp* mLayoutHelp;
    UIOverMapLayout* mTestLayout;
// Unit Tests:
public:

    // Called before all unit tests in this suite, remove if not needed
    // Called before all unit tests in this suite, remove if not needed
    void setUp()
    {
        // Header for all UI Testing Elements
        Logger::GetInstance( "unitTestLog.txt" );
        Logger::GetInstance()->Initialize();
        SecurityManager::GetInstance()->Initialize();
        SecurityManager::GetInstance()->LoadPasswordHashFile( "passwords" );

        SDLRenderer::GetInstance()->Initialize( 640, 480, 32 );
        ResourceManager::GetInstance()->Initialize();
        DBEngine::GetInstance()->Initialize();
    }

    // Called after all unit tests in this suite, remove if note needed
    void tearDown()
    {
        delete mTestLayout;
        delete mLayoutHelp;

        DBEngine::GetInstance()->Shutdown();
        ResourceManager::GetInstance()->Shutdown();
        SDLRenderer::GetInstance()->Shutdown();
        SecurityManager::GetInstance()->Shutdown();
        Logger::GetInstance()->Shutdown();
    }

    void testLayout()
    {
        // Test OnLoad/OnClose
        mTestLayout = new UIOverMapLayout();
        mLayoutHelp = new UILayoutTestHelp(mTestLayout);
        mLayoutHelp->SetPos( Point( (640 - mLayoutHelp->GetElement()->w)/2, 20) );

        mLayoutHelp->RunBasicTest();

    }

};


#endif // __UIOVERMAPLAYOUTTEST_H

