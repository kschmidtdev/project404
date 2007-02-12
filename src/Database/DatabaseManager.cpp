/**
 * File: DatabaseManager.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Seung Woo Han, February 7 2007 | Initial design
 * Seung Woo Han, February 11 2007 | Added LaodFromFile() function which handles XML.
 */

#include "DatabaseManager.h"
#include <iostream> // test
using namespace std; // test

DatabaseManager::DatabaseManager()
{
}

DatabaseManager::~DatabaseManager()
{
}

int DatabaseManager::GenerateUniqueID()
{
    int uniqueID =  10000000 + mSize;
    mSize++;
    return uniqueID;
}

void DatabaseManager::LoadFromFile()
{
    TiXmlDocument Document( "database.xml" );
	bool loadOkay = Document.LoadFile();

	if (loadOkay)
	{

        TiXmlHandle docHandle( &Document );

        TiXmlElement* Root = docHandle.FirstChild().ToElement();

        cout << Root->Value() << endl;









	}

	else
	{
	    // if loading xml file is failed.
    }
}
