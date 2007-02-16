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

    /**
     * Constructor takes two parameters.
     */
    DBNode(const int uniqueID, const string& name);

    /**
     * Constructor takes 3 parameters.
     */
    DBNode(const int uniqueID, const string& name, DBNode* parent);

    /**
     * Constructor takes 4 parameters.
     */
    DBNode(const int uniqueID, const string& name, DBNode* parent, vector<DBNode*> children);

    /**
     * Constructor takes 5 parameters.
     */
    DBNode(const int uniqueID, const string& name, DBNode* parent, vector<DBNode*> children, vector<DBData*> attributes);

    /**
     * Default Destructor.
     */
    virtual ~DBNode(void);

    /**
     * Get Method. Return the name of this node.
     */
    string GetName() { return mName; }

    /**
     * Get Method. Return the pointer of its parent node.
     */
    DBNode* GetParent() { return mParent; } // *** How do I make sure that returned value (mParent) is not changing anywhere?

    /**
     * Get Method. Return the pointer of its first child node.
     */
    DBNode* GetFirstChild();

    /**
     * Get Method. Return the pointer of its next child node.
     */
    DBNode* GetNextChild();

    /**
     * Get Method. Return the pointer of its child node specified with parameter.
     */
    DBNode* GetChild(const string& name); // return the specific child in the child vector.

    /**
     * Get Method. Return the pointer of its first attribute data.
     */
    DBData* GetFirstAttribute();

    /**
     * Get Method. Return the pointer of its next attribute data.
     */
    DBData* GetNextAttribute();

    /**
     * Get Method. Return the pointer of its attribute data specified with parameter.
     */
    DBData* GetAttribute(const string& name); // return the specific attribute in the attribute vector.

    /**
     * Set Method. Set its parent node.
     */
    void SetParent(DBNode* parent) { mParent = parent; } // INLINE METHOD.

    /**
     * Add Method. Add its child node.
     */
    void AddChild(DBNode * child) { mChildren.push_back(child); } // INLINE METHOD.

    /**
     * Add Method. Add its attribute data.
     */
    void AddAttribute(DBData* attribute) { mAttributes.push_back(attribute); } // INLINE METHOD.

protected:

private:

    // VARIABLES
    string mName;
    DBNode* mParent;
    vector<DBNode*> mChildren;
    vector<DBData*> mAttributes;
    vector<DBNode*>::iterator mChildrenIter;
    vector<DBData*>::iterator mAttributesIter;

};

#endif  // _DBNode_h_
