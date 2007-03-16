#ifndef __UITEXTTEST_H
#define __UITEXTTEST_H

#include <cxxtest/TestSuite.h>

#include <UIText.h>

//
// A generated test suite: Just write tests!
//

class UITextTest : public CxxTest::TestSuite
{
private:
// any variables that could be shared between tests

    UIText* testText;
    UIUnitTestHelp* mUIUnitTester;

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

        // Initializing Elements for test
        UIText* storage;
        UIImage* backdrop = new UIImage("testButton.png");
        SDLRenderer::GetInstance()->AddToRenderQueue(backdrop);

        testText = new UIText();
        mUIUnitTester = new UIUnitTestHelp( testText , "UIText" );

        // Basic Test
        mUIUnitTester->RunBasicTest();

        // Test default constructor
        storage = testText;
        testText = NULL;
        testText = new UIText("BASIC TEXT");
        mUIUnitTester->SetNewElement(testText);
        delete storage;
        storage = NULL;

        mUIUnitTester->RunBasicTest();
        SDLRenderer::GetInstance()->RemoveFromRenderQueue(backdrop);

        // Test 3rd constructor
        storage = testText;
        testText = NULL;
        testText = new UIText("DIFFERENT TEXT", 36, 0, 0, 255);
        mUIUnitTester->SetNewElement(testText);
        delete storage;
        storage = NULL;
        mUIUnitTester->RunNewTest("DIFF TEXT");

        // Test operators
        //=========

        // Text
        testText->ChangeText("MORE TEXT");
        mUIUnitTester->RunNewTest("MORE TEXT");

        // Colour
        testText->SetColour(255, 255, 255);
        mUIUnitTester->RunNewTest("White");

        // Size
        testText->SetSize(12);
        mUIUnitTester->RunNewTest("Small");

        // Everything
        testText->ChangeText("New Text!!", 16, 0, 255, 0);
        mUIUnitTester->RunNewTest("All New Text!!");


        delete mUIUnitTester;
        delete testText;
        delete backdrop;

    }

};


#endif // __UITEXTTEST_H

