/**
 * File: DBNode.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Seung Woo Han, February 7 2007 | Initial design
 * Seung Woo Han, February 11 2007 | Created some overloading constructors and added more functions.
 * Karl Schmidt, February 14 2007 | Fixed some bugs that crashed on some machines (invalid iters, ptrs)
 */

#include "DBNode.h"                                       // class implemented
/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

DBNode::DBNode( const int uniqueID, const string& name )
: DBBase( uniqueID ), mName( name ), mParent( NULL )
{
} // DBNode

DBNode::DBNode( const int uniqueID, const string& name, DBNode* parent )
: DBBase( uniqueID ), mName( name ), mParent( parent )
{
} // DBNode

DBNode::DBNode( const int uniqueID, const string& name, DBNode* parent, vector<DBNode*> children )
: DBBase( uniqueID ), mName( name ), mParent( parent ), mChildren( children )
{
} // DBNode

DBNode::DBNode( const int uniqueID, const string& name, DBNode* parent, vector<DBNode*> children, vector<DBData*> attributes )
: DBBase( uniqueID ), mName( name ), mParent( parent ), mChildren( children ), mAttributes( attributes )
{
} // DBNode

DBNode::~DBNode()
{
} // ~DBNode

//============================= OPERATORS ====================================
//============================= OPERATIONS ===================================
//============================= ACCESS     ===================================
//============================= INQUIRY    ===================================

DBNode* DBNode::GetFirstChild()
{
    mChildrenIter = mChildren.begin();
    return *mChildrenIter;
}

DBNode* DBNode::GetNextChild()
{
    ++mChildrenIter;
    if ( mChildrenIter != mChildren.end() )
    {
        return *mChildrenIter;
    }
    else
    {
        return NULL;
    }
}

DBNode* DBNode::GetChild( const string& name )
{
    vector<DBNode*>::iterator Iter;
    for ( Iter = mChildren.begin(); Iter != mChildren.end(); Iter++ )
    {
        if ( (*Iter)->GetName() == name ) return *Iter;
    }

    return NULL; // no matching entry.
}

DBData* DBNode::GetFirstAttribute()
{
    mAttributesIter = mAttributes.begin();
    if( mAttributesIter != mAttributes.end() )
    {
        return *mAttributesIter;
    }
    else
    {
        return NULL;
    }
}

DBData* DBNode::GetNextAttribute()
{
    ++mAttributesIter;
    if ( mAttributesIter != mAttributes.end() )
    {
        return *mAttributesIter;
    }
    else
    {
        return NULL;
    }
}

DBData* DBNode::GetAttribute( const string& name )
{
    vector<DBData*>::iterator Iter;
    for ( Iter = mAttributes.begin(); Iter != mAttributes.end(); Iter++ )
    {
        if ( (*Iter)->GetName() == name ) return *Iter;
    }

    return NULL; // no matching entry.
}

/////////////////////////////// PROTECTED  ///////////////////////////////////
/////////////////////////////// PRIVATE    ///////////////////////////////////
