/**
 * File: DBColour.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Seung Woo Han, February 7 2007 | Initial design
 * Seung Woo Han, February 11 2007 | Done for all the basic implementation
 */

#include "DBColour.h"

DBColour::DBColour(const int uniqueID, const string& name, const int* colourData)
: DBData(uniqueID, name)
{

    for (int i=0; i<3; i++) mColourData[i] = colourData[i];

}

DBColour::~DBColour()
{
}

