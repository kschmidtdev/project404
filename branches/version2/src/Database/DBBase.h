/**
 * Base class for every other classes in database(except DatabaseManager class)
 *
 * #include "DBBase.h"
 *
 * This class stores a unique ID which might be useful in further implementaion
 * This class cannot be instaniated(Abstract Base Class)
 *
 * Project 404 2007
 *
 * Authors:
 * Seung Woo Han, February 7 2007 | Initial design
 * Seung Woo Han, February 11 2007 | Done for all the basic implementation
 */

#ifndef DBBase_h
#define DBBase_h

class DBBase // This is abstract base class(ABC).
{

public:

    // No default constructor.

    /**
     * Constructor which takes a int (unique ID).
     */
    DBBase(const int uniqueID); // constructor with 1 argument.

    /**
     * Destructor. This is a pure virtual function which makes DBBase class Abstarct Base Class.
     */
    virtual ~DBBase(void) = 0; // destructor with a pure virtual function.

    /**
     * Simple Get method. Get UniqueID of this instance.
     */
    int GetUniqueID() { return mUniqueID; } // INLINE METHOD : returns a unique ID of this instance.

protected:

    // proteced here.

private:

    // VARIABLES
    int mUniqueID; // variable to save a unique ID of this instance.

};

#endif  // _DBBase_h_
