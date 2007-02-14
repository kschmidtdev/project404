#ifndef __GAMEROOTANDSOUNDMANAGERTEST_H
#define __GAMEROOTANDSOUNDMANAGERTEST_H

#include <cxxtest/TestSuite.h>

#include <GameRoot.h>
#include <unistd.h>
#include <ResourceManager/ResourceManager.h>
#include <SoundManager.h>

//
// A generated test suite: Just write tests!
//

class GameRootAndSoundManagerTest : public CxxTest::TestSuite
{
private:
// any variables that could be shared between tests
    GameRoot gRoot;

// Unit Tests:
public:
    // These static functions are required if I need code to run once before all tests,
    // and then once after all tests.
    static GameRootAndSoundManagerTest *createSuite()
    {
        return new GameRootAndSoundManagerTest();
    }
    static void destroySuite( GameRootAndSoundManagerTest *suite )
    {
        delete suite;
    }

    GameRootAndSoundManagerTest()
    {
        gRoot.Initialize();
    }
    virtual ~GameRootAndSoundManagerTest()
    {
        gRoot.Shutdown();
    }

    void testMusicPlayback()
    {
        const char* musFileName = "testMusic.ogg";

        // Cannot run this unit test without the test music file
        TS_ASSERT( access( musFileName, F_OK ) == 0 );
        Mix_Music* musicToPlay = ResourceManager::GetInstance()->LoadMusic( musFileName );
        TS_ASSERT( musicToPlay );

        SoundManager::GetInstance()->PlayMusic( musicToPlay, false );
        TS_WARN( "Playing music for 2 seconds, you should hear it" );
        SDL_Delay( 2000 );
    }

    void testSoundPlayback()
    {
        const char* sndFileName = "testSound.wav";

        // Cannot run this unit test without the test sound file
        TS_ASSERT( access( sndFileName, F_OK ) == 0 );
        Mix_Chunk* soundToPlay = ResourceManager::GetInstance()->LoadSound( sndFileName );
        TS_ASSERT( soundToPlay );

        SoundManager::GetInstance()->PlaySound( soundToPlay, false );
        TS_WARN( "Playing sound for 1 second, you should hear it" );
        SDL_Delay( 1000 );
    }
};


#endif // __GAMEROOTANDSOUNDMANAGERTEST_H

