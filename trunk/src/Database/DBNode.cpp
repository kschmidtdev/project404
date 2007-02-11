#include "DBNode.h"

DBNode::DBNode(const int uniqueID, const string & name, DBNode* parent, vector<DBNode*> children, vector<DBData*> attributes) :
DBBase(uniqueID), mName(name), mParent(parent), mChildren(children), mAttributes(attributes)
{
}

DBNode::~DBNode()
{
}

DBNode* DBNode::GetChildren()
{

    return NULL; // tesing

}

DBNode* DBNode::GetAttributes()
{

    return NULL; // testing

}

DBData* DBNode::GetAttribute(const string & name)
{

    DBData* SearchKey = new DBData(0, name);
    mAIter = find(mAttributes.begin(), mAttributes.end(), SearchKey);
    return NULL;

}

