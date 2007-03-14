/**
 * File: City.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, March 13 2007 | Initial Creation
 * Karl Schmidt, March 14 2007   | Added city ID auto-increment, removed default constructor (unused)
 */
#include "City.h"                                // class implemented

int City::_idCount = 1;

/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

// Cities will probably be created by DBEngine

City::City(Point p, string fileName)
: mBattleMap( NULL ), mDefeated( false )
{
    mMapPos = p;
    mImageFilename = fileName;

    mID = _idCount;
    ++_idCount;
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
