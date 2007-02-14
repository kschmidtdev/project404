/**
 * File: DBFloat.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Seung Woo Han, February 7 2007 | Initial design
 * Seung Woo Han, February 11 2007 | Done for all the basic implementation
 */

#include "DBFloat.h"                                      // class implemented

/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

DBFloat::DBFloat( const int uniqueID, const string& name, const float floatData )
: DBData( uniqueID, name ), mFloatData( floatData )
{
} // DBFloat

DBFloat::~DBFloat()
{
} // ~DBFloat

//============================= OPERATORS ====================================
//============================= OPERATIONS ===================================
//============================= ACCESS     ===================================
//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////
/////////////////////////////// PRIVATE    ///////////////////////////////////
