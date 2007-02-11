/**
 * A one line description of the class.
 *
 * #include "DatabaseManager.h"
 *
 * A longer description.
 *
 * @see something
 *
 * Project 404 2007
 *
 * Authors:
 * Name, Date (Month Day Year), What was done
 */

#ifndef DatabaseManager_h
#define DatabaseManager_h

#include <time.h>
#include "DBNode.h"
#include "HashTable.h"

class DatabaseManager
{
public:

    DatabaseManager();
    ~DatabaseManager();
    void Initialize();
    void Shutdown();
    int GenerateUniqueID(const int datatype);
    vector<DBNode*> Search(const string& key);
    void LoadFromFile();
    void SaveToFile();

protected:
// PROTECTED VARIABLES
private:

    DBNode* mRootNode;
    // vector<DBNode*> mDatabase;
    HashTable<DBNode*> * mDatabase;

};

#endif  // _DatabaseManager_h_
