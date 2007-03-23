#ifndef __SOUNDMANAGERTEST_H
#define __SOUNDMANAGERTEST_H

#include <cxxtest/TestSuite.h>

#include <unistd.h>
#include <ResourceManager/ResourceManager.h>
#include <SoundManager.h>
#include <Logger.h>
#include <Renderer/SDLRenderer.h>

class SoundManagerTest : public CxxTest::TestSuite
{
private:

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
        TS_TRACE( "Initializing the SoundManager" );
        Logger::GetInstance( "unitTestLog.txt" );
        Logger::GetInstance()->Initialize();

        // For some stupid reason sounds won't play in SDL unless it has a window created :/
        SDLRenderer::GetInstance()->Initialize( 320, 240, 32 );

        SoundManager::GetInstance()->Initialize();

        ResourceManager::GetInstance()->Initialize();
    }
    virtual ~SoundManagerTest()
    {
        TS_TRACE( "Shutting down the SoundManager" );

        ResourceManager::GetInstance()->Shutdown();
        SoundManager::GetInstance()->Shutdown();

        SDLRenderer::GetInstance()->Shutdown();

        Logger::GetInstance()->Shutdown();
    }

    void testMusicPlayback()
    {
        const char* musFileName = "testMusic.ogg";

        // Cannot run this unit test without the test music file
        TS_ASSERT( access( musFileName, F_OK ) == 0 );
        Mix_Music* musicToPlay = NULL;
        musicToPlay = ResourceManager::GetInstance()->LoadMusic( musFileName );
        TS_ASSERT( musicToPlay );

        SoundManager::GetInstance()->PlayMusic( musicToPlay, false );
        TS_TRACE( "Playing music for 2 seconds, you should hear it\n" );
        SDL_Delay( 2000 );
    }

    void testSoundPlayback()
    {
        const char* sndFileName = "testSound.wav";

        // Cannot run this unit test without the test sound file
        TS_ASSERT( access( sndFileName, F_OK ) == 0 );
        Mix_Chunk* soundToPlay = NULL;
        soundToPlay = ResourceManager::GetInstance()->LoadSound( sndFileName );
        TS_ASSERT( soundToPlay );

        SoundManager::GetInstance()->PlaySound( soundToPlay, false );
        TS_TRACE( "Playing sound for 1 second, you should hear it\n" );
        SDL_Delay( 1000 );
    }
};


#endif // __SOUNDMANAGERTEST_H

