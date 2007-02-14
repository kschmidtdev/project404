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
 * Karl Schmidt, February 13 2007 | Added code to make DatabaseManager a singleton
 */

#ifndef DatabaseManager_h
#define DatabaseManager_h

#include "tinyxml.h"
#include "DBNode.h"

class DatabaseManager
{
public:

    /**
    * Returns the instance of the DatabaseManager
    */
    static DatabaseManager* GetInstance();

    /**
    * Deconstructor
    */
    ~DatabaseManager();

    /**
    * Initializes the DatabaseManager (sets up anything that must be
    * set up before any functions can be run)
    */
    void Initialize();

    /**
    * Shuts down the DatabaseManager, cleans up anything left
    * open or reserved
    */
    void Shutdown();

    int GenerateUniqueID();
    bool LoadFromFile(const string& filename);
    void SaveToFile();
    DBNode* GetRootNode() { return mRootNode; }
    DBNode* Search(const string& name);

protected:
    // PROTECTED METHODS

    /**
    * Default constructor.
    */
    DatabaseManager();


    // PROTECTED VARIABLES

    static DatabaseManager* _instance;

private:

    void CreateSiblingNode( TiXmlElement* currentNode, DBNode* parent );
    void CreateChildNode( TiXmlElement* currentNode, DBNode* parent );
    DBData* CreateAttribute( TiXmlElement* thisTag );

    vector<DBNode*> mSearchList;
    DBNode* mRootNode;
    int mSize;

};

#endif  // _DatabaseManager_h_
