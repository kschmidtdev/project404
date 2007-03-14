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

    /**
     * Constructor with 3 parameters.
     */
    DBColour(const int uniqueID, const string& name, const int* colourData);

    /**
     * Default destructor.
     */
    virtual ~DBColour();

    /**
     * Get Method. Return its class type.
     */
    virtual string GetType() { return "DBColour"; } // INLINE METHOD.

    /**
     * Get Method. Return the pointer of its data.
     */
    int* GetData() { return mColourData; } // INLINE METHOD.

    /**
     * Get Method. Return the value of Red.
     */
    int GetRed() { return mColourData[0]; } // INLINE METHOD.

    /**
     * Get Method. Return the value of Green.
     */
    int GetGreen() { return mColourData[1]; } // INLINE METHOD.

    /**
     * Get Method. Return the value of Blue.
     */
    int GetBlue() { return mColourData[2]; } // INLINE METHOD.

    /**
     * Set Method.
     */
     void SetRed(int red) { mColourData[0] = red; }

    /**
     * Set Method.
     */
     void SetGreen(int green) { mColourData[1] = green; }

    /**
     * Set Method.
     */
     void SetBlue(int blue) { mColourData[2] = blue; }

protected:

private:

    // VARIABLES
    int mColourData[3]; // saves a colour data : Red, Green, Blue.

};

#endif  // _DBColour_h_
