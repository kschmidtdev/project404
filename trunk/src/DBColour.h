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
 * Authors:
 * Name, Date (Month Day Year), What was done
 */

#ifndef DBColour_h
#define DBColour_h

class DBColour : public DBData
{
public:

    DBColour(const int uniqueID, const string & name, const int* colourData) : DBBase(uniqueID), DBData(uniqueID, name) { /* mColourData =  colourData; */ }
    ~DBColour(void);

    int* getData() { return mColourData; }
    int getRed() { return mColourData[0]; }
    int getGreen() { return mColourData[1]; }
    int getBlue() { return mColourData[2]; }

protected:

private:

    int mColourData[3];

};

#endif  // _DBColour_h_
