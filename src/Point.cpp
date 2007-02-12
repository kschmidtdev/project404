/**
 * File: Point.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Mike Malyuk,    February 7, 2007 | Initial design
 * Andrew Osborne, February 8, 2007 | Added default construct
 * Mike Malyuk,    February 9, 2007 | Added comparison operator
 * Andrew Osborne, February 10 2007 | added Set(x,y) function
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
//============================= OPERATORS  ===================================
bool Point::operator==(const Point &other) const
{
    if(mX == other.mX && mY == other.mY)
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool Point::operator!=(const Point &other)const
{
    if(mX == other.mX && mY == other.mY)
    {
        return false;
    }
    else
    {
        return true;
    }
}

Point Point::operator+(const Point &other)const
{
    return Point( mX + other.mX, mY + other.mY);
}

Point Point::operator*(const int &other)const
{
    return Point( mX * other, mY * other );
}

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

void Point::Set(int x, int y)
{
    mX = x;
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
