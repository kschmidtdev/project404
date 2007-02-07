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

class DBVector2D : public DBBase, public DBData
{
public:

    DBVector2D(const int uniqueID, const string & name, const int* vector2DData) : DBBase(uniqueID), DBData(uniqueID, name) { /* mVector2DData =  vector2DData; */ }
    ~DBVector2D(void);

    int* getData() { return mVector2DData; }
    int getX() { return mVector2DData[0]; }
    int getY() { return mVector2DData[1]; }

protected:

private:

    int mVector2DData[2];

};

#endif  // _DBVector2D_h_
