/**
 * A one line description of the class.
 *
 * #include "DBNode.h"
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

#ifndef DBNode_h
#define DBNode_h

#include <string>
#include <vector>
#include "DBBase.h"
#include "DBData.h"
using namespace std;

class DBNode : public DBBase
{
public:

    // no default constructor.
    DBNode(const int uniqueID, const string & name, DBNode* parent = NULL, vector<DBNode*> children = NULL, vector<DBData*> attributes = NULL);
    virtual ~DBNode(void);
    // Serialization here.
    string GetName() { return mName; }
    DBNode* GetParent() { return mParent; } // *** How do I make sure that returned value (mParent) is not changing anywhere?
    DBNode* GetChildren(); // using iterator to traverse all the children in the vector container.
    DBNode* GetAttributes(); // using iterator to traverse all the attributes in the vector container.
    DBData* GetAttribute(const string & name); // return the specific attribute in the attribute vector.
    void SetParent(DBNode* parent) { mParent = parent; }

protected:

private:

    string mName;
    DBNode* mParent;
    vector<DBNode*> mChildren;
    vector<DBData*> mAttributes;

    vector<DBNode*>::iterator mCIter; // iterator for Children vector.
    vector<DBData*>::iterator mAIter; // iterator for attributes vector.

};

#endif  // _DBNode_h_
