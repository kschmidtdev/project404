/**
 * File: Tile.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Mike Malyuk, February 9, 2007 | Initial design
 */
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
       mWeight = 1;
    }
    //list types here
    else
    {
        mWeight = 2;
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
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
