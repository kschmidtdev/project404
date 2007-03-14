/**
 * File: City.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, March 13 2007 | Initial Creation
 */
#include "City.h"                                // class implemented


/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

// Cities will probably be created by DBEngine

City::City()
: mBattleMap( NULL ), mDefeated( false )
{
    mImageFilename = "victory.png";
}// City

City::City(Point p, string fileName)
: mBattleMap( NULL ), mDefeated( false )
{
    mMapPos = p;
    mImageFilename = fileName;
}

City::~City()
{
}// ~City


//============================= OPERATORS ====================================



//============================= OPERATIONS ===================================
//============================= ACCESS     ===================================

void City::SetDefeated(bool n)
{
    mDefeated = n;
}

//============================= INQUIRY    ===================================

bool City::IsDefeated(void)
{
    return mDefeated;
}

Point City::GetMapPos(void)
{
    return mMapPos;
}


string City::GetImageName(void)
{
    return mImageFilename;
}

/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
