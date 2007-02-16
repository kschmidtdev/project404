/**
 * Subclass of DBData for storing integer-type data
 *
 * #include "DBInt.h"
 *
 * This class stores a unique ID, name, and integer data.
 *
 * @see DBData.h
 *
 * Project 404 2007
 *
 * Authors:
 * Seung Woo Han, February 7 2007 | Initial design
 * Seung Woo Han, February 11 2007 | Done for all the basic implementation
 */

#ifndef DBInt_h
#define DBInt_h

#include "DBData.h"

class DBInt : public DBData
{
public:

    /**
     * Constructor.
     */
    DBInt(const int uniqueID, const string& name, const int intData);

    /**
     * Default Destructor.
     */
    virtual ~DBInt(void);

    /**
     * Get Method. Return its class type.
     */
    virtual string GetType() { return "DBInt"; } // INLINE METHOD.

    /**
     * Get Method. Return its data.
     */
    int GetData() { return mIntData; } // INLINE METHOD.

protected:

private:

    // VARIABLES
    int mIntData;

};

#endif  // _DBInt_h_
