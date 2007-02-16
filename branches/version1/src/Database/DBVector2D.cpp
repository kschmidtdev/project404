/**
 * File: DBVector2D.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Seung Woo Han, February 7 2007 | Initial design
 * Seung Woo Han, February 11 2007 | Done for all the basic implementation
 */

#include "DBVector2D.h"                                   // class implemented

/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

DBVector2D::DBVector2D( const int uniqueID, const string& name, const int* vector2DData )
: DBData( uniqueID, name )
{
    for (int i=0; i<2; i++) mVector2DData[i] = vector2DData[i];
} // DBVector2D

DBVector2D::~DBVector2D()
{
} // ~DBVector2D

//============================= OPERATORS ====================================
//============================= OPERATIONS ===================================
//============================= ACCESS     ===================================
//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////
/////////////////////////////// PRIVATE    ///////////////////////////////////
