#ifndef __UISCROLLTEXTTEST_H
#define __UISCROLLTEXTTEST_H

#include <cxxtest/TestSuite.h>

#include <UI/UIScrollText.h>
#include <UI/UIUnitTestHelp.h>

//
// A generated test suite: Just write tests!
//

class UIScrollTextTest : public CxxTest::TestSuite
{
private:
// any variables that could be shared between tests

    UIScrollText* mScroll;
    UIUnitTestHelp* mHelp;

// Unit Tests:
public:

    // Called before all unit tests in this suite, remove if not needed
    void setUp()
    {
        // Header for all UI Testing Elements
        Logger::GetInstance( "unitTestLog.txt" );
        Logger::GetInstance()->Initialize();
        SDLRenderer::GetInstance()->Initialize( 640, 320, 32 );
        ResourceManager::GetInstance()->Initialize();
    }

    // Called after all unit tests in this suite, remove if note needed
    void tearDown()
    {
        ResourceManager::GetInstance()->Shutdown();
        SDLRenderer::GetInstance()->Shutdown();
        Logger::GetInstance()->Shutdown();
    }

    void testRenderSelf()
    {

        mScroll = new UIScrollText();
        mHelp = new UIUnitTestHelp(mScroll, "UIScrollText");

        // Basic Test
        mHelp->RunBasicTest();

        // Add one line
        mScroll->AddLine("Add First Line");
        mHelp->RunNewTest("One Line");

        // Fill page
        mScroll->AddLine("Second Line");
        mScroll->AddLine("Third Line");
        mScroll->AddLine("Fourth Line");
        mHelp->RunNewTest("4 Lines");

        // Add line, still 1st page
        mScroll->AddLine("New Page");
        mHelp->RunNewTest("Still First Page");

        // New Page
        TS_ASSERT( mScroll->NextPage() );
        mHelp->RunNewTest("New Page");

        // Test further functionality
        TS_ASSERT( mScroll->NextPage() == false );


        delete mHelp;
        delete mScroll;


    }

};


#endif // __UISCROLLTEXTTEST_H

