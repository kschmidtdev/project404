/**
 * A one line description of the class.
 *
 * #include "DBVector2D.h"
 *
 * A longer description.
 *
 * @see something
 *
 * Project 404 2007
 *
 * Authors:
 * Name, Date (Month Day Year), What was done
 */

#ifndef DBVector2D_h
#define DBVector2D_h

#include "DBData.h"

class DBVector2D : public DBData
{
public:

    DBVector2D(const int uniqueID, const string & name, const int* vector2DData);
    virtual ~DBVector2D();
    int* GetData() { return mVector2DData; }
    int GetX() { return mVector2DData[0]; }
    int GetY() { return mVector2DData[1]; }

protected:

private:

    int mVector2DData[2];

};

#endif  // _DBVector2D_h_
