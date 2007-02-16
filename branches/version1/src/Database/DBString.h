/**
 * Subclass of DBData for storing string-type data
 *
 * #include "DBString.h"
 *
 * This class stores a unique ID, name, and string data.
 *
 * @see DBData.h
 *
 * Project 404 2007
 *
 * Authors:
 * Seung Woo Han, February 7 2007 | Initial design
 * Seung Woo Han, February 11 2007 | Done for all the basic implementation
 */


#ifndef DBString_h
#define DBString_h

#include "DBData.h"

class DBString : public DBData
{
public:

    /**
     * Constructor.
     */
    DBString(const int uniqueID, const string& name, const string& stringData);

    /**
     * Default Destructor.
     */
    virtual ~DBString(void);

    /**
     * Get Method. Return its class type.
     */
    virtual string GetType() { return "DBString"; } // INLINE METHOD.

    /**
     * Get Method. Return its data.
     */
    string GetData() { return mStringData; } // INLINE METHOD.

protected:

private:

    // VARIABLES
    string mStringData;

};

#endif  // _DBString_h_
