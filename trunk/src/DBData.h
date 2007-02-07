/**
 * A one line description of the class.
 *
 * #include "DBData.h"
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

#ifndef DBData_h
#define DBData_h

#include <string>

class DBData : public DBBase // ABS.
{
public:

    DBData(const int uniqueID, const string & name) : DBBase(uniqueID), mName(name) {}

    ~DBData(void) = 0;

    string getName() { return mName; }

protected:

private:

    string mName;

};

#endif  // _DBData_h_
