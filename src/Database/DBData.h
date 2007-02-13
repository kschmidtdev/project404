/**
 * Subclass of DBBase. This is also a base class for all other data classes.
 *
 * #include "DBData.h"
 *
 * This class stores a unique ID, and name
 * This class cannot be instaniated(Abstract Base Class)
 *
 * @see DBBase.h
 *
 * Project 404 2007
 *
 * Authors:
 * Seung Woo Han, February 7 2007 | Initial design
 * Seung Woo Han, February 11 2007 | Done for all the basic implementation
 */


#ifndef DBData_h
#define DBData_h

#include <string>
#include "DBBase.h"
using namespace std;

class DBData : public DBBase // ABS.
{
public:

    DBData(const int uniqueID, const string& name);
    virtual ~DBData(void) = 0;
    virtual string GetType() { return "DBBase"; }
    string GetName() { return mName; }


protected:

private:

    string mName;

};

#endif  // _DBData_h_
