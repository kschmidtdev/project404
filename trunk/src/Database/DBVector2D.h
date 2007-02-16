/**
 * Subclass of DBData for storing 2D-Vector-type data
 *
 * #include "DBVector2D.h"
 *
 * This class stores a unique ID, name, and 2D Vector data(which are 2 integers)
 *
 * @see DBData.h
 *
 * Project 404 2007
 *
 * Authors:
 * Seung Woo Han, February 7 2007 | Initial design
 * Seung Woo Han, February 11 2007 | Done for all the basic implementation
 */


#ifndef DBVector2D_h
#define DBVector2D_h

#include "DBData.h"

class DBVector2D : public DBData
{
public:

    /**
     * Constructor.
     */
    DBVector2D(const int uniqueID, const string& name, const int* vector2DData);

    /**
     * Default Destructor.
     */
    virtual ~DBVector2D();

    /**
     * Get Method. Return its class type.
     */
    virtual string GetType() { return "DBVector2D"; } // INLINE METHOD.

    /**
     * Get Method. Return the pointer of its data.
     */
    int* GetData() { return mVector2DData; } // INLINE METHOD.

    /**
     * Get Method. Return the value of X-coordinate.
     */
    int GetX() { return mVector2DData[0]; } // INLINE METHOD.

    /**
     * Get Method. Return the value of Y-coordinate.
     */
    int GetY() { return mVector2DData[1]; } // INLINE METHOD.

protected:

private:

    // VARIABLES
    int mVector2DData[2];

};

#endif  // _DBVector2D_h_
