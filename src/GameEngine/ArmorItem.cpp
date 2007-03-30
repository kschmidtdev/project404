/**
 * File: ArmorItem.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Mike Malyuk, February 7 2007 | Initial design
 * Mike Malyuk, March 27, 2007  | Added cost
 * Andrew Osborne, March 29 2007 | Added 'type' declaration.
 */

#include <util.h>


#include "ArmorItem.h"                                // class implemented


/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

ArmorItem::ArmorItem(string name, int attr)
{
    mName = name;
    mValue = attr;
    mCost = 1000;
    mType = Item::ARMOR;
}
ArmorItem::~ArmorItem()
{
}// ~ArmorItem


//============================= OPERATIONS ===================================
//============================= ACCESS     ===================================
//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
