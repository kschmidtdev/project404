/**
 * File: UIOverMap.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, March 4, 2007 | Initial Creation
 * Karl Schmidt, March 9 2007	 | Changed textures to png
 * Andrew Osborne, March 12, 2007 | Added "UpdateMap"
 * Karl Schmidt, March 12 2007	 | Added battle initialization to starting a new level
 * Andrew Osborne, March 13 2007 | OverMapTile now calls BattleInit
 */
#include "UIOverMap.h"                                // class implemented
#include "UIManager.h"
#include "GameEngine/GameEngine.h"

/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

UIOverMap::UIOverMap()
: mDefaultTile( NULL ), mCurrentLevelProgression( 0 )
{

    // Simulate input from cities
    // blah, blah, blah

    // Create Tile elements
    vector<City*>* cityVector = GameEngine::GetInstance()->GetCities();
    vector<City*>::iterator iter;

    for (iter = cityVector->begin(); iter != cityVector->end(); ++iter)
    {
            mMapTiles.push_back( UIOverMapTile( (*iter) ) );
    }


    //mMapTiles.push_back( UIOverMapTile(130,350) );
    //mMapTiles.push_back( UIOverMapTile(180,270) );
    //mMapTiles.push_back( UIOverMapTile(250,170) );
    //mMapTiles.push_back( UIOverMapTile(390,70) );

    mMapTiles[0].SetNextPrev( &mMapTiles[1] , NULL);
    mMapTiles[1].SetNextPrev( &mMapTiles[2], &mMapTiles[0]);
    mMapTiles[2].SetNextPrev( &mMapTiles[3], &mMapTiles[1]);
    mMapTiles[3].SetNextPrev( &mMapTiles[4], &mMapTiles[2]);
    mMapTiles[4].SetNextPrev( NULL, &mMapTiles[3]);

    // Some Debug
    //mMapTiles[0].LevelDefeated();

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
        {
            // Temporary until true functionality is added

            // Temporarily hardcoding this initialization (until the UI has the overmap that does this)
            vector<Character*> partyTemp;
            mCursor.GetCurTile()->BattleInit();

            UIManager::GetInstance()->PushLayout("BattleScreen");
        }
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

void UIOverMap::UpdateMap(void)
{

    for(MapTileItr iter = mMapTiles.begin(); iter !=mMapTiles.end(); ++iter)
    {
        (*iter).Update();
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
