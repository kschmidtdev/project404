/**
 * File: DatabaseManager.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Seung Woo Han, February 7 2007 | Initial design
 * Seung Woo Han, February 11 2007 | Added LoadFromFile() function which handles XML.
 * Karl Schmidt, February 13 2007 | Added code to make DatabaseManager a singleton, fixed a warning
 */

#include "DatabaseManager.h"
#include <iostream> // test
using namespace std; // test

DatabaseManager* DatabaseManager::_instance = 0;

DatabaseManager* DatabaseManager::GetInstance()
{
    if( !_instance )
    {
        _instance = new DatabaseManager();
    }
    return _instance;
}

DatabaseManager::~DatabaseManager()
{
}

void DatabaseManager::Initialize()
{
    // stub
}

void DatabaseManager::Shutdown()
{
    // stub
}

int DatabaseManager::GenerateUniqueID()
{
    int uniqueID =  10000000 + mSize;
    mSize++;
    return uniqueID;
}

bool DatabaseManager::LoadFromFile(const string& filename)
{
    TiXmlDocument Document( filename );
	bool loadOkay = Document.LoadFile();

	if (loadOkay)
	{
	    TiXmlHandle docHandle( &Document );

        TiXmlElement* XML_Root = docHandle.FirstChild().ToElement();
        mRootNode = new DBNode( GenerateUniqueID(), "Database" ); // Save the first xml node to the mRootNode.
        mSearchList.push_back( mRootNode );

        CreateSiblingNode( XML_Root->FirstChildElement(), mRootNode ); // Recursive function to traverse all XML tags and create DBNode objects.
        return true;
    }

	else
	{
        return false;
    }
}

DBNode* DatabaseManager::Search(const string& name)
{
    vector<DBNode*>::iterator Iter;
    for ( Iter = mSearchList.begin(); Iter != mSearchList.end(); Iter++ )
    {
        if ( (*Iter)->GetName() == name ) return *Iter;
    }

    return NULL;
}

/////////////////////////////// PRIVATE    ///////////////////////////////////

void DatabaseManager::CreateSiblingNode( TiXmlElement* currentNode, DBNode* parent ) // All sibling nodes have the same parent node.
{
    if ( currentNode != NULL ) // If currentNode == NULL, the recursion terminate.
    {
        if ( currentNode->ValueStr() == "Data" )
        {
            parent->AddAttribute( CreateAttribute( currentNode ) );
            CreateSiblingNode( currentNode->NextSiblingElement(), parent );
        }

        else
        {
            DBNode* newChild = new DBNode( GenerateUniqueID(), currentNode->Attribute( "name" ), parent );
            parent->AddChild(newChild);
            mSearchList.push_back( newChild );

            CreateChildNode( currentNode->FirstChildElement(), newChild );
            CreateSiblingNode( currentNode->NextSiblingElement(), parent );
        }
    }
}

void DatabaseManager::CreateChildNode( TiXmlElement* currentNode, DBNode* parent )
{
    if ( currentNode != NULL ) // If currentNode == NULL, the recursion terminate.
    {
        if ( currentNode->ValueStr() == "Data" )
        {
            parent->AddAttribute( CreateAttribute( currentNode ) );
            CreateSiblingNode( currentNode->NextSiblingElement(), parent );
        }

        else
        {
            DBNode* newChild = new DBNode( GenerateUniqueID(), currentNode->Attribute( "name" ), parent );
            parent->AddChild( newChild );
            mSearchList.push_back( newChild );

            CreateChildNode( currentNode->FirstChildElement(), newChild );
            CreateSiblingNode( currentNode->NextSiblingElement(), parent );
        }
    }
}

DBData* DatabaseManager::CreateAttribute( TiXmlElement* thisTag )
{
    string attributeType( thisTag->Attribute( "type" ) );

    if ( attributeType == "string" )
    {
        DBString* newString = new DBString( GenerateUniqueID(), thisTag->Attribute( "name" ), thisTag->Attribute( "value" ) );
        return newString;
    }
    else if ( attributeType == "int" )
    {
        int value = 0;
        thisTag->Attribute( "value", &value );
        DBInt* newInt = new DBInt( GenerateUniqueID(), thisTag->Attribute( "name" ), value );
        return newInt;
    }
    else if ( attributeType == "float" )
    {
        double value = 0;
        thisTag->Attribute( "value", &value );
        DBFloat* newFloat = new DBFloat( GenerateUniqueID(), thisTag->Attribute( "name" ), value );
        return newFloat;
    }
    else if ( attributeType == "vector2d" )
    {
        string value( thisTag->Attribute( "value" ) );
        string strX( value, 0, value.find(":") ); // parsing to ':'
        string strY( value, value.find(":")+1 ); // parsing from ':'
        int nX = atoi(strX.c_str());
        int nY = atoi(strY.c_str());

        int XY[2] = {nX, nY};
        DBVector2D * newVector2D = new DBVector2D( GenerateUniqueID(), thisTag->Attribute( "name" ), XY );
        return newVector2D;
    }
    else if ( attributeType == "colour" )
    {
        // Not implemented yet
        return NULL;
    }
    else // unknown type.
    {
        return NULL;
    }
}

// PROTECTED

DatabaseManager::DatabaseManager()
{
}

