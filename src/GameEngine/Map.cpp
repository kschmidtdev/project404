/**
 * File: Map.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Mike Malyuk, February 9, 2007 | Initial design
 * Mike Malyuk, February 11 2007 | Removed unused code
 * Mike Malyuk, March 9, 2007    | Added default constructor implementation and GetTiles()
 */

#include <util.h>

#include "Map.h"                                // class implemented


/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

Map::Map()
{
    mTiles.push_back( Tile(Point(0,0), "GRASS"));
    mTiles.push_back( Tile(Point(0,1), "GRASS"));
    mTiles.push_back( Tile(Point(0,2), "GRASS"));
    mTiles.push_back( Tile(Point(0,3), "GRASS"));
    mTiles.push_back( Tile(Point(0,4), "GRASS"));
    mTiles.push_back( Tile(Point(0,5), "GRASS"));
    mTiles.push_back( Tile(Point(0,6), "GRASS"));
    mTiles.push_back( Tile(Point(0,7), "GRASS"));
    mTiles.push_back( Tile(Point(0,8), "GRASS"));
    mTiles.push_back( Tile(Point(0,9), "GRASS"));
    mTiles.push_back( Tile(Point(1,0), "GRASS"));
    mTiles.push_back( Tile(Point(1,1), "GRASS"));
    mTiles.push_back( Tile(Point(1,2), "GRASS"));
    mTiles.push_back( Tile(Point(1,3), "GRASS"));
    mTiles.push_back( Tile(Point(1,4), "GRASS"));
    mTiles.push_back( Tile(Point(1,5), "GRASS"));
    mTiles.push_back( Tile(Point(1,6), "GRASS"));
    mTiles.push_back( Tile(Point(1,7), "GRASS"));
    mTiles.push_back( Tile(Point(1,8), "GRASS"));
    mTiles.push_back( Tile(Point(1,9), "GRASS"));
    mTiles.push_back( Tile(Point(2,0), "ROAD"));
    mTiles.push_back( Tile(Point(2,1), "ROAD"));
    mTiles.push_back( Tile(Point(2,2), "ROAD"));
    mTiles.push_back( Tile(Point(2,3), "ROAD"));
    mTiles.push_back( Tile(Point(2,4), "ROAD"));
    mTiles.push_back( Tile(Point(2,5), "ROAD"));
    mTiles.push_back( Tile(Point(2,6), "GRASS"));
    mTiles.push_back( Tile(Point(2,7), "GRASS"));
    mTiles.push_back( Tile(Point(2,8), "GRASS"));
    mTiles.push_back( Tile(Point(2,9), "GRASS"));
    mTiles.push_back( Tile(Point(3,0), "GRASS"));
    mTiles.push_back( Tile(Point(3,1), "GRASS"));
    mTiles.push_back( Tile(Point(3,2), "GRASS"));
    mTiles.push_back( Tile(Point(3,3), "GRASS"));
    mTiles.push_back( Tile(Point(3,4), "GRASS"));
    mTiles.push_back( Tile(Point(3,5), "ROAD"));
    mTiles.push_back( Tile(Point(3,6), "GRASS"));
    mTiles.push_back( Tile(Point(3,7), "GRASS"));
    mTiles.push_back( Tile(Point(3,8), "GRASS"));
    mTiles.push_back( Tile(Point(3,9), "GRASS"));
    mTiles.push_back( Tile(Point(4,0), "GRASS"));
    mTiles.push_back( Tile(Point(4,1), "GRASS"));
    mTiles.push_back( Tile(Point(4,2), "GRASS"));
    mTiles.push_back( Tile(Point(4,3), "GRASS"));
    mTiles.push_back( Tile(Point(4,4), "GRASS"));
    mTiles.push_back( Tile(Point(4,5), "ROAD"));
    mTiles.push_back( Tile(Point(4,6), "GRASS"));
    mTiles.push_back( Tile(Point(4,7), "GRASS"));
    mTiles.push_back( Tile(Point(4,8), "GRASS"));
    mTiles.push_back( Tile(Point(4,9), "GRASS"));
    mTiles.push_back( Tile(Point(5,0), "WATER"));
    mTiles.push_back( Tile(Point(5,1), "WATER"));
    mTiles.push_back( Tile(Point(5,2), "WATER"));
    mTiles.push_back( Tile(Point(5,3), "WATER"));
    mTiles.push_back( Tile(Point(5,4), "WATER"));
    mTiles.push_back( Tile(Point(5,5), "ROAD"));
    mTiles.push_back( Tile(Point(5,6), "GRASS"));
    mTiles.push_back( Tile(Point(5,7), "GRASS"));
    mTiles.push_back( Tile(Point(5,8), "GRASS"));
    mTiles.push_back( Tile(Point(5,9), "GRASS"));
    mTiles.push_back( Tile(Point(6,0), "GRASS"));
    mTiles.push_back( Tile(Point(6,1), "GRASS"));
    mTiles.push_back( Tile(Point(6,2), "GRASS"));
    mTiles.push_back( Tile(Point(6,3), "GRASS"));
    mTiles.push_back( Tile(Point(6,4), "GRASS"));
    mTiles.push_back( Tile(Point(6,5), "ROAD"));
    mTiles.push_back( Tile(Point(6,6), "WATER"));
    mTiles.push_back( Tile(Point(6,7), "WATER"));
    mTiles.push_back( Tile(Point(6,8), "WATER"));
    mTiles.push_back( Tile(Point(6,9), "WATER"));
    mTiles.push_back( Tile(Point(7,0), "GRASS"));
    mTiles.push_back( Tile(Point(7,1), "GRASS"));
    mTiles.push_back( Tile(Point(7,2), "GRASS"));
    mTiles.push_back( Tile(Point(7,3), "GRASS"));
    mTiles.push_back( Tile(Point(7,4), "ROAD"));
    mTiles.push_back( Tile(Point(7,5), "ROAD"));
    mTiles.push_back( Tile(Point(7,6), "ROAD"));
    mTiles.push_back( Tile(Point(7,7), "ROAD"));
    mTiles.push_back( Tile(Point(7,8), "ROAD"));
    mTiles.push_back( Tile(Point(7,9), "ROAD"));
    mTiles.push_back( Tile(Point(8,0), "GRASS"));
    mTiles.push_back( Tile(Point(8,1), "GRASS"));
    mTiles.push_back( Tile(Point(8,2), "GRASS"));
    mTiles.push_back( Tile(Point(8,3), "GRASS"));
    mTiles.push_back( Tile(Point(8,4), "ROAD"));
    mTiles.push_back( Tile(Point(8,5), "GRASS"));
    mTiles.push_back( Tile(Point(8,6), "GRASS"));
    mTiles.push_back( Tile(Point(8,7), "GRASS"));
    mTiles.push_back( Tile(Point(8,8), "GRASS"));
    mTiles.push_back( Tile(Point(8,9), "GRASS"));
    mTiles.push_back( Tile(Point(9,0), "GRASS"));
    mTiles.push_back( Tile(Point(9,1), "GRASS"));
    mTiles.push_back( Tile(Point(9,2), "GRASS"));
    mTiles.push_back( Tile(Point(9,3), "GRASS"));
    mTiles.push_back( Tile(Point(9,4), "ROAD"));
    mTiles.push_back( Tile(Point(9,5), "GRASS"));
    mTiles.push_back( Tile(Point(9,6), "GRASS"));
    mTiles.push_back( Tile(Point(9,7), "GRASS"));
    mTiles.push_back( Tile(Point(9,8), "GRASS"));
    mTiles.push_back( Tile(Point(9,9), "GRASS"));
}// Map
Map::Map(vector<Tile> tiles)
:mTiles(tiles)
{
}
Map::~Map()
{
}// ~Map

//============================= OPERATIONS ===================================
//============================= ACCESS     ===================================
void Map::AddTiles(Tile tile)
{
    mTiles.push_back(tile);
}
//============================= INQUIRY    ===================================
Tile Map::GetTile(Point p)
{
    vector<Tile>::iterator iter;
    iter = mTiles.begin();
    while( ((*iter).GetPoint()) != p && iter != mTiles.end())
    {
        iter++;
    }
    if(((*iter).GetPoint()) == p)
    {
        return *iter;
    }

    //should throw exception
    else
    {
        return (*mTiles.begin());
    }
}

vector<Tile> Map::GetTiles()
{
    return mTiles;
}
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
