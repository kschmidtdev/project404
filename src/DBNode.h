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

class DBNode : public DBBase
{
public:

    DBNode(const int uniqueID, const string & name) : DBBase(uniqueID), mName(name) {}
    // Another constructor here.
    ~DBNode(void);

    // Serialization.
    string getName() { return mName; }
    DBNode* getParent() { return mParent; }
    // getChildren. // getAttribute
    DBData* getAttribute(const string & name); // return the specific attribute in the attribute vector.

    void setParent(const DBNode* parent) { mParent = parent; }

protected:

private:

    string mName;
    DBNode* mParent;
    vector<DBNode*> mChildren;
    vector<DBData*> mAttributes;

};

#endif  // _DBNode_h_
