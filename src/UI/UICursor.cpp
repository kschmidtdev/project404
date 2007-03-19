/**
 * File: UICursor.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, February 11 2007 | Initial Creation
 * Andrew Osborne, March 18 2007 | Re-initialized class for use, added UpdatePos and SetAttach methods
 */

#include <util.h>


#include "UICursor.h"                                // class implemented


/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

UICursor::UICursor()
{
}// UICursor

UICursor::UICursor(string filename, Point o, UIElement* start)
: mOffset( o ), mAttach( start )
{

    mElementImage = ResourceManager::GetInstance()->LoadTexture(filename);

}// UICursor


UICursor::~UICursor()
{
    mAttach = NULL;
}// ~UICursor


//============================= OPERATORS ====================================


//============================= OPERATIONS ===================================

void UICursor::UpdatePos(void)
{
    if (mAttach)
    {
        SetPos( mAttach->GetPos() + mOffset );
    }
}

//============================= ACCESS     ===================================

void UICursor::SetAttach(UIElement* e)
{
    mAttach = e;
    if (mAttach)
        UpdatePos();
}

//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
