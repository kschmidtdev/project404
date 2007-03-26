#ifndef __SDLRENDERERTEST_H
#define __SDLRENDERERTEST_H

#include <cxxtest/TestSuite.h>

#include <Logger.h>
#include <Renderer/sdlrenderer.h>
#include <Renderer/ExampleRenderable.h>
#include <ResourceManager/ResourceManager.h>

//
// A generated test suite: Just write tests!
//

class sdlrendererTest : public CxxTest::TestSuite
{
private:
// any variables that could be shared between tests
    ExampleRenderable exTextureRenderable;
    ExampleRenderable exTextRenderable;

// Unit Tests:
public:

    // Called before all unit tests in this suite, remove if not needed
    void setUp()
    {
        Logger::GetInstance( "unitTestLog.txt" );
        Logger::GetInstance()->Initialize();
        SDLRenderer::GetInstance()->Initialize( 320, 240, 32 );
        ResourceManager::GetInstance()->Initialize();
    }

    // Called after all unit tests in this suite, remove if note needed
    void tearDown()
    {
        ResourceManager::GetInstance()->Shutdown();
        SDLRenderer::GetInstance()->Shutdown();
        Logger::GetInstance()->Shutdown();
    }

    void testRenderTexture()
    {
        // SDLRenderer::DrawImageAt is tested within the ExampleRenderable
        SDL_Surface* texture = NULL;
        texture = ResourceManager::GetInstance()->LoadTexture( "archer_party.png" );
        TS_ASSERT( texture );
        exTextureRenderable.SetTexture( texture );
        SDLRenderer::GetInstance()->AddToRenderQueue( &exTextureRenderable );
        SDLRenderer::GetInstance()->Draw();
        TS_TRACE( "You should see a texture rendering for .5 seconds" );
        SDL_Delay( 500 );
        SDLRenderer::GetInstance()->RemoveFromRenderQueue( &exTextureRenderable );
        SDLRenderer::GetInstance()->Draw();
        TS_TRACE( "You should not a texture rendering for .5 seconds" );
        SDL_Delay( 500 );
    }

    void testRenderText()
    {
        SDL_Surface* texture = NULL;
        texture = SDLRenderer::GetInstance()->CreateTextSurface( "Test text", 12, 255, 255, 255 );
        TS_ASSERT( texture );
        exTextRenderable.SetTexture( texture );
        SDLRenderer::GetInstance()->AddToRenderQueue( &exTextRenderable );
        SDLRenderer::GetInstance()->Draw();
        TS_TRACE( "You should see text rendering for .5 seconds" );
        SDL_Delay( 500 );
        SDLRenderer::GetInstance()->RemoveFromRenderQueue( &exTextRenderable );
        SDLRenderer::GetInstance()->Draw();
        TS_TRACE( "You should not text rendering for .5 seconds" );
        SDL_Delay( 500 );
    }

    void testRenderTemp()
    {
        SDL_Surface* texture = NULL;
        texture = SDLRenderer::GetInstance()->CreateTextSurface( "Temporary Text", 12, 255, 255, 255 );
        TS_ASSERT( texture );
        ExampleRenderable* temporaryRenderable = new ExampleRenderable();
        temporaryRenderable->SetTexture( texture );
        SDLRenderer::GetInstance()->AddToTempRenderQueue( temporaryRenderable, SDL_GetTicks() + 500 );
        SDLRenderer::GetInstance()->Draw();
        TS_TRACE( "You should see text render and then disappear" );
        Uint32 futureTime = SDL_GetTicks() + 1000;
        while( SDL_GetTicks() < futureTime )
        {
            SDLRenderer::GetInstance()->Draw();
        }
    }

    void testRenderTempStartInFuture()
    {
        SDL_Surface* texture = NULL;
        texture = SDLRenderer::GetInstance()->CreateTextSurface( "Temporary Text", 12, 255, 255, 255 );
        TS_ASSERT( texture );
        ExampleRenderable* temporaryRenderable = new ExampleRenderable();
        temporaryRenderable->SetTexture( texture );
        SDLRenderer::GetInstance()->AddToTempRenderQueue( temporaryRenderable, SDL_GetTicks() + 1000, SDL_GetTicks() + 500 );
        SDLRenderer::GetInstance()->Draw();
        TS_TRACE( "You should see no text, then text render and then disappear" );
        Uint32 futureTime = SDL_GetTicks() + 2000;
        while( SDL_GetTicks() < futureTime )
        {
            SDLRenderer::GetInstance()->Draw();
        }
    }

    void testAnimationExample()
    {
        TS_TRACE( "You should see text, then the number 1, then the number 2, then the number 3" );

        SDLRenderableVec frames;

        SDL_Surface* texture = NULL;
        texture = SDLRenderer::GetInstance()->CreateTextSurface( "Animation Commencing", 12, 255, 255, 255 );
        TS_ASSERT( texture );
        ExampleRenderable* temporaryRenderable = new ExampleRenderable();
        temporaryRenderable->SetTexture( texture );

        frames.push_back( temporaryRenderable );

        texture = SDLRenderer::GetInstance()->CreateTextSurface( "1", 12, 255, 255, 255 );
        TS_ASSERT( texture );
        temporaryRenderable = new ExampleRenderable();
        temporaryRenderable->SetTexture( texture );

        frames.push_back( temporaryRenderable );

        texture = NULL;
        texture = SDLRenderer::GetInstance()->CreateTextSurface( "2", 12, 255, 255, 255 );
        TS_ASSERT( texture );
        temporaryRenderable = new ExampleRenderable();
        temporaryRenderable->SetTexture( texture );

        frames.push_back( temporaryRenderable );

        texture = NULL;
        texture = SDLRenderer::GetInstance()->CreateTextSurface( "3", 12, 255, 255, 255 );
        TS_ASSERT( texture );
        temporaryRenderable = new ExampleRenderable();
        temporaryRenderable->SetTexture( texture );

        frames.push_back( temporaryRenderable );

        Uint32 totalTime = SDL_GetTicks() + frames.size() * 500;

        SDLRenderer::GetInstance()->AddAnimation( frames, 500 );
        while( SDL_GetTicks() < totalTime )
        {
            SDLRenderer::GetInstance()->Draw();
        }
    }

};


#endif // __SDLRENDERERTEST_H

