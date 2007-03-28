/**
 * File: WeaponItem.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Mike Malyuk, February 7 2007 | Initial design
 * Mike Malyuk, March 27 2007   | Adding cost of items
 */

#include <util.h>


#include "WeaponItem.h"                                // class implemented

/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================
WeaponItem::WeaponItem(string name, int attr)
{
    mName = name;
    mValue = attr;
    mCost = 1000;
}

WeaponItem::~WeaponItem()
{
}// ~WeaponItem
//============================= OPERATIONS ===================================
//============================= ACCESS     ===================================
//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
