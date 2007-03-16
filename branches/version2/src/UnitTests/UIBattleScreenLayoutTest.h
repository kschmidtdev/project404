#ifndef __UIBATTLESCREENLAYOUTTEST_H
#define __UIBATTLESCREENLAYOUTTEST_H

#include <cxxtest/TestSuite.h>

#include <UIBattleScreenLayout.h>
#include <UILayoutTestHelp.h>
#include <GameEngine/GameEngine.h>

//
// A generated test suite: Just write tests!
//

class UIBattleScreenLayoutTest : public CxxTest::TestSuite
{
private:
// any variables that could be shared between tests
    UILayoutTestHelp* mLayoutHelp;
    UIBattleScreenLayout* mTestLayout;

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
        SecurityManager::GetInstance()->Initialize();
        SecurityManager::GetInstance()->LoadPasswordHashFile( "passwords" );
        DatabaseManager::GetInstance()->Initialize();
        DBEngine::GetInstance()->Initialize();

        // Messing with GameEngine
        vector<City*>* cities = GameEngine::GetInstance()->GetCities();
        //(*cities)[0]->
        //GameEngine::GetInstance()->BattleInit( (*cities)[0] );
    }

    // Called after all unit tests in this suite, remove if note needed
    void tearDown()
    {
        DBEngine::GetInstance()->Shutdown();
        ResourceManager::GetInstance()->Shutdown();
        SDLRenderer::GetInstance()->Shutdown();
        SecurityManager::GetInstance()->Shutdown();
        Logger::GetInstance()->Shutdown();
        //GameEngine::GetInstance()->Shutdown();
    }

    void testLayout()
    {
        // Test OnLoad/OnClose
        mTestLayout = new UIBattleScreenLayout();
        mLayoutHelp = new UILayoutTestHelp(mTestLayout);
        mLayoutHelp->SetPos( Point( (640 - mLayoutHelp->GetElement()->w)/2, 20) );

        //mLayoutHelp->RunBasicTest();

    }

};


#endif // __UIBATTLESCREENLAYOUTTEST_H

