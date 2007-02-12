/**
 * File: WeaponItem.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Mike Malyuk, February 7 2007 | Initial design
 */

#include "WeaponItem.h"                                // class implemented

/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================
WeaponItem::WeaponItem(string name, int attr)
{
    mName = name;
    mValue = attr;
}

WeaponItem::~WeaponItem()
{
}// ~WeaponItem
//============================= OPERATIONS ===================================
//============================= ACCESS     ===================================
//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
