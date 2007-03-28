/**
 * File: City.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, March 13 2007 | Initial Creation
 * Karl Schmidt, March 14 2007   | Added city ID auto-increment, removed default constructor (unused)
 * Mike Malyuk,  March 27 2007   | Adding items to all cities. Fixing destructor to work with this.
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
    mArmoryItems.push_back(new ArmorItem("Chain Mail", 5));
    mArmoryItems.push_back(new ArmorItem("Leather Jerkin", 2));
    mArmoryItems.push_back(new ArmorItem("Steel Plate", 7));
    mMarketItems.push_back(new WeaponItem("Blades of Steel", 3));
    mMarketItems.push_back(new WeaponItem("Vorpal Sword", 5));
    mMarketItems.push_back(new WeaponItem("Rat Flail", 1));
    mID = _idCount;
    ++_idCount;
}

City::~City()
{
    for(vector<Item*>::iterator item = mArmoryItems.begin(); item != mArmoryItems.end(); item++)
    {
        delete (*item);
    }
    for(vector<Item*>::iterator item = mMarketItems.begin(); item != mMarketItems.end(); item++)
    {
        delete (*item);
    }
    mArmoryItems.clear();
    mMarketItems.clear();
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
