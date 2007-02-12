/**
 * File: DBData.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Seung Woo Han, February 7 2007 | Initial design
 * Seung Woo Han, February 11 2007 | Done for all the basic implementation
 */

#include "DBData.h"

DBData::DBData(const int uniqueID, const string& name)
: DBBase(uniqueID), mName(name)
{
}

DBData::~DBData()
{
}
