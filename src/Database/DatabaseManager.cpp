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
    TiXmlDocument Document( "sample.xml" );
	bool loadOkay = Document.LoadFile();

	if (loadOkay)
	{
        TiXmlHandle docHandle( &Document );

        TiXmlElement* XML_Root = docHandle.FirstChild().ToElement();
        mRootNode = new DBNode( GenerateUniqueID(), "Database" ); // Save the first xml node to the mRootNode.

        CreateSiblingNode( XML_Root->FirstChildElement(), mRootNode ); // Recursive function to traverse all XML tags and create DBNode objects.
    }

	else
	{
	    cout << "Failed to Load." << endl; // if loading xml file is failed.
    }
}

string DatabaseManager::Search(string& name)
{
}

/////////////////////////////// PRIVATE    ///////////////////////////////////

void DatabaseManager::CreateSiblingNode(TiXmlElement* currentNode, DBNode* parent) { // All sibling nodes have the same parent node.

    if (currentNode != NULL) // If currentNode == NULL, the recursion terminate.
    {
        DBNode* newChild = new DBNode( GenerateUniqueID(), currentNode->Attribute( "name" ), parent );
        //cout << newChild->GetName() << endl;
        CreateChildNode( currentNode->FirstChildElement(), newChild );
        CreateSiblingNode( currentNode->NextSiblingElement(), parent );
    }
}

void DatabaseManager::CreateChildNode(TiXmlElement* currentNode, DBNode* parent) {

    if (currentNode != NULL) // If currentNode == NULL, the recursion terminate.
    {
        DBNode* newChild = new DBNode( GenerateUniqueID(), currentNode->Attribute( "name" ), parent );
        //cout << newChild->GetName() << endl;
        CreateChildNode( currentNode->FirstChildElement(), newChild );
        CreateSiblingNode( currentNode->NextSiblingElement(), parent );
    }
}

void DatabaseManager::ToNextSiblingNode(DBNode* parent)
{
}

void DatabaseManager::ToNextChildNode(DBNode* parent)
{
}
