/**
 * A one line description of the class.
 *
 * #include "DBString.h"
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

#ifndef DBString_h
#define DBString_h

class DBString : public DBData
{
public:

    DBString(const int uniqueID, const string & name, const string & stringData) : DBBase(uniqueID), DBData(uniqueID, name) { mStringData = stringData; }
    ~DBString(void);

    string getData() { return mStringData; }

protected:

private:

    string mStringData;

};

#endif  // _DBString_h_
