/**
 * File: ResourceManager.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Karl Schmidt, February 10 2007 | Added support for sound and music resources, added some assertions
 * Karl Schmidt, February 9 2007 | Initial creation and stubbing out of methods
 */
#include "ResourceManager.h"                                // class implemented

#include "Resource.h"
#include "TextureResource.h"
#include "SoundResource.h"
#include "MusicResource.h"

#include "Logger.h"
#include "util.h"

ResourceManager* ResourceManager::_instance = 0;

/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

ResourceManager* ResourceManager::GetInstance()
{
    if( !_instance )
    {
        _instance = new ResourceManager();
    }
    return _instance;
}

ResourceManager::~ResourceManager(void)
{
    // stub
}

void ResourceManager::Initialize()
{
    LogInfo( "The ResourceManager has been initialized successfully." );
    // stub
}

void ResourceManager::Shutdown()
{
    LogInfo( "Beginning ResourceManager shut down..." );
    for( ResourceVecItr i = mLoadedResources.begin(); i != mLoadedResources.end(); ++i )
    {
        (*i)->Unload();
        delete *i;
    }
    delete _instance;
    _instance = NULL;
    LogInfo( "The ResourceManager has been shut down successfully." );
}

//============================= OPERATORS ====================================

//============================= OPERATIONS ===================================
//============================= ACCESS     ===================================
//============================= INQUIRY    ===================================

SDL_Surface* ResourceManager::LoadTexture( const string fileName )
{
    Resource* toLoad = CheckForResource( fileName );

    if( !toLoad )
    {
        toLoad = new TextureResource( fileName );

        tacAssert( toLoad );
        toLoad->Load();
        mLoadedResources.push_back( toLoad );
    }
    return static_cast<TextureResource*>(toLoad)->GetTexture();
}

Mix_Chunk* ResourceManager::LoadSound( const string fileName )
{
    Resource* toLoad = CheckForResource( fileName );

    if( !toLoad )
    {
        toLoad = new SoundResource( fileName );

        tacAssert( toLoad );
        toLoad->Load();
        mLoadedResources.push_back( toLoad );
    }
    return static_cast<SoundResource*>(toLoad)->GetSound();
}

Mix_Music* ResourceManager::LoadMusic( const string fileName )
{
    Resource* toLoad = CheckForResource( fileName );

    if( !toLoad )
    {
        toLoad = new MusicResource( fileName );

        tacAssert( toLoad );
        toLoad->Load();
        mLoadedResources.push_back( toLoad );
    }
    return static_cast<MusicResource*>(toLoad)->GetMusic();
}

/////////////////////////////// PROTECTED  ///////////////////////////////////

Resource* ResourceManager::CheckForResource( const string fileName )
{
    for( ResourceVecItr i = mLoadedResources.begin(); i != mLoadedResources.end(); ++i )
    {
        if( (*i)->GetFileName() == fileName )
        {
            return (*i);
        }
    }
    return NULL;
}

ResourceManager::ResourceManager()
{
}// ResourceManager

/////////////////////////////// PRIVATE    ///////////////////////////////////
