/**
 * A one line description of the class.
 *
 * #include "DBFloat.h"
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

#ifndef DBFloat_h
#define DBFloat_h

#include "DBData.h"

class DBFloat : public DBData
{
public:

    DBFloat(const int uniqueID, const string & name, const float floatData);
    virtual ~DBFloat();
    float GetData() { return mFloatData; }

protected:

private:

    float mFloatData;

};

#endif  // _DBFloat_h_
