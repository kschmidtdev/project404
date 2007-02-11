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
