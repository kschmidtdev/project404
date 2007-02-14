#ifndef __SOUNDMANAGERTEST_H
#define __SOUNDMANAGERTEST_H

#include <cxxtest/TestSuite.h>

#include <SoundManager.h>
#include <ResourceManager/ResourceManager.h>

//
// A test suite for the SoundManager
//

class SoundManagerTest : public CxxTest::TestSuite
{
// Unit Tests:
public:

    // These static functions are required if I need code to run once before all tests,
    // and then once after all tests.
    static SoundManagerTest *createSuite()
    {
        return new SoundManagerTest();
    }
    static void destroySuite( SoundManagerTest *suite )
    {
        delete suite;
    }

    SoundManagerTest()
    {
        Logger::GetInstance()->Initialize();
        ResourceManager::GetInstance()->Initialize();
        SoundManager::GetInstance()->Initialize();
    }
    virtual ~SoundManagerTest()
    {
        SoundManager::GetInstance()->StopAllPlayback();
        ResourceManager::GetInstance()->Shutdown();
        SoundManager::GetInstance()->Shutdown();
        Logger::GetInstance()->Shutdown();
    }

    void testMusicPlayback()
    {
        const char* musFileName = "testMusic.mp3";

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


#endif // __SOUNDMANAGERTEST_H

