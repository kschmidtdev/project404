/**
 * File: UICursor.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, February 11 2007 | Initial Creation
 */
#include "UICursor.h"                                // class implemented


/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

UICursor::UICursor()
{
}// UICursor

UICursor::UICursor(const string fileName, const string buttonHeading)
{
    mElementImage = ResourceManager::GetInstance()->LoadTexture(fileName);

}// UICursor


UICursor::~UICursor()
{

}// ~UICursor


//============================= OPERATORS ====================================


//============================= OPERATIONS ===================================


//============================= ACCESS     ===================================

//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
