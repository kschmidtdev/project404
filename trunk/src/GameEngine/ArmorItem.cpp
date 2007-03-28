/**
 * File: ArmorItem.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Mike Malyuk, February 7 2007 | Initial design
 * Mike Malyuk, March 27, 2007  | Added cost
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
}
ArmorItem::~ArmorItem()
{
}// ~ArmorItem


//============================= OPERATIONS ===================================
//============================= ACCESS     ===================================
//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
