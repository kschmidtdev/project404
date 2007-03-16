#ifndef __UICHARWINDOWTEST_H
#define __UICHARWINDOWTEST_H

#include <cxxtest/TestSuite.h>

#include <UICharWindow.h>
#include <UIUnitTestHelp.h>
#include <GameEngine/Character.h>

//
// A generated test suite: Just write tests!
//

class UICharWindowTest : public CxxTest::TestSuite
{
private:
// any variables that could be shared between tests

    UICharWindow* mWindow;
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

    void testRenderSelf()
    {

        mWindow = new UICharWindow();
        mHelp = new UIUnitTestHelp(mWindow, "UICharWindow");

        // Run Basic Test
        mHelp->RunBasicTest();

        // Set Character
        Character *c = new Character();
        mWindow->SetPos( Point(0,0) );
        mWindow->SetCharacter(c);
        mHelp->RunNewTest("Add Char");

        // Clear Character
        mWindow->ClearCharacter();
        mHelp->RunNewTest("Clear Char");


        delete mHelp;
        delete mWindow;



    }

};


#endif // __UICHARWINDOWTEST_H

