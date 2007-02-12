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
    DBBase(const int uniqueID); // constructor with 1 argument.
    virtual ~DBBase(void) = 0; // destructor with a pure virtual function.
    int GetUniqueID() { return mUniqueID; }

protected:

    // proteced here.

private:

    int mUniqueID;

};

#endif  // _DBBase_h_
