/**
 * Subclass of DBBase.
 *
 * #include "DBNode.h"
 *
 * This class stores a unique ID, name, parent Node, children Nodes(0 to infinite numbers of),
 * and attributes(DBData-type)
 *
 * @see DBBase.h
 *
 * Project 404 2007
 *
 * Authors:
 * Seung Woo Han, February 7 2007 | Initial design
 * Seung Woo Han, February 11 2007 | Added more functinos related to iterator.
 */


#ifndef DBNode_h
#define DBNode_h

#include <string>
#include <vector>
#include "DBBase.h"
#include "DBData.h"
#include "DBColour.h"
#include "DBFloat.h"
#include "DBInt.h"
#include "DBString.h"
#include "DBVector2D.h"
using namespace std;

class DBNode : public DBBase
{
public:

    // no default constructor.
    DBNode(const int uniqueID, const string& name);
    DBNode(const int uniqueID, const string& name, DBNode* parent);
    DBNode(const int uniqueID, const string& name, DBNode* parent, vector<DBNode*> children);
    DBNode(const int uniqueID, const string& name, DBNode* parent, vector<DBNode*> children, vector<DBData*> attributes);
    virtual ~DBNode(void);
    // Serialization here.
    string GetName() { return mName; }
    DBNode* GetParent() { return mParent; } // *** How do I make sure that returned value (mParent) is not changing anywhere?

    vector<DBNode*>::iterator GetFirstChild() { return mChildren.begin(); }
    vector<DBNode*>::iterator GetEndChild() { return mChildren.end(); }
    vector<DBData*>::iterator GetFirstAttribute() { return mAttributes.begin(); }
    vector<DBData*>::iterator GetEndAttribute() { return mAttributes.end(); }

    vector<DBNode*>* GetChildren() { return &mChildren; }

    DBData* GetAttribute(const string& name); // return the specific attribute in the attribute vector.
    void SetParent(DBNode* parent) { mParent = parent; }
    void AddChild(DBNode * child) { mChildren.push_back(child); }
    void AddAttribute(DBData* attribute) { mAttributes.push_back(attribute); }

    void CheckDataType(const string& type); // Determine what type of the data it is : DBInt, DBFloat, DBString, and etc.

protected:

private:

    string mName;
    DBNode* mParent;
    vector<DBNode*> mChildren;
    vector<DBData*> mAttributes;

};

#endif  // _DBNode_h_
