#include "DBString.h"

DBString::DBString(const int uniqueID, const string & name, const string & stringData)
: DBData(uniqueID, name), mStringData(stringData)
{
}

DBString::~DBString()
{
}
