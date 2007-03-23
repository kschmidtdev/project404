#ifndef __UITITLESCREENLAYOUTTEST_H
#define __UITITLESCREENLAYOUTTEST_H

#include <cxxtest/TestSuite.h>

#include <UI/Layouts/UITitleScreenLayout.h>
#include <UI/UILayoutTestHelp.h>
#include <Renderer/SDLRenderer.h>

//
// A generated test suite: Just write tests!
//

class UITitleScreenLayoutTest : public CxxTest::TestSuite
{
private:
// any variables that could be shared between tests
    UILayoutTestHelp* mLayoutHelp;
    UITitleScreenLayout* mTestLayout;

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
    }

    // Called after all unit tests in this suite, remove if note needed
    void tearDown()
    {
        ResourceManager::GetInstance()->Shutdown();
        SDLRenderer::GetInstance()->Shutdown();
        Logger::GetInstance()->Shutdown();
    }

    void testLayout()
    {
        // Test OnLoad/OnClose
        mTestLayout = new UITitleScreenLayout();
        mLayoutHelp = new UILayoutTestHelp(mTestLayout);
        mLayoutHelp->SetPos( Point( (640 - mLayoutHelp->GetElement()->w)/2, 20) );

        mLayoutHelp->RunBasicTest();

    }

};


#endif // __UITITLESCREENLAYOUTTEST_H

