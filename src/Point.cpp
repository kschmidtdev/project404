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
 * Karl Schmidt,   February 14 2007 | Added consts
 */

#include "Point.h"                                // class implemented


/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

Point::Point()
: mX( 0 ), mY( 0 )
{
}// Point

Point::Point( const int x, const int y)
:mX(x), mY(y)
{}

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
void Point::SetX( const int x )
{
    mX = x;
}

void Point::SetY( const int y )
{
    mY = y;
}

void Point::Set( const int x, const int y )
{
    mX = x;
    mY = y;
}

int Point::GetX() const
{
    return mX;
}

int Point::GetY() const
{
    return mY;
}
//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
