/**
 * File: Point.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Mike Malyuk, February 7 2007 | Initial design
 */

#include "Point.h"                                // class implemented


/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

Point::Point()
: mX( 0 ), mY( 0 )
{
}// Point

Point::Point(int x, int y):mX(x), mY(y){}

Point::Point(const Point& from)
{
    mX = from.mX;
    mY = from.mY;
}// Point

Point::~Point()
{
}// ~Point

//============================= OPERATIONS ===================================
//============================= ACCESS     ===================================
void Point::SetX(int x)
{
    mX = x;
}

void Point::SetY(int y)
{
    mY = y;
}

int Point::GetX()
{
    return mX;
}

int Point::GetY()
{
    return mY;
}
//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
