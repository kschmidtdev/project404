/**
 * A one line description of the class.
 *
 * #include "DBBase.h"
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

#ifndef DBBase_h
#define DBBase_h

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//

// LOCAL INCLUDES
//

// FORWARD REFERENCES
//


class DBBase // This is abstract base class(ABC).
{
public:

    // No default constructor.

    DBBase(const int uniqueID) { mUniqueID = uniqueID; } // constructor with 1 argument.

    ~DBBase(void) = 0; // destructor with pure virtual function.

    int getUniqueID() { return mUniqueID; }

protected:

private:

    int mUniqueID;

};

#endif  // _DBBase_h_
