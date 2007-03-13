#ifndef __GAMEROOTTEST_H
#define __GAMEROOTTEST_H

#include <cxxtest/TestSuite.h>

#include <GameRoot.h>

//
// This tests starting up and stopping/destroying the GameRoot object.
// This tests all managers starting up and shutting down.
//

class GameRootTest : public CxxTest::TestSuite
{
private:

// Unit Tests:
public:

    void testGameRoot()
    {
        GameRoot gRoot;
        gRoot.Initialize( false );
        TS_TRACE("Game root test");
        gRoot.Shutdown();
    }
};


#endif // __GAMEROOTTEST_H

