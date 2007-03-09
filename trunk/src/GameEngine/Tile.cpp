/**
 * File: Tile.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Mike Malyuk, February 9, 2007 | Initial design
 * Mike Malyuk, March 8 2007     | Added Tile mPic getter, allows UI to create easier
 */

#include <util.h>

#include "Tile.h"                                // class implemented


/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

Tile::Tile()
: mTilePoint(Point(0,0)), mType("GRASS"), mWeight(1)
{
}// Tile

Tile::Tile(Point p, string type)
: mTilePoint(p), mType(type)
{
    if(type.compare("GRASS") == 0)
    {
       mWeight = 2;
       mPic = "grass.bmp";
    }
    //list types here
    else if(type.compare("WATER") == 0)
    {
        mWeight = 3;
        mPic = "water.bmp";
    }
    else if(type.compare("ROAD") == 0)
    {
        mWeight = 1;
        mPic = "road.bmp";
    }
    else
    {
        mWeight = 2;
        mPic = "defaultTile.bmp";
    }
}

Tile::~Tile()
{
}// ~Tile

//============================= OPERATIONS ===================================
//============================= ACCESS     ===================================
//============================= INQUIRY    ===================================
Point Tile::GetPoint()
{
    return mTilePoint;
}
int Tile::GetWeight()
{
    return mWeight;
}
string Tile::GetType()
{
    return mType;
}
string Tile::GetPic()
{
    return mPic;
}
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////