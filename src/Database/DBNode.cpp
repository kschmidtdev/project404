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

DBData* DBNode::GetAttribute(const string& name)
{
    return NULL;
}

void DBNode::CheckDataType(const string& type) {


}

