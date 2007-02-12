/**
 * Subclass of DBData for storing colour-type data
 *
 * #include "DBColour.h"
 *
 * This class stores a unique ID, name, and colour data.
 *
 * @see DBData.h
 *
 * Project 404 2007
 *
 * Authors:
 * Seung Woo Han, February 7 2007 | Initial design
 * Seung Woo Han, February 11 2007 | Done for all the basic implementation
 */

#ifndef DBColour_h
#define DBColour_h

#include "DBData.h"

class DBColour : public DBData
{
public:

    DBColour(const int uniqueID, const string& name, const int* colourData);
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
