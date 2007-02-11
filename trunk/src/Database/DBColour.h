/**
 * A one line description of the class.
 *
 * #include "DBColour.h"
 *
 * A longer description.
 *
 * @see something
 *
 * Project 404 2007
 *
 * Authors : Seung Woo, Han
 * Date : 2007.02.07
 */

#ifndef DBColour_h
#define DBColour_h

#include "DBData.h"

class DBColour : public DBData
{
public:

    DBColour(const int uniqueID, const string & name, const int* colourData);
    virtual ~DBColour();
    int* GetData() { return mColourData; }
    int GetRed() { return mColourData[0]; }
    int GetGreen() { return mColourData[1]; }
    int GetBlue() { return mColourData[2]; }

protected:

private:

    int mColourData[3];

};

#endif  // _DBColour_h_
