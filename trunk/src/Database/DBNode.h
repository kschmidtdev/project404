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

    DBNode* GetFirstChild();
    DBNode* GetNextChild();
    DBNode* GetChild(const string& name); // return the specific child in the child vector.

    DBData* GetFirstAttribute();
    DBData* GetNextAttribute();
    DBData* GetAttribute(const string& name); // return the specific attribute in the attribute vector.

    void SetParent(DBNode* parent) { mParent = parent; }
    void AddChild(DBNode * child) { mChildren.push_back(child); }
    void AddAttribute(DBData* attribute) { mAttributes.push_back(attribute); }

protected:

private:

    string mName;
    DBNode* mParent;
    vector<DBNode*> mChildren;
    vector<DBData*> mAttributes;

    vector<DBNode*>::iterator mChildrenIter;
    vector<DBData*>::iterator mAttributesIter;

};

#endif  // _DBNode_h_