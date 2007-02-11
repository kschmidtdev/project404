#include "DBInt.h"

DBInt::DBInt(const int uniqueID, const string & name, const int intData)
: DBData(uniqueID, name),  mIntData(intData)
{
}

DBInt::~DBInt()
{
}
