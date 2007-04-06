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
 * Karl Schmidt, March 15 2007  | Big changes to support reloading db
 */

#ifndef DatabaseManager_h
#define DatabaseManager_h

#include "tinyxml.h"
#include "DBNode.h"
#include <sstream>

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

    void ClearLoadedData();

    /**
     * Check if the incoming file can be loaded by tinyXML or not
     */
    bool IsValidFile( const string & fileName, const string & userName );

    /**
     * Load XML file and creates Nodes from that file.
     */
    bool LoadFromFile(const string& filename);

    /**
     * Save to XML file.
     */
    void SaveToFile(const string& filename);

    /**
     * Get Method. Return the root node of the database.
     */
    DBNode* GetRootNode() { return mRootNode; } // INLINE METHOD.

    /**
     * Search a Node which is specified with a parameter.
     */
    DBNode* Search(const string& name);

    /**
     * Update existing Node. Update DBString.
     */
     bool UpdateNode(const string& nodeName, const string& attributeName, const string& value);

    /**
     * Update existing Node. Update DBInt.
     */
     bool UpdateNode(const string& nodeName, const string& attributeName, int value);

    /**
     * Update existing Node. Update DBVector2D
     */
     bool UpdateNode(const string& nodeName, const string& attributeName,int xValue, int yValue);

protected:

    // PROTECTED METHODS
    /**
    * Default constructor.
    */
    DatabaseManager();

    // PROTECTED VARIABLES
    static DatabaseManager* _instance;

private:

    // METHODS
    /**
     * Generate a Unique ID for each Node and Data.
     */
    int GenerateUniqueID();

    /**
     * This is a recursive function. Which finds and creates a sibling node.
     */
    void CreateSiblingNode( TiXmlElement* currentElement, DBNode* parentNode );

    /**
     * This is a recursive function. Which finds and creates a child node.
     */
    void CreateChildNode( TiXmlElement* currentElement, DBNode* parentNode );

    /**
     * This is a recursive function. Which finds and creates a attribute data.
     */
    DBData* CreateAttribute( TiXmlElement* thisTag );

    /**
     * This is a recursive function. Which finds and saves a sibling node to the output file.
     */
    void SaveSiblingNode( DBNode* currentNode, TiXmlElement* parentElement );

    /**
     * This is a recursive function. Which finds and saves a child node to the output file.
     */
    void SaveChildNode( DBNode* currentNode, TiXmlElement* parentElement );

    /**
     * This is a recursive function. Which finds and saves attributes of this node to the output file.
     */
    void SaveAttribute( DBNode* thisNode, TiXmlElement* parentElement );

    // VARIABLES
    vector<DBNode*> mSearchList;
    DBNode* mRootNode;
    int mSize; // Save a size of Nodes and Datas.
};

#endif  // _DatabaseManager_h_
