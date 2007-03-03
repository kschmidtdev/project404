/**
 * File: DBInt.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Seung Woo Han, February 7 2007 | Initial design
 * Seung Woo Han, February 11 2007 | Done for all the basic implementation
 */

#include <util.h>


#include "DBInt.h"                                        // class implemented

/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

DBInt::DBInt( const int uniqueID, const string& name, const int intData )
: DBData( uniqueID, name ),  mIntData( intData )
{
} // DBInt

DBInt::~DBInt()
{
} // ~DBInt

//============================= OPERATORS ====================================
//============================= OPERATIONS ===================================
//============================= ACCESS     ===================================
//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////
/////////////////////////////// PRIVATE    ///////////////////////////////////
