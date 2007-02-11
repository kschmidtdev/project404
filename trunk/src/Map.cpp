/**
 * File: Map.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Mike Malyuk, February 9, 2007 | Initial design
 */
#include "Map.h"                                // class implemented


/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

Map::Map()
{
}// Map
Map::Map(vector<Tile*> tiles)
:mTiles(tiles)
{
}
Map::~Map()
{
}// ~Map

//============================= OPERATIONS ===================================
//============================= ACCESS     ===================================
void Map::AddTiles(Tile* tile)
{
    mTiles.push_back(tile);
}
//============================= INQUIRY    ===================================
Tile* Map::GetTile(Point p)
{
    vector<Tile*>::iterator iter;
    iter = mTiles.begin();
    (*iter)->GetPoint();
    while( ((*iter)->GetPoint()) != p && iter != mTiles.end())
    {
        iter++;
    }
    if(((*iter)->GetPoint()) == p)
    {
        return *iter;
    }
    else
    {
        return NULL;
    }
}
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
