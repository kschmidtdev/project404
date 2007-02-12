/**
 * This is a class which take a controll of whole database system.
 *
 * #include "DatabaseManager.h"
 *
 * Major functionalities : Load XML file and create DBNode objects and set a relationship among them
 *                         Save existing DBNode objects and their attributes to XML file.
 *                         Generate Unique ID and assign it to each Data and Nodes object in database.
 *
 * @see DBData.h
 *
 * Project 404 2007
 *
 * Authors:
 * Seung Woo Han, February 7 2007 | Initial design
 * Seung Woo Han, February 11 2007 | Done for all the basic implementation
 */

#ifndef DatabaseManager_h
#define DatabaseManager_h

#include "tinyxml.h"
#include "DBNode.h"

class DatabaseManager
{
public:

    DatabaseManager();
    ~DatabaseManager();
    void Initialize();
    void Shutdown();
    int GenerateUniqueID();
    vector<DBNode*> Search(const string& key);
    void LoadFromFile();
    void SaveToFile();
    string Search(string& name);

protected:

    // PROTECTED VARIABLES

private:

    void CreateSiblingNode( TiXmlElement* currentNode, DBNode* parent );
    void CreateChildNode( TiXmlElement* currentNode, DBNode* parent );
    void ToNextSiblingNode(DBNode* parent);
    void ToNextChildNode(DBNode* parent);
    DBNode* mRootNode;
    int mSize;

};

#endif  // _DatabaseManager_h_
