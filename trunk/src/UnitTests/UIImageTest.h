#ifndef __UIIMAGETEST_H
#define __UIIMAGETEST_H

#include <cxxtest/TestSuite.h>

#include <UI/UIImage.h>
#include <UI/UIUnitTestHelp.h>
#include <Logger.h>

//
// A generated test suite: Just write tests!
//

class UIImageTest : public CxxTest::TestSuite
{
private:
// any variables that could be shared between tests
    UIImage *testImage1;
    UIImage *testImage2; // 2 different constructors
    string testFileName;
    UIUnitTestHelp* mUIUnitTester;

// Unit Tests:
public:

    // Constructor
    UIImageTest()
    : testImage1( NULL ), testImage2( NULL ), mUIUnitTester( NULL )
    {
    }


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
        testFileName = "charTile.png";
        testImage1 = new UIImage();
        testImage2 = new UIImage(testFileName);
        mUIUnitTester = new UIUnitTestHelp( testImage1 , "UIImage" );

        if ( (testImage1) && (testImage2) )
        {

            TS_ASSERT( testImage1->GetElement() == NULL );

            TS_ASSERT( testImage2->GetElement() != NULL );

            mUIUnitTester->RunBasicTest();
            mUIUnitTester->SetNewElement( testImage2 );
            mUIUnitTester->RunBasicTest();



        }
        else
        {
            TS_TRACE( "Images not initializing for some reason" );
        }

        delete testImage1;
        delete testImage2;
        delete mUIUnitTester;

    }


};


#endif // __UIIMAGETEST_H

