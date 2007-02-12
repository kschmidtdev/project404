/**
 * File: UICursor.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Name, Date | Work Done
 */
#include "UICursor.h"                                // class implemented


/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

UICursor::UICursor()
{
}// UICursor

UICursor::UICursor(const string fileName, const string buttonHeading)
{
    elementImage = ResourceManager::GetInstance()->LoadTexture(fileName);

}// UICursor


UICursor::~UICursor()
{
}// ~UICursor


//============================= OPERATORS ====================================


//============================= OPERATIONS ===================================
/*
UICursor::moveUp(void)
{
}

UICursor::moveDown(void)
{
}

UICursor::moveLeft(void)
{
}

UICursor::moveRight(void)
{
}



//============================= ACCESS     ===================================


UICursor::setDefaultPos(Point startPos)
{
}

UICursor::setDefaultPos*/
//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
