/**
 * File: Tile.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Mike Malyuk, February 9, 2007 | Initial design
 * Mike Malyuk, March 8 2007     | Added Tile mPic getter, allows UI to create easier
 * Karl Schmidt, March 9 2007	 | Changed textures to png
 * Mike Malyuk, March 14 2007    | Added rock
 * Karl Schmidt, March 20 2007   | Major adding of consts and reference usage, rearranging includes
 */

#include "Tile.h"                                // class implemented
#include <util.h>

/*#include <string>
#include <iostream>*/

/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

Tile::Tile()
: mTilePoint( Point(0,0)), mType("GRASS"), mPic(""), mWeight(2)
{
}// Tile

Tile::Tile( const Point & p, const string & type )
: mTilePoint( p ), mType( type ), mPic(""), mWeight(0)
{
    if(type.compare("GRASS") == 0)
    {
       mWeight = 2;
       mPic = "grass.png";
    }
    //list types here
    else if(type.compare("WATER") == 0)
    {
        mWeight = 3;
        mPic = "water.png";
    }
    else if(type.compare("ROAD") == 0)
    {
        mWeight = 1;
        mPic = "road.png";
    }
    else if(type.compare("ROCK") == 0)
    {
        mWeight = INT_MAX;
        mPic = "rock.png";
    }
    else
    {
        mWeight = 2;
        mPic = "defaultTile.png";
    }
}

Tile::~Tile()
{
}// ~Tile

//============================= OPERATIONS ===================================
//============================= ACCESS     ===================================
//============================= INQUIRY    ===================================
const Point& Tile::GetPoint() const
{
    return mTilePoint;
}
const int Tile::GetWeight() const
{
    return mWeight;
}
const string& Tile::GetType() const
{
    return mType;
}
const string& Tile::GetPic() const
{
    return mPic;
}
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
