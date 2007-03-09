/**
 * File: UIOverMap.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, March 4, 2007 | Initial Creation
 */
#include "UIOverMap.h"                                // class implemented
#include "UIManager.h"

/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

UIOverMap::UIOverMap()
: mDefaultTile( NULL )
{
    // Create Tile elements
    mMapTiles.push_back( UIOverMapTile(20,230) );
    mMapTiles.push_back( UIOverMapTile(170,130) );
    mMapTiles.push_back( UIOverMapTile(250,30) );

    mMapTiles[0].SetRight( &mMapTiles[1] );
    mMapTiles[1].SetLeft( &mMapTiles[0] );
    mMapTiles[1].SetRight( &mMapTiles[2] );
    mMapTiles[1].SetUp( &mMapTiles[2] );
    mMapTiles[2].SetLeft( &mMapTiles[1] );
    mMapTiles[2].SetDown( &mMapTiles[1] );

    mElementImage = ResourceManager::GetInstance()->LoadTexture("castle_title.bmp");

    mPos.Set(30, 30);
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
        // Draw cursor first
        mCursor.RenderSelf(destination);

        MapTileItr iter;

        // Move points in OverMap to relative position
        iter = mMapTiles.begin();
        while (iter!=mMapTiles.end())
        {
            (*iter).RenderSelf(destination);
            iter++;
        }
    }



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
