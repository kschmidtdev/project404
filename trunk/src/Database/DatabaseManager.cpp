/**
 * File: DatabaseManager.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Seung Woo Han, February 7 2007 | Initial design
 * Seung Woo Han, February 11 2007 | Added LoadFromFile() function which handles XML.
 * Karl Schmidt, February 13 2007 | Added code to make DatabaseManager a singleton, fixed a warning
 * Seung Woo Han, March 14 2007 | SaveToFile and protected methods related to this is implemented.
 */

#include <util.h>
#include "DatabaseManager.h"                              // class implemented

/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

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
    vector<DBNode*>::iterator Iter;

    for (Iter=mSearchList.begin(); Iter!=mSearchList.end(); Iter++)
    {
        DBData* thisAttribute = (*Iter)->GetFirstAttribute();
        while ( thisAttribute != NULL )
        {
            delete thisAttribute; // delete attribute instances of each Node.
            thisAttribute = (*Iter)->GetNextAttribute();
        }

        delete (*Iter); // delete node instances.
    }

    if( _instance )
    {
        delete _instance; // delete DatabaseManager instance.
        _instance = NULL;
    }
}

//============================= OPERATORS ====================================
//============================= OPERATIONS ===================================

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

void DatabaseManager::SaveToFile( const string& filename )
{
    TiXmlDocument Document;

    // Save Root Node
    TiXmlElement * RootElement = new TiXmlElement( mRootNode->GetName() );
    Document.LinkEndChild( RootElement );

    // Save Each Node below Root Node.
    SaveSiblingNode( mRootNode->GetFirstChild(), RootElement );

    Document.SaveFile( filename );
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

bool DatabaseManager::UpdateNode( const string& nodeName, const string& attributeName, const string& value )
{
    DBNode* thisNode = Search( nodeName );
    if ( thisNode != NULL )
    {
        DBString* thisAttribute = dynamic_cast<DBString*>( thisNode->GetAttribute( attributeName ) );
        if ( thisAttribute != NULL )
        {
            thisAttribute->SetData( value );
            return true;
        }
    }

    return false;
}

bool DatabaseManager::UpdateNode( const string& nodeName, const string& attributeName, int value )
{
    DBNode* thisNode = Search( nodeName );
    if ( thisNode != NULL )
    {
        DBInt* thisAttribute = dynamic_cast<DBInt*>( thisNode->GetAttribute( attributeName ) );
        if ( thisAttribute != NULL )
        {
            thisAttribute->SetData( value );
            return true;
        }
    }

    return false;
}

bool DatabaseManager::UpdateNode( const string& nodeName, const string& attributeName, int xValue, int yValue )
{
    DBNode* thisNode = Search( nodeName );
    if ( thisNode != NULL )
    {
        DBVector2D* thisAttribute = dynamic_cast<DBVector2D*>( thisNode->GetAttribute( attributeName ) );
        if ( thisAttribute != NULL )
        {
            thisAttribute->SetX( xValue );
            thisAttribute->SetY( yValue );
            return true;
        }
    }

    return false;
}

//============================= ACCESS     ===================================
//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

DatabaseManager::DatabaseManager()
{
}

/////////////////////////////// PRIVATE    ///////////////////////////////////

int DatabaseManager::GenerateUniqueID()
{
    int uniqueID =  10000000 + mSize;
    mSize++;
    return uniqueID;
}

void DatabaseManager::CreateSiblingNode( TiXmlElement* currentElement, DBNode* parentNode ) // All sibling nodes have the same parent node.
{
    if ( currentElement != NULL ) // If currentNode == NULL, the recursion terminate.
    {
        if ( currentElement->ValueStr() == "Data" )
        {
            parentNode->AddAttribute( CreateAttribute( currentElement ) );
            CreateSiblingNode( currentElement->NextSiblingElement(), parentNode );
        }

        else
        {
            DBNode* newChildNode = new DBNode( GenerateUniqueID(), currentElement->Attribute( "name" ), parentNode );
            parentNode->AddChild( newChildNode );
            mSearchList.push_back( newChildNode );

            CreateChildNode( currentElement->FirstChildElement(), newChildNode );
            CreateSiblingNode( currentElement->NextSiblingElement(), parentNode );
        }
    }
}

void DatabaseManager::SaveSiblingNode( DBNode* currentNode, TiXmlElement* parentElement )
{
    if ( currentNode != NULL ) // If currentNode == NULL, the recursion terminate.
    {
        TiXmlElement * newElement = new TiXmlElement( "Node" );
        newElement->SetAttribute( "name", currentNode->GetName() );
        parentElement->LinkEndChild( newElement );

        SaveAttribute( currentNode, newElement );

        SaveChildNode( currentNode->GetFirstChild(), newElement );
        SaveSiblingNode( currentNode->GetRightSibling(), parentElement );
    }
}

void DatabaseManager::CreateChildNode( TiXmlElement* currentElement, DBNode* parentNode )
{
    if ( currentElement != NULL ) // If currentNode == NULL, the recursion terminate.
    {
        if ( currentElement->ValueStr() == "Data" )
        {
            parentNode->AddAttribute( CreateAttribute( currentElement ) );
            CreateSiblingNode( currentElement->NextSiblingElement(), parentNode );
        }

        else
        {
            DBNode* newChild = new DBNode( GenerateUniqueID(), currentElement->Attribute( "name" ), parentNode );
            parentNode->AddChild( newChild );
            mSearchList.push_back( newChild );

            CreateChildNode( currentElement->FirstChildElement(), newChild );
            CreateSiblingNode( currentElement->NextSiblingElement(), parentNode );
        }
    }
}

void DatabaseManager::SaveChildNode( DBNode* currentNode, TiXmlElement* parentElement )
{
    if ( currentNode != NULL ) // If currentNode == NULL, the recursion terminate.
    {
        TiXmlElement * newElement = new TiXmlElement( "Node" );
        newElement->SetAttribute( "name", currentNode->GetName() );
        parentElement->LinkEndChild( newElement );

        SaveAttribute( currentNode, newElement );

        SaveChildNode( currentNode->GetFirstChild(), newElement );
        SaveSiblingNode( currentNode->GetRightSibling(), parentElement );
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

void DatabaseManager::SaveAttribute( DBNode* thisNode, TiXmlElement* parentElement )
{
    DBData* newData = thisNode->GetFirstAttribute();
    string attributeType;

    while ( newData != NULL )
    {
        TiXmlElement * newElement = new TiXmlElement( "Data" );
        attributeType = newData->GetType();

        if ( attributeType == "DBString" )
        {
            newElement->SetAttribute( "type", "string" );
            newElement->SetAttribute( "name", newData->GetName() );

            DBString* newString = dynamic_cast<DBString*>( newData );
            newElement->SetAttribute( "value", newString->GetData() );
        }

        else if ( attributeType == "DBInt" )
        {
            newElement->SetAttribute( "type", "int" );
            newElement->SetAttribute( "name", newData->GetName() );

            DBInt* newInt = dynamic_cast<DBInt*>( newData );
            newElement->SetAttribute( "value", newInt->GetData() );
        }
        else if ( attributeType == "DBFloat" )
        {
            newElement->SetAttribute( "type", "float" );
            newElement->SetAttribute( "name", newData->GetName() );

            DBFloat* newFloat = dynamic_cast<DBFloat*>( newData );
            newElement->SetDoubleAttribute( "value", newFloat->GetData() );
        }
        else if ( attributeType == "DBVector2D" )
        {
            newElement->SetAttribute( "type", "vector2d" );
            newElement->SetAttribute( "name", newData->GetName() );

            DBVector2D* newVector2D = dynamic_cast<DBVector2D*>( newData );

            // Int -> String, Convert to X:Y form.
            string vector2dValue;
            std::stringstream oss; oss << newVector2D->GetX(); vector2dValue.append( oss.str() );
            vector2dValue.append( ":" );
            std::stringstream oss2 ;oss2 << newVector2D->GetY(); vector2dValue.append( oss2.str() );

            newElement->SetAttribute( "value", vector2dValue );
        }
        else if ( attributeType == "DBColour" )
        {
            // newElement->SetAttribute( "type", "colour" );
            // newElement->SetAttribute( "name", newData->GetName() );

            // DBColour* newColour = dynamic_cast<DBColour*>( newData );
            // Not implemented yet
        }
        else // unknown type.
        {
           // Not implemented yet
        }

        parentElement->LinkEndChild( newElement );
        newData = thisNode->GetNextAttribute();
    }
}
