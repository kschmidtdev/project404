/**
 * File: ResourceManager.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Name, Date | Work Done
 * Karl Schmidt, February 9 2007 | Initial creation and stubbing out of methods
 */
#include "ResourceManager.h"                                // class implemented

#include "Resource.h"
#include "TextureResource.h"

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
    // stub
}

void ResourceManager::Shutdown()
{
    for( ResourceVecItr i = mLoadedResources.begin(); i != mLoadedResources.end(); ++i )
    {
        (*i)->Unload();
        delete *i;
    }
}

//============================= OPERATORS ====================================

//============================= OPERATIONS ===================================
//============================= ACCESS     ===================================
//============================= INQUIRY    ===================================

SDL_Surface* ResourceManager::LoadTexture( const string fileName )
{
    Resource* toLoad = LoadResource( fileName );

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

Resource* ResourceManager::LoadResource( const string fileName )
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
