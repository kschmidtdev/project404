/**
 * File: UICursor.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, February 11 2007 | Initial Creation
 * Andrew Osborne, March 18 2007 | Re-initialized class for use, added UpdatePos and SetAttach methods
 * Karl Schmidt, March 22 2007      | Correcting include orders and paths
 */

#include "UICursor.h"                                // class implemented

#include <util.h>

#include <ResourceManager/ResourceManager.h>

/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

UICursor::UICursor()
{
}// UICursor

UICursor::UICursor( const std::string & filename, const Point & point, UIElement* start )
: mAttach( start ), mOffset( point )
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
