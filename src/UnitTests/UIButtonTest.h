#ifndef __UIBUTTONTEST_H
#define __UIBUTTONTEST_H

#include <cxxtest/TestSuite.h>

#include <UI/UIButton.h>
#include <UI/UIUnitTestHelp.h>

//
// A generated test suite: Just write tests!
//

class UIButtonTest : public CxxTest::TestSuite
{
private:
// any variables that could be shared between tests

    UIButton* testButton;
    UIButton* testButton2;
    UIUnitTestHelp* mHelp;
// Unit Tests:
public:

    // Called before all unit tests in this suite, remove if not needed
    void setUp()
    {

        // Header for all UI Testing Elements
        Logger::GetInstance( "unitTestLog.txt" );
        Logger::GetInstance()->Initialize();
        SDLRenderer::GetInstance()->Initialize( 480, 320, 32 );
        ResourceManager::GetInstance()->Initialize();

    }

    // Called after all unit tests in this suite, remove if note needed
    void tearDown()
    {
        ResourceManager::GetInstance()->Shutdown();
        SDLRenderer::GetInstance()->Shutdown();
        Logger::GetInstance()->Shutdown();
    }

    void testUIButtonRenderSelf()
    {

        testButton = new UIButton("Button Text");
        mHelp = new UIUnitTestHelp(testButton, "UIButton");

        // Basic Test
        mHelp->RunBasicTest();

        // Default Constructor
        testButton2 = new UIButton();
        mHelp->SetNewElement(testButton2);
        mHelp->RunNewTest("Empty");

        delete mHelp;
        delete testButton;
        delete testButton2;


    }

};


#endif // __UIBUTTONTEST_H

