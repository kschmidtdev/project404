/**
 * File: UIOverMap.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, March 4, 2007 | Initial Creation
 * Karl Schmidt, March 9 2007	 | Changed textures to png
 */
#include "UIOverMap.h"                                // class implemented
#include "UIManager.h"

/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

UIOverMap::UIOverMap()
: mDefaultTile( NULL )
{

    // Simulate input from cities
    // blah, blah, blah

    // Create Tile elements
    mMapTiles.push_back( UIOverMapTile(20,400) );
    mMapTiles.push_back( UIOverMapTile(130,350) );
    mMapTiles.push_back( UIOverMapTile(180,270) );
    mMapTiles.push_back( UIOverMapTile(250,170) );
    mMapTiles.push_back( UIOverMapTile(390,70) );

    UIOverMapTile* dummy = NULL;

    mMapTiles[0].SetNextPrev( NULL , &mMapTiles[1]);
    mMapTiles[1].SetNextPrev( &mMapTiles[0], &mMapTiles[2]);
    mMapTiles[2].SetNextPrev( &mMapTiles[1], &mMapTiles[3]);
    mMapTiles[3].SetNextPrev( &mMapTiles[2], &mMapTiles[4]);
    mMapTiles[4].SetNextPrev( &mMapTiles[3], dummy );



    mElementImage = ResourceManager::GetInstance()->LoadTexture("castle_main.png");

    //mPos.Set(30, 30);
    SetPos(mPos);

    mCursor.SetCurTile( &mMapTiles[0] );


}// UIOverMap



UIOverMap::~UIOverMap()
{
    mMapTiles.clear();
}// ~UIOverMap


//============================= OPERATORS ====================================



//============================= OPERATIONS ===================================


void UIOverMap::ProcessEvent( const InputManager::INPUTKEYS evt )
{
    UIOverMapTile* temp;
    switch(evt)
    {
        case InputManager::LEFT:
            // Attempt to move left
            temp = mCursor.GetCurTile();
            temp = temp->GetLeft();
            if (temp!=NULL)
            {
                mCursor.SetCurTile(temp);
            }
            break;
        case InputManager::RIGHT:
            // Attempt to move left
            temp = mCursor.GetCurTile();
            temp = temp->GetRight();
            if (temp!=NULL)
            {
                mCursor.SetCurTile(temp);
            }
            break;
        case InputManager::UP:
            // Attempt to move left
            temp = mCursor.GetCurTile();
            temp = temp->GetUp();
            if (temp!=NULL)
            {
                mCursor.SetCurTile(temp);
            }
            break;
        case InputManager::DOWN:
            // Attempt to move left
            temp = mCursor.GetCurTile();
            temp = temp->GetDown();
            if (temp!=NULL)
            {
                mCursor.SetCurTile(temp);
            }
            break;
        case InputManager::CONFIRM:
            // Temporary until true functionality is added
            UIManager::GetInstance()->PushLayout("BattleScreen");
            break;
        default:
            // Do nothing
            break;
    }

}

void UIOverMap::RenderSelf(SDL_Surface* destination)
{


    UIElement::RenderSelf(destination);

    if (mVisible)
    {
        MapTileItr iter;

        // Move points in OverMap to relative position
        iter = mMapTiles.begin();
        while (iter!=mMapTiles.end())
        {
            (*iter).RenderSelf(destination);
            iter++;
        }

        // Draw cursor on top
        mCursor.RenderSelf(destination);
    }



}

void UIOverMap::SetMapProgression(int newLevel)
{
    //if (newLevel>mCurrentLevelProgression)
        //for (int i=mCurrentLevelProgression; i<=newLevel; i++)


}

//============================= ACCESS     ===================================

void UIOverMap::SetPos( const Point & nPos )
{
    //Point tempPoint;
    MapTileItr iter;

    // Move points in OverMap to relative position
    iter = mMapTiles.begin();
    while (iter!=mMapTiles.end())
    {
        //tempPoint = (*iter).GetPos();
        (*iter).SetPos( mPos + (*iter).GetMapOffset() );
        iter++;
    }

}


//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
