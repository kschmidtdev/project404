#ifndef __UIMENUTEST_H
#define __UIMENUTEST_H

#include <cxxtest/TestSuite.h>

#include <UIMenu.h>


// Generated Function Object

class MenuTestOperation : public FuncObj
{

    UIUnitTestHelp *mHelp;
    string buttonNum;

    public:
    MenuTestOperation(UIUnitTestHelp* u, string num)
    : mHelp( NULL ), buttonNum ( "" )
    {
        mHelp = u;
        buttonNum = num;
    }

    virtual ~MenuTestOperation() { };

    void operator()(void)
    {

        // Run Test
        mHelp->RunNewTest("Test Function: " + buttonNum);

    }

};

//
// A generated test suite: Just write tests!
//


class UIMenuTest : public CxxTest::TestSuite
{
private:
// any variables that could be shared between tests

    UIMenu* testMenu;
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

    void testUIMenuAddButton()
    {

        testMenu = new UIMenu();
        mUIUnitTester = new UIUnitTestHelp(testMenu, "UIMenu");

        // Basic Test
        mUIUnitTester->RunBasicTest();

        // Preamble to creating Functions
        // What were you doing here? UIMenu deletes it's buttons and it's functions,
        // and you were creating functions on the stack that would be getting deleted
        // by UIMenu when it destructs, causing a crash
        MenuTestOperation* Func1 = new MenuTestOperation(mUIUnitTester, "1");
        // Note:  This testing of function will come later
        // Once I complete an Input-help class

        // Add One Button
        testMenu->AddButton("Button 1", Func1);
        mUIUnitTester->RunNewTest("Add 1 Button");


        delete mUIUnitTester;
        delete testMenu;


    }

};


#endif // __UIMENUTEST_H

