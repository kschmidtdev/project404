#include "DatabaseManager.h"

DatabaseManager::DatabaseManager()
{

    mDatabase = new HashTable<DBNode*>;
    srand(time(NULL)); // generate seed for random value.

}

DatabaseManager::~DatabaseManager()
{

    delete mDatabase;

}

int DatabaseManager::GenerateUniqueID(const int datatype)
{

    int uniqueID = datatype * 10000;



}
