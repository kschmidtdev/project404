/**
 * File: DBNode.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Seung Woo Han, February 7 2007 | Initial design
 * Seung Woo Han, February 11 2007 | Created some overloading constructors and added more functions.
 */

#include "DBNode.h"
#include <iostream>
using namespace std;

DBNode::DBNode(const int uniqueID, const string& name)
: DBBase(uniqueID), mName(name), mParent(NULL)
{
}

DBNode::DBNode(const int uniqueID, const string& name, DBNode* parent)
: DBBase(uniqueID), mName(name), mParent(parent)
{
}

DBNode::DBNode(const int uniqueID, const string& name, DBNode* parent, vector<DBNode*> children)
: DBBase(uniqueID), mName(name), mParent(parent), mChildren(children)
{
}

DBNode::DBNode(const int uniqueID, const string& name, DBNode* parent, vector<DBNode*> children, vector<DBData*> attributes)
: DBBase(uniqueID), mName(name), mParent(parent), mChildren(children), mAttributes(attributes)
{
}

DBNode::~DBNode()
{
}

DBNode* DBNode::GetFirstChild()
{
    mChildrenIter = mChildren.begin();
    return *mChildrenIter;
}

DBNode* DBNode::GetNextChild()
{
    if ( mChildrenIter != mChildren.end() )
    {
        mChildrenIter++;
        return *mChildrenIter;
    }

    else
    {
        return NULL;
    }
}

DBNode* DBNode::GetChild(const string& name)
{
    vector<DBNode*>::iterator Iter;
    for ( Iter = mChildren.begin(); Iter != mChildren.end(); Iter++)
    {
        if ( (*Iter)->GetName() == name ) return *Iter;
    }

    return NULL; // no matching entry.
}

DBData* DBNode::GetFirstAttribute()
{
    mAttributesIter = mAttributes.begin();
    return *mAttributesIter;
}

DBData* DBNode::GetNextAttribute()
{
    if ( mAttributesIter != mAttributes.end() )
    {
        mAttributesIter++;
        return *mAttributesIter;
    }

    else
    {
        return NULL;
    }
}

DBData* DBNode::GetAttribute(const string& name)
{
    vector<DBData*>::iterator Iter;
    for ( Iter = mAttributes.begin(); Iter != mAttributes.end(); Iter++)
    {
        if ( (*Iter)->GetName() == name ) return *Iter;
    }

    return NULL; // no matching entry.
}

void DBNode::CheckDataType(const string& type) {


}

void DBNode::TestFunc()
{
    vector<DBNode*>::iterator Iter;
    for ( Iter = mChildren.begin(); Iter != mChildren.end(); Iter++)
    {
        cout << (*Iter)->GetName() << endl;
    }

}

