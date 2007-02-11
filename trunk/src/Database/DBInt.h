/**
 * A one line description of the class.
 *
 * #include "DBInt.h"
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

#ifndef DBInt_h
#define DBInt_h

#include "DBData.h"

class DBInt : public DBData
{
public:

    DBInt(const int uniqueID, const string & name, const int intData);
    virtual ~DBInt(void);
    int GetData() { return mIntData; }

protected:

private:

    int mIntData;

};

#endif  // _DBInt_h_
