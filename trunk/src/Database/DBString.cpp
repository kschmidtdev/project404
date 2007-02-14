/**
 * File: DBString.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Seung Woo Han, February 7 2007 | Initial design
 * Seung Woo Han, February 11 2007 | Done for all the basic implementation
 */

#include "DBString.h"                                     // class implemented

/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

DBString::DBString( const int uniqueID, const string& name, const string& stringData )
: DBData( uniqueID, name ), mStringData( stringData )
{
} // DBString

DBString::~DBString()
{
} // ~DBString

//============================= OPERATORS ====================================
//============================= OPERATIONS ===================================
//============================= ACCESS     ===================================
//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////
/////////////////////////////// PRIVATE    ///////////////////////////////////
