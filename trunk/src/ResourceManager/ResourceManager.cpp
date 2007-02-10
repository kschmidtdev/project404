/**
 * File: ResourceManager.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Karl Schmidt, February 9 2007 | Initial creation and stubbing out of methods
 */
#include "ResourceManager.h"                                // class implemented

#include "Resource.h"
#include "TextureResource.h"
#include "Logger.h"

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
        // TODO: assert toLoad here
        toLoad->Load();
        mLoadedResources.push_back( toLoad );
    }
    return static_cast<TextureResource*>(toLoad)->GetTexture();
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
