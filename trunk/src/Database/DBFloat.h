/**
 * Subclass of DBData for storing float-type data
 *
 * #include "DBFloat.h"
 *
 * This class stores a unique ID, name, and float data.
 *
 * @see DBData.h
 *
 * Project 404 2007
 *
 * Authors:
 * Seung Woo Han, February 7 2007 | Initial design
 * Seung Woo Han, February 11 2007 | Done for all the basic implementation
 */

#ifndef DBFloat_h
#define DBFloat_h

#include "DBData.h"

class DBFloat : public DBData
{
public:

    /**
     * Constructor.
     */
    DBFloat(const int uniqueID, const string& name, const float floatData);

    /**
     * Default Destructor.
     */
    virtual ~DBFloat();

    /**
     * Get Method. Return its class type.
     */
    virtual string GetType() { return "DBFloat"; } // INLINE METHOD.

    /**
     * Get Method. Return its data.
     */
    float GetData() { return mFloatData; } // INLINE METHOD.

    /**
     * Set Method.
     */
     void SetData(float data) { mFloatData = data; }

protected:

private:

    // VARIABLES
    float mFloatData;

};

#endif  // _DBFloat_h_
